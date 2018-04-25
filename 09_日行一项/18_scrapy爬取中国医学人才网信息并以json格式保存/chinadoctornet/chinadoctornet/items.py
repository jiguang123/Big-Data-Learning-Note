# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class ChinadoctornetItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()

    # 爬取中国医学人才网的条目(共5个条目)
    # 医院名称
    hospitalName = scrapy.Field()
    # 医院规模
    hospitalSize = scrapy.Field()
    # 医院所在地
    hospitalAddress = scrapy.Field()
    # 医院科目
    hospitalDesc = scrapy.Field()
    # pass
