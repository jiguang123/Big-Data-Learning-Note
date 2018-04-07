#!/usr/bin/python  
# -*- encoding:utf-8 -*-  
  
""" 
@author : Tom
@file : douban_movie 
@time : 2018/4/6 23:04 
@description :  
 
"""  

import requests  
import re  
from bs4 import BeautifulSoup  
import csv  
  
  
# 先创建一个csv文件，写好头部  
with open("douban_top250_movies.csv", 'w') as filed:  # a+为添加，w为擦除重写  
    csv_writer = csv.DictWriter(filed, [  
        u'片名',  
        u'评分',  
        u'评分人数',  
        u'一句话描述',  
        u'豆瓣链接',  
    ])  
    csv_writer.writeheader()  
  
  
def get_mov_info(response):  
    mov_info = {}  
    soup = BeautifulSoup(response.text, "lxml")  
    movies = soup.find_all('div', class_="info")  
  
    for info in movies:  
        # 获得电影的中文名  
        mov_info['mov_name'] = info.find('span', class_='title').text  # find()只找到一个，结果以树结构返回  
  
        # 获得电影在豆瓣中的链接  
        mov_info['mov_link'] = info.find('a').get('href')  
  
        # 找到评分以及评价人数  
        rating_num = info.find(class_='rating_num')  
        mov_info['rating_score'] = rating_num.text  
        comment = rating_num.find_next_sibling().find_next_sibling()  
        # 对评价字段切分  
        comment_num = re.findall('\d{0,}', comment.text)  
        mov_info['comment_nums'] = comment_num[0]    # 正则匹配re中没有find()，findall()以列表形式返回结果  
  
        # 获得一句话评价  
        comment_one = info.find('span', class_='inq')  
        if comment_one is None:  
            mov_info['inq_comment'] = u' '  
        else:  
            mov_info['inq_comment'] = comment_one.text  
        print (mov_info) 
  
        # 一条条存入csv文件  
        write_csv(mov_info)  
  
  
def write_csv(info_dict):  
    with open("douban_top250_movies.csv", 'a+') as f:  
        csv_write = csv.DictWriter(f, [  
            u'片名',  
            u'评分',  
            u'评分人数',  
            u'一句话描述',  
            u'豆瓣链接',  
        ])  
        csv_write.writerow({                   # writerow()写入单行，writerows写入多行，这里只有一行数据，用writerows报错  
            u'片名': info_dict['mov_name'],  
            u'评分': info_dict['rating_score'],  
            u'评分人数': info_dict['comment_nums'],  
            u'一句话描述': info_dict['inq_comment'],  
            u'豆瓣链接': info_dict['mov_link']  
        })  
  
for num in range(0, 10):  
    page = num * 25  
    response = requests.get("https://movie.douban.com/top250?start=%d&filter=" % page)   
    get_mov_info(response)