import scrapy
from doubanmovie.items import DoubanmovieItem

class Movie(scrapy.Spider):
    # 爬虫唯一标识符
    name = 'doubanMovie'
    # 爬取域名
    allowed_domain = ['movie.douban.com']
    # 爬取页面地址
    start_urls = ['https://movie.douban.com/top250']

    def parse(self, response):
        selector = scrapy.Selector(response)
        # 解析出各个电影
        movies = selector.xpath('//div[@class="item"]')
        # 存放电影信息
        item = DoubanmovieItem()

        for movie in movies:

            # 电影各种语言名字的列表
            titles = movie.xpath('.//span[@class="title"]/text()').extract()
            # 将中文名与英文名合成一个字符串
            name = ''
            for title in titles:
                name += title.strip()
            item['name'] = name

            # 电影信息列表
            infos = movie.xpath('.//div[@class="bd"]/p/text()').extract()
            # 电影信息合成一个字符串
            fullInfo = ''
            for info in infos:
                fullInfo += info.strip()
            item['info'] = fullInfo
            # 提取评分信息
            item['rating'] = movie.xpath('.//span[@class="rating_num"]/text()').extract()[0].strip()
            # 提取评价人数
            item['num'] = movie.xpath('.//div[@class="star"]/span[last()]/text()').extract()[0].strip()[:-3]
            # 提取经典语句，quote可能为空
            quote = movie.xpath('.//span[@class="inq"]/text()').extract()
            if quote:
                quote = quote[0].strip()
            item['quote'] = quote
            # 提取电影图片
            item['img_url'] = movie.xpath('.//img/@src').extract()[0]

            yield item

        next_page = selector.xpath('//span[@class="next"]/a/@href').extract()[0]
        url = 'https://movie.douban.com/top250' + next_page
        if next_page:
            yield scrapy.Request(url, callback=self.parse)

