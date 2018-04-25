#encoding=utf8
import scrapy
from youtxNanJin.items import YoutxnanjinItem

class NanJinDefault(scrapy.Spider):
    name = 'youtx'
    allowed_domains = ['youtx.com']
    start_urls = ["http://www.youtx.com/nanjing/longrent1-page{}".format(n) for n in range(0,6)]
    def parse(self, response):
        # print(response.body)
        node_list = response.xpath("//div[@class='duanzu houseList']/ul/li[@class='clearfix']")
        # print(node_list)
        for node in node_list:
            item = YoutxnanjinItem()
            homeName = node.xpath("./div[@class='houseInfo clearfix']/div[@class='house-tit clearfix']/h3/a/text()").extract()
            homeLink = node.xpath("./div[@class='houseInfo clearfix']/div[@class='house-tit clearfix']/h3/a/@href").extract()
            print(homeName)
            print(homeLink)

            # 单日价格
            homeSinglePrice = node.xpath("./div[@class='houseInfo clearfix']/div[@class='house-tit clearfix']/div[@class='house-price mt9']/span/span[@class='housePrice']/text()").extract()
            print(homeSinglePrice)

            # 获取房源地址
            homeAddress = node.xpath("./div[@class='houseInfo clearfix']/div[@class='houseInfo-left mt2']/p[@class='clearfix mt5']/text()").extract()
            # 房租信息
            homeDesc =node.xpath("./div[@class='houseInfo clearfix']/div[@class='houseInfo-left mt2']/p[@class='mt5']/text()").extract()
            homeDesc2 =node.xpath("./div[@class='houseInfo clearfix']/div[@class='houseInfo-left mt2']/p[@class='mt5']/span[2]/text()").extract()
            print(homeAddress)
            print(homeDesc)
            print(homeDesc2)

            # 满30天的信息
            homeThrty = node.xpath("./div[@class='houseInfo clearfix']/div[@class='house-tit clearfix']/div[@class='house-price mt9']/div[@class='mix12_5']/div[@class='discount']/div[@class='discount-price']/span//text()").extract()
            print(homeThrty)
            # 房东信息
            homePerson = node.xpath("./div[@class='houseInfo clearfix']/div[@class='agentInfo mt16']/p[1]/a/text()").extract()
            # 房东链接
            homePersonLink = node.xpath("./div[@class='houseInfo clearfix']/div[@class='agentInfo mt16']/p[1]/a/@href").extract()
            print(homePerson)
            print(homePersonLink)

            # 房源大图图片
            homeBigPic = node.xpath("./div[@class='house-img']/a[1]/img/@src").extract()
            homeBigPicLink = node.xpath("./div[@class='house-img']/a[1]/@href").extract()
            print(homeBigPic)
            print(homeBigPicLink)
            # 房东头像信息
            personPic = node.xpath("./div[@class='house-img']/a[2]/img/@src").extract()
            # 房东头像链接地址
            personPicLink = node.xpath("./div[@class='house-img']/a[2]/img/@href").extract()

            print(personPic)
            print(homePersonLink)
            item['homeName'] ="".join(homeName)
            item['homeLine'] ="".join(homeLink)
            item['homeSinglePrice'] ="".join(homeSinglePrice)
            item['homeAddress'] ="".join(homeAddress)
            item['homeDetai'] ="".join(homeDesc)+"".join(homeDesc2)
            # 这里的值暂时没有取出来
            item['homeSeven'] ="".join(homeThrty)
            item['homeThirth'] ="".join(homeThrty)

            item['homePerson'] ="".join(homePerson)
            item['homePersonImg'] ="".join(personPic)
            item['homePersonLink'] ="".join(homePersonLink)
            item['homePicBg'] ="".join(homeBigPic)
            item['homePicLink'] ="".join(homeBigPicLink)
            yield item