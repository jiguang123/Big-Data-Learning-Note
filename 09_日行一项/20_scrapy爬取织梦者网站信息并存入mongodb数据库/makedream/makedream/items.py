# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class MakedreamItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    # pass

    # 文章标题
    articleTitle = scrapy.Field()
    # 文章标题url
    articleUrl = scrapy.Field()
    # 文章描述
    articleDesc = scrapy.Field()
    # 文章发布时间
    articlePublic = scrapy.Field()
    # 文章类型
    articleType = scrapy.Field()
    # 文章标签
    articleTag = scrapy.Field()
