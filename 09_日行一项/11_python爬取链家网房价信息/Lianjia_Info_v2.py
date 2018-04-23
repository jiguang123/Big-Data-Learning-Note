#coding=utf-8 
#爬取链家二手房信息  
import requests  
from bs4 import BeautifulSoup  
import csv  
  
def getHTMLText(url):  
    try:  
        r = requests.get(url,timeout=30)  
        r.raise_for_status()  
        r.encoding = r.apparent_encoding  
        return r.text  
    except:  
        return '产生异常'  
  
def get_data(list,html):  
    soup = BeautifulSoup(html,'html.parser')  
    infos = soup.find('ul',{'class':'sellListContent'}).find_all('li')  
    with open(r'lianjia.csv','a',encoding='utf-8') as f:  
        for info in infos:  
            name = info.find('div',{'class':'title'}).find('a').get_text()  
            price =info.find('div',{'class':'priceInfo'}).find('div',{'class','totalPrice'}).find('span').get_text()  
            f.write("{},{}\n".format(name,price))  
        
def main():  
    start_url = 'https://sh.lianjia.com/ershoufang/pg'  
    depth = 20  
    info_list =[]  
    for i in range(depth):  
        url = start_url + str(i)  
        html = getHTMLText(url)  
        get_data(info_list,html)  
main()  