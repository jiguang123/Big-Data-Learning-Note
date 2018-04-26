# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html
from findtrip.spiders.washctrip import wash
import pymongo
from scrapy.conf import settings
from scrapy import log

class FindtripPipeline(object):
    def process_item(self, item, spider):
        return item


class MongoDBPipeline(object):
    def __init__(self):
        self.client = pymongo.MongoClient(host=settings['MONGO_HOST'], port=settings['MONGO_PORT'])
        self.db = self.client[settings['MONGO_DB']]
        self.post = self.db[settings['MONGO_COLL']]

    def process_item(self, item, spider):
        if item['site'] == 'Qua':
            if item['company']:
                item['company'] = wash(item['company'])
            if item['flight_time']:
                item['flight_time'] = wash(item['flight_time'])
            if item['airports']:
                item['airports'] = wash(item['airports'])
            if item['passtime']:
                item['passtime'] = wash(item['passtime'])
            if item['price']:
                item['price'] = wash(item['price'])        
            for data in item:
                if not data:
                    raise DropItem("Missing data!")
            self.collection.insert(dict(item))
            log.msg("Question added to MongoDB database!",
                    level=log.DEBUG, spider=spider)
        elif item['site'] == 'Ctrip':
            self.collection.insert(dict(item))
            log.msg("Question added to MongoDB database!",
                    level=log.DEBUG, spider=spider)

        return item