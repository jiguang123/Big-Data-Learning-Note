#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import requests
from bs4 import BeautifulSoup
import re
import os
import pymysql
#from itertools import islice

# 获取网页文档，创建BeautifulSoup对象
def get_soup(url):
    res = requests.get(url)  # 获取网页
    res.encoding = 'utf-8'  # 最好设为utf-8，防止不必要的麻烦
    #print(res.text)
    soup = BeautifulSoup(res.text,'html.parser')
    # print(soup)
    return (soup,res)  # 这里同时返回res是为后面的正则表达式服务

# 获取影片部分信息
def get_movie_comment(movie_url):
    (soup,res) = get_soup(movie_url)
    f = open("movie.txt", "a",encoding='utf-8')
    for items in soup.select('#content'):
        #print(items)
        movie_name = items.select('span')[0].text
        print(movie_name)
        f.write(movie_name + ",")
        for info in soup.select('#info'):
            #print(info)
            director = info.select('.attrs')[0].text
            print(director)
            editor = info.select('.attrs')[1].text
            actors = info.select('.attrs')[2].text.strip()
            actor = actors.split("/")[0:2]
            actor = ''.join(actor)
            print(actor)
            style = ' '.join([style.text for style in info.select('span[property="v:genre"]')]) # python 简洁一行
            print(style)
            time = info.select('span[property="v:initialReleaseDate"]')[0].text
            time = re.split('\(',time)[0]
            print(time)
            comment_url = items.select('.mod-hd span.pl a')[0]['href']
            #print(type(comment_url))
            print(comment_url)
            f.write(director + ",")
            f.write(editor + ",")
            f.write(actor + ",")
            f.write(style + ",")
            f.write(time + ",")
            f.write(comment_url + ',')
            f.close()
            get_eval(comment_url)
            for i in range(20,200,20): ##从start=20开始，间隔为20
                new_url = comment_url.replace("status=P","start={}").format(i)
                #print(new_url)
                get_comment(new_url)

# 获取评论整体情况
def get_eval(comment_url):
    (soup1, res1) = get_soup(comment_url)
    movie_comment = soup1.select('#content h1')[0].text.rsplit(' 短评')[0]
    f = open("movie.txt", "a", encoding='utf-8')
    f.write(movie_comment + ",")
    for it in soup1.select('.comment-filter'):
        #print(it)
        good_eval = it.select('.filter-name')[1].text   #评价
        good_cp = it.select('span.comment-percent')[1].text    #好评率
        common_eval = it.select('.filter-name')[2].text
        common_cp =it.select('span.comment-percent')[2].text
        bad_eval = it.select('.filter-name')[3].text
        bad_cp = it.select('span.comment-percent')[3].text
        # print(common_eval)
        # print(bad_eval)
        f.write(good_eval + ":")
        f.write(good_cp + ",")
        f.write(common_eval + ":")
        f.write(common_cp + ",")
        f.write(bad_eval + ":")
        f.write(bad_cp)
        f.write("\n")
    f.close()

# 获取全部评论
def get_comment(comment_url):
    (soup2, res2) = get_soup(comment_url)
    f = open("comment.txt", "a",encoding='utf-8')
    for sc in soup2.select('.mod-bd'):
        #print(sc)
        for i in range(0,18):
            commor = sc.select('.comment-info a')[i].text
            #stars = sc.select('.allstar.rating')[i]['title']
            #print(stars)
            #re_words = re.compile(u"(\s),[\u4e00-\u9fa5]+")
            #res = ''.join(re.findall(re_words, stars))
            stars = re.findall(r'<span class="allstar(.+) rating" title=".+"></span>', res2.text)[i]
            comment = sc.select('p')[i].text.strip()
            # #print('--------')
            # print(stars)
            # #print('--------')
            # print(commor)
            # #print('--------')
            # print(comment)
            # #print('--------')
            f.write(commor + ",")
            f.write(stars + ",")
            f.write(comment)
            f.write("\n")
    f.close()
if __name__ == "__main__":
    if os.path.exists("F:\\SpiderDB") == False:
        os.mkdir("F:\\SpiderDB")
    if (os.path.exists("F:\\SpiderDB\\movie.txt") and os.path.exists("F:\\SpiderDB\\comment.txt")) == True:
        os.remove("F:\\SpiderDB\\movie.txt")
        os.remove("F:\\SpiderDB\\comment.txt")
    movie_url = 'https://movie.douban.com/subject/26861685/?from=showing'
    get_movie_comment(movie_url)
    print('连接数据库：')
    connect = pymysql.connect(  # 连接数据库
        "localhost", "root", "******", "mysql", charset='utf8')
    print('连接成功！')
    con = connect.cursor()
    con.execute("drop database DouB")
    con.execute("create database DouB CHARACTER SET utf8 COLLATE utf8_general_ci")
    con.execute("use DouB")
    con.execute("drop table if exists movie")
    sql1 = """create table movie(id  int (4) primary key not null  auto_increment,
					movie_name VARCHAR(40) NOT NULL,
					director VARCHAR(40) NOT NULL,
					editor VARCHAR(40) NOT NULL,
					actor VARCHAR(40) NOT NULL,
					style VARCHAR(40) NOT NULL,
					time VARCHAR(40) NOT NULL,
					comment_url VARCHAR(100),
                    good_eval VARCHAR(10) NOT NULL,
                    common_eval VARCHAR(10) NOT NULL,
                    bad_eval VARCHAR(10) NOT NULL           
					)ENGINE=InnoDB DEFAULT CHARSET=utf8;"""
    con.execute(sql1)

    con.execute("drop table if exists comment_info")
    sql2 = """create table comment_info(id  int (4) primary key not null  auto_increment,
    				commor VARCHAR(40) NOT NULL,
                    stars INT(4) NOT NULL,
                    comment VARCHAR(200)
                    )ENGINE=InnoDB DEFAULT CHARSET=utf8;"""
    con.execute(sql2)
    f = open("F:\\SpiderDB\\movie.txt", "r", encoding='utf-8')
    while True:
        line = f.readline()
        if line:
            line = line.strip("\n")
            line = line.split(",")
            #print(line)
            movie_name = line[0]
            director = line[1]
            editor = line[2]
            actor = line[3]
            style = line[4]
            time = line[5]
            comment_url = line[6]
            good_eval = line[7]
            common_eval = line[8]
            bad_eval = line[9]
            con.execute("insert into movie(movie_name,director,editor,actor,style,time,comment_url,good_eval,common_eval,bad_eval)VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)",
                        [movie_name,director,editor,actor,style,time,comment_url,good_eval,common_eval,bad_eval])
        else:
            break
        connect.commit()
    f.close()

    f = open("F:\\SpiderDB\\comment.txt", "r", encoding='utf-8')
    while True:
        # # 跳过第一行
        # for line in islice(f, 1, None):
        line = f.readline()
        if line:
            line = line.strip("\n")
            line = line.split(",")
            #print(line)
            commor = line[0]
            stars = line[1]
            comment = line[2]
            con.execute("insert into comment_info(commor,stars,comment)VALUES (%s,%s,%s)",
                        [commor,stars,comment])
        else:
            break
        connect.commit()
    con.close()
    connect.close()
    f.close()





