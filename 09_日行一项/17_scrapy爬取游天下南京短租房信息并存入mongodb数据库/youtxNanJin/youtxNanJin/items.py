# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class YoutxnanjinItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    # pass
    
	# 房源名称
    homeName = scrapy.Field()
    # 房源链接
    homeLine = scrapy.Field()
    # 房租单价
    homeSinglePrice = scrapy.Field()
    # 房租地址
    homeAddress = scrapy.Field()
    # 房租近期信息
    homeDetai = scrapy.Field()
    # 满七天价格
    homeSeven = scrapy.Field()
    # 满30天价格
    homeThirth = scrapy.Field()

    # 房东
    homePerson = scrapy.Field()
    # 房东头像
    homePersonImg = scrapy.Field()
    # 房东头像链接
    homePersonLink = scrapy.Field()

    # 房子大图
    homePicBg = scrapy.Field()
    # 房子大图链接
    homePicLink = scrapy.Field()

    # 品牌店铺信息
    # homePinPai = scrapy.Field()
    # 明星房东
    # homeStarrPerson = scrapy.Field()

