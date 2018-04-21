'''
今日主题：python抓取斗罗大陆最新章节标题信息
所用模块：requests re bs4 pandas数据分析
 '''
import requests
import re
import pandas as pd 
from bs4 import BeautifulSoup #分析网页 获取标签内容

url = 'https://www.freexs.org/novel/0/896/index.html'

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36'
}

items_list = []

html = requests.get(url,headers=headers)
html.encoding = 'gb2312'

data = re.findall('<dd><a href="(.*?)">(.*?)</a></dd>',html.text)
for i in data:
	url_1 = 'https://www.freexs.org/novel/0/896/'+str(i[0])
	print (i[1])
	print (url_1)
	list = [url_1, i[1]]
	items_list.append(list)


	# html_1 = requests.get(url_1,headers=headers)
	# html_1.encoding = 'gb2312'
	# soup = BeautifulSoup(html_1.text,'lxml')
	# title = soup.find('div', class_='readout').text #标题
	# print (title)

df = pd.DataFrame(items_list, columns = ['链接','章节主题'])
df.to_csv('斗罗大陆小说.csv')