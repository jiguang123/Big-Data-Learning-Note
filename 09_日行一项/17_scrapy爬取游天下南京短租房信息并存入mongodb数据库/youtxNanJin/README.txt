输入：scrapy crawl youtx -o items.json 时以json格式保存下载数据
输入：scrapy crawl youtx -o items.csv 时以csv格式保存下载数据


Scrapy必须背下来的命令：
1 创建项目： scrapy startproject youtxNanJin
			startproject: 表示创建项目
			youtxNanJin： 表示创建的项目名

2 创建爬虫： scrapy genspider youtx "http://www.youtx.com"
			genspider： 表示生成一个爬虫（默认是scrapy.Spider类）
			youtx： 表示爬虫名（对应爬虫代码里的 name 参数）
			"http://www.youtx.com"： 表示允许爬虫爬取的域范围

3 执行爬虫： scrapy crawl youtx
			crawl: 表示启动一个sc	rapy爬虫
			youtx: 表示需要启动的爬虫名（对应爬虫代码里的 name 参数）