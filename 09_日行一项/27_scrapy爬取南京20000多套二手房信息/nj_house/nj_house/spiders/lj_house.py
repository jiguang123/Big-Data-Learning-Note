# -*- coding: utf-8 -*-
import re
import scrapy
from nj_house.items import NjHouseItem

class LjHouseSpider(scrapy.Spider):
    name = "lj_house"
    allowed_domains = ["nj.lianjia.com/ershoufang/"]
    start_urls = ['http://nj.lianjia.com/ershoufang//']

    def parse(self, response):
        clears = response.css('.sellListContent li')
        item = NjHouseItem()
        for c in clears:       	
        		house = c.css('.houseInfo a::text').extract_first()
        		house_text = c.css('.houseInfo::text').extract_first()
        		house_info_list = [e for e in re.split('\|', int(house_text)) if len(e) > 1]
        		house_room = house_info_list[0].strip()
        		house_area = ''.join(re.findall(r'[\d+\.]', house_info_list[1]))
        		total_price = c.css('.totalPrice span::text').extract_first()
        		unit_price = c.css('.unitPrice span::text').extract_first()
        		unit_price = re.findall('\d+', unit_price)[0]

        		item['house'] = house
        		item['total_price'] = float(total_price)
        		item['unit_price'] = int(unit_price)
        		item['house_area'] = float(house_area)
        		item['house_room'] = house_room
        		yield item

        page_info = response.css('div[class="page-box fr"]').css('div::attr(page-data)').extract_first()
        page_list = re.findall('\d+', page_info)
        next_page = 'pg' + str(int(page_list[1]) + 1)
        url = self.start_urls[0] + next_page
        if next_page:
            yield Request(url=url, callback=self.parse)
