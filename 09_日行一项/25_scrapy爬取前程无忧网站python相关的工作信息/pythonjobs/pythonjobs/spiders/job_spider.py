# -*- coding: utf-8 -*-
import scrapy
from pythonjobs.items import PythonjobsItem
#from bs4 import BeautifulSoup

class JobspiderSpider(scrapy.Spider):
    name = 'jobSpider'
    allowed_domains = ['search.51job.com','jobs.51job.com']

    def start_requests(self):
        for i in range(1,20):              # Set pages to crawl here.
            url = "http://search.51job.com/list/000000,000000,0000,00,9,99,python,2,{0}.html".format(i)
            yield scrapy.Request(url)

    def parse(self, response):
        for sel in response.css("html body div.dw_wp div#resultList.dw_table div.el p.t1 span a"):
            url  = sel.re('href="(.*?)"')[0]
            yield scrapy.Request(url,callback=self.parse_item)

    def parse_item(self, response):
        item = PythonjobsItem()
        item['title'] = response.xpath('//div[@class="cn"]/h1/@title').extract()[0]
        item['url'] = response.url
        item['city'] = response.xpath('//span[@class="lname"]/text()').extract()[0]
        item['company'] = response.xpath('//p[@class="cname"]/a/@title').extract()[0]
        item['location'] = response.xpath('//p[@class="fp"]/text()').extract()[1].rstrip()
        return item