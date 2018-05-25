#!/usr/bin/python
#-*- coding: utf-8 -*-
'''
今日主题：python抓取斗破苍穹最新章节标题信息
所用模块：requests re bs4 pandas数据分析
'''
import requests
import re
import pandas as pd 
from bs4 import BeautifulSoup #分析网页 获取标签内容

url = 'https://www.miaobige.com/read/68/'

headers = {'user-agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36'}

items_list = []

html = requests.get(url, headers=headers)
# html.encoding = 'gb2312'
soup = BeautifulSoup(html.text,'html.parser')
title = soup.find('div', id='readerlists')
datas = re.findall('<li><a href="(.*?)">(.*?)</a></li>',title.text)
for data in datas:
	url_1 = 'https://www.miaobige.com/' + data[0]
	print (data)
	item_list = [url_1, data[1]]
	items_list.append(item_list)

df = pd.DataFrame(items_list, columns = ['链接','章节主题'])
df.to_csv('斗破苍穹小说.csv')