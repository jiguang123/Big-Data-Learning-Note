'''
今日主题：python抓取电影天堂最新电影迅雷下载地址链接信息
所用模块：requests bs4 pandas数据分析
 '''
import requests
import re
import pandas as pd 

url = 'https://www.dy2018.com/html/gndy/dyzz/index.html'

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36'
}

items_list = []

html = requests.get(url,headers=headers)
html.encoding = 'gb2312'
data = re.findall('<a href="(.*?)" class="ulink" title="(.*?)>.*?</a>',html.text)
for i in data:
	url_1 = 'https://www.dy2018.com/'+str(i[0])
	#print(i)
	#print(url_1)
	html_1= requests.get(url_1,headers=headers)
	html_1.encoding = 'gb2312'
	data_1 = re.findall('<a href="(.*?)">.*?</a></td>',html_1.text)
	#print(data_1[0])	
	list_1 = [i[1], url_1, data_1[0]]

	# list_1 = [url_1]

	items_list.append(list_1)
	#print (list_1)

#print ('==========================================================================================================')

for m  in range(2, 298):
	url_2 = 'https://www.dy2018.com/html/gndy/dyzz/index_'+str(m)+'.html'
	print(url_2)
	html_2 = requests.get(url_2,headers=headers)
	html_2.encoding = 'gb2312'
	data_2 = re.findall('<a href="(.*?)" class="ulink" title="(.*?)>.*?</a>',html_2.text)
	for n in data_2:
		url_3 = 'https://www.dy2018.com/'+str(n[0])
		#print(n)
		#print(url_3)
		html_3= requests.get(url_3,headers=headers)
		html_3.encoding = 'gb2312'
		data_3 = re.findall('<a href="(.*?)">.*?</a></td>',html_3.text)
		#print(data_3[0])
		if len(data_3) < 1:
			continue
		list_2 = [n[1], url_3, data_3[0]]
		# list_2 = [url_3]
		

		items_list.append(list_2)
		#print (list_2)	
	#print ('=====================================================================================================')

df = pd.DataFrame(items_list, columns = ['电影名称','电影网址链接','电影迅雷下载链接'])

df.to_csv('dytt.csv')