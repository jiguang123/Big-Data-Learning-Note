# -*- coding: utf-8 -*-

import requests
import re
# 导入mongo 数据库
import pymongo
import json

# 打开数据库连接，mongodb默认端口为27017
conn = pymongo.MongoClient(host='localhost',port=27017)
# 选择或创建数据库
toutiao = conn['toutiao']
# 选择或者创建数据集合
newsdata = toutiao['news']

toutiaoUrl = 'http://www.toutiao.com/api/pc/focus/'
reqData = requests.get(toutiaoUrl).text
print(reqData)

jsonData = json.loads(reqData)
newsData = jsonData['data']['pc_feed_focus']

# 存储到数据库
for new in newsData:
    title = new['title']
    img_url = new['image_url']
    url = new['media_url']
    data = {
        'title':title,
        'img_url':img_url,
        'url':url
    }
    # 插入一行数据
    newsdata.insert_one(data)

for i in newsdata.find():
    # 从数据库中读取出来
    print('i'+str(i))