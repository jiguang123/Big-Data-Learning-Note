# encoding=utf8
import scrapy
from makedream.items import MakedreamItem


class DramingNet(scrapy.Spider):
    # 启动爬虫的名称
    name = 'dreaming'
    # 爬虫的域范围
    allowed_domains = ['zhimengzhe.com']
    # 爬虫的第一个url
    start_urls = ['http://www.zhimengzhe.com/bianchengjiaocheng/qitabiancheng/index_{}.html'.format(n) for n in
                  range(0, 1466)]

    # 爬取结果解析
    def parse(self, response):
        base_url = 'http://www.zhimengzhe.com'
        # print(response.body)
        node_list = response.xpath("//ul[@class='list-unstyled list-article']/li")
        for node in node_list:
            item = MakedreamItem()
            nextNode = node.xpath("./div[@class='pull-left ltxt w658']")
            print('*' * 30)
            title = nextNode.xpath('./h3/a/text()').extract()
            link = nextNode.xpath('./h3/a/@href').extract()
            desc = nextNode.xpath('./p/text()').extract()

            # 创建时间，类型，标签
            publicTime = nextNode.xpath("./div[@class='tagtime']/span[1]/text()").extract()
            publicType = nextNode.xpath("./div[@class='tagtime']/span[2]/a/text()").extract()
            publicTag = nextNode.xpath("./div[@class='tagtime']/span[3]/a/text()").extract()
            # node
            titleLink = base_url + ''.join(link)
            item['articleTitle'] = title
            # 文章标题url
            item['articleUrl'] = titleLink
            # 文章描述
            item['articleDesc'] = desc
            # 文章发布时间
            item['articlePublic'] = publicTime
            # 文章类型
            item['articleType'] = publicType
            # 文章标签
            item['articleTag'] = publicTag
            yield item