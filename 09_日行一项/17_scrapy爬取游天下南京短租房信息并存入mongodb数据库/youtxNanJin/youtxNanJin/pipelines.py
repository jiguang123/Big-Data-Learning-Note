# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html
import json
from scrapy.conf import settings
import pymongo


class YoutxnanjinPipeline(object):
    def process_item(self, item, spider):
        return item


class YouTXMongo(object):
    def __init__(self):
        self.client = pymongo.MongoClient(host=settings['MONGO_HOST'], port=settings['MONGO_PORT'])
        self.db = self.client[settings['MONGO_DB']]
        self.post = self.db[settings['MONGO_COLL']]

    def process_item(self, item, spider):
        postItem = dict(item)
        self.post.insert(postItem)
        return item

# 写入json文件
class JsonWritePipline(object):
    def __init__(self):
        self.file = open('游天下南京.json','w',encoding='utf-8')

    def process_item(self,item,spider):
        line  = json.dumps(dict(item),ensure_ascii=False)+"\n"
        self.file.write(line)
        return item

    def spider_closed(self,spider):
        self.file.close()