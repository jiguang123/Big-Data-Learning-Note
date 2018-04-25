# encoding=utf8
import scrapy
from chinadoctornet.items import ChinadoctornetItem


class ChinaDocNet(scrapy.Spider):
    # 启动爬虫的名称
    name = 'docNet'
    # 爬取域名的范围
    allowed_domains = ['yixuezp.com']
    # 爬虫第一个url地址
    start_urls = ['http://www.yixuezp.com/zhaopin?page={}'.format(n) for n in range(0, 464)]  # 463

    def parse(self, response):
        # 医院name
        node_list = response.xpath("//div[@class='newsjob']/ul/li")
        items = []
        for node in node_list:
            item = ChinadoctornetItem()
            hospitalName = node.xpath("./a/text()").extract()
            hospitalSize = node.xpath("./span[1]/text()").extract()
            hospitalAddress = node.xpath("./span[2]/text()").extract()
            hospitalDesc = node.xpath("./p/a/text()").extract()

            item['hospitalName'] = hospitalName
            item['hospitalSize'] = hospitalSize
            item['hospitalAddress'] = hospitalAddress
            item['hospitalDesc'] = hospitalDesc
            items.append(item)
            # return items # 如果直接return的话，一页数据只会返回一条数据
            yield item #用yield 的话，可以交给下载器，继续执行下一步操作。