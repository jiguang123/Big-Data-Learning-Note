'''
今日主题：python抓取美团网百万商家信息
所用模块：requests bs4 数据分析
流程分析：1、获取主页源码
          2、获取二级菜单链接（美食、电影。。。）
          3、商品店家信息
 '''
import requests
from bs4 import BeautifulSoup #分析网页 获取标签内容
import json
import lxml
import pandas as pd 

url = 'http://chs.meituan.com/'

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36'
}
  
#获取分类（电影、美食）
def get_start_links(url, headers=None):
    html = requests.get(url,headers=headers).text #发送请求获取主页文本
    soup = BeautifulSoup(html, 'lxml') #解析网页
    links = [link.find('div').find('div').find('dl').find('dt').find('a')['href'] for link in soup.find_all('div', class_='J-nav-item')]
    return links

#获取分类链接中的店铺id
def get_detail_id(url, headers=None):
    html = requests.get(url,headers=headers).text
    soup = BeautifulSoup(html,'lxml')
    content_id = json.loads(soup.find('div', class_='J-scrollloader cf J-hub')['data-async-params'])
    return json.loads(content_id.get('data')).get('poiidList') 

#获取店铺详情数据
def get_item_info(url, headers=None):
    html = requests.get(url,headers=headers).text
    soup = BeautifulSoup(html,'lxml')
    title = soup.find('span', class_='title').text #标题
    score = soup.find('span', class_='biz-level').get_text() #评分
    address = soup.find('span', class_='geo').text #地址
    phone = soup.find_all('p', class_='under-title')[1].get_text() #电话
    Evaluation_number = soup.find('a', class_='num rate-count').text #评价
    print (u'店名： '+title) 
    print (u'评论数量： '+Evaluation_number)
    print (u'地址： '+address)
    print (u'评分： '+score) 
    print (u'电话： '+phone)
    print ('======================================================')
    return (title, score, address, phone, Evaluation_number)


items_list = []
   
start_url_list = get_start_links(url)
for j in start_url_list:#分类链接
    for i in range(1,11): #多页
        category_url = j+'/all/page()'.format(i) #完整的分类多页链接
        shop_id_list = get_detail_id(category_url,headers=headers)
        print (shop_id_list)
        for shop_id in shop_id_list:
            items = get_item_info(url+'shop/{}'.format(shop_id),headers)
            items_list.append(items)

df = pd.DataFrame(items_list, columns = ['title','score','address','phone','Evaluation_number'])
df.to_csv('meituan.csv')