# -*- coding: utf-8 -*-

#爬虫爬取豆瓣书目录
import requests
from bs4 import BeautifulSoup
import json
import pandas #该库用于对爬取的信息进行表格性操作
from skimage import io#该库用于打印爬取到的照片

url = 'https://market.douban.com/book/?utm_campaign=book_nav_freyr&utm_source=douban&utm_medium=pc_web&page={}&page_num=18'

#该函数式用来返回一个列表存放含有书籍信息的字典
def bookList(url): 
    newurl = requests.get(url)
    soup = BeautifulSoup(newurl.text,'html.parser')
    result_total = []
    for book in soup.select('.book-item'):
        if len(book.select('.book-brief'))>0:

            bookimag2 = io.imread(book.select('img')[1]['src'])#书的图片
            io.imshow(bookimag2)
            #io.show()#为了使爬取到的图片显示出来

            bookurl = book.select('a')[0]['href']#抓取书的链接url
            #print('链接:   ',bookurl)

            result_total.append(booktextscore(bookurl))#将所抓取书的信息字典添加到列表里面

            bookimag1 = io.imread(book.select('img')[0]['src'])#背景图片
            io.imshow(bookimag1)
            #io.show()
    return result_total #返回一个列


#该函数式用来爬取书籍的名字，评分，评价人数以及书的简单介绍
def booktextscore(url):
    booktexturl = requests.get(url)
    soup = BeautifulSoup(booktexturl.text,'html.parser')
    result = {}#创建一个字典将相关书籍信息存入到字典中
    bookname = soup.select('.book-breintro h3')[0].text
    bookname2 = '《' + bookname + '》'
    print(bookname2)
    result['书籍名称'] = bookname2

    bookauthor = soup.select('.book-public')[0].text.lstrip('\n          ').rstrip('\n        ')
    result['作者'] = bookauthor
    print(bookauthor)

    print(url)
    result['书籍链接'] = url

    score = soup.select('.total-score')[0].text#爬取该书评分，其中可能含有有些书籍由于评论人数不足导致没有评分，加一个判断默认该种情况成评分为0
    if score == '评价人数不足':
        score = 0
    score = float(score)
    result['书籍评分'] = float(score)#将评分强制转换成float类型的
    print('评分:',score)

    commentnum = soup.select('.comment-number')[0].text#爬取本书评论人数
    print(commentnum)
    print('该书简介:\n')
    result['书籍评论人数'] = commentnum 

    article = []#添加一个列表
    for ench in soup.select('.layout-content'):#爬取的是图书详情
        for p in ench.select('.paragraph-content  p')[:-1]:
            article.append(p.text.strip())#将p标签中的文字添加到列表中
        articlebook = '\n '.join(article)
        #print(articlebook)
    #result['书籍简介'] = articlebook 
    return result



book_total = []
#由于书籍信息有两页，所以加一个循环将两页书籍信息都添加进列表中方便生成表格
for ench in range(1,4):
    newurl = url.format(ench)#通过format将URL地址实现可变性，可以将两页书籍信息都打印出来
    book_result = bookList(newurl)
    book_total.extend(book_result)

df = pandas.DataFrame(book_total)
df.to_csv('books.csv')#将爬取后的书籍信息通过pandas转换成表格形式

