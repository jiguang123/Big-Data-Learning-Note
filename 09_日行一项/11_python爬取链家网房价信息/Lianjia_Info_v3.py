# -*- coding:utf-8 -*-
import requests
from requests.exceptions import RequestException
from bs4 import BeautifulSoup
from time import sleep
import csv


def write_to_file(content):
    with open('lianjia_bs4.csv', 'w') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerows(content)
        csvfile.close()


def get_one_page(url):
    try:
        response = requests.get(url)
        if response.status_code == 200:
            return response.text
        else:
            return None
    except RequestException:
        return None


def parse_one_page(html):
    soup = BeautifulSoup(html, 'lxml')
    prefix = 'http://sh.lianjia.com'
    for item in soup.select('.info-panel'):
        houseUrl = prefix + item.find("h2").a["href"]
        title = item.find("h2").a["title"]
        spans = item.find(class_="where").find_all("span")
        xiaoqu, huxing, mianji = spans[0].string, spans[1].string.split('\xa0')[0], spans[2].string.split('\xa0')[0]
        cons = item.find(class_="con").find_all("a")
        area, sub_area = cons[0].string, cons[1].string
        subway = item.find(class_="fang-subway-ex").string
        price = item.find(class_="price").find(class_="num").string
        data = item.find(class_="price-pre").string.split('\n')[0]
        watched = item.find(class_="square").find(class_="num").string

        yield [houseUrl, title, xiaoqu, huxing, mianji, area, sub_area, subway, price, data, watched]


if __name__ == '__main__':
    results = []
    for page in range(100):
        sleep(1)
        print (page)
        url = 'http://sh.lianjia.com/zufang/d' + str(page)
        html = get_one_page(url)
        for item in parse_one_page(html):
            results.append(item)
    write_to_file(results)