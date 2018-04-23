# -*- coding:utf-8 -*-
import requests
from requests.exceptions import RequestException
from time import sleep
import re
import csv


def write_to_file(content):
    with open('lianjia_re_v4.csv', 'w') as csvfile:
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
    pattern = re.compile('<h2>.*?"\shref="(.*?)".*?title="(.*?)".*?</a>.*?<span>(.*?)&nb.*?<span>' +
                         '(.*?)&nb.*?/">(.*?)</a>.*?/">(.*?)</a>.*?</span>(.*?)<.*?-ex"><span>(.*?)<' +
                         '.*?-ex"><span>(.*?)</span>.*?num">(\d+)<.*?-pre">(.*?)<.*?num">(\d+)<.*?</li>', re.S)
    prefix = 'http://sh.lianjia.com'
    items = re.findall(pattern, html)
    for item in items:
        item = list(item)
        item[0] = prefix + item[0]
        item[6] = item[6].strip()
        item[10] = item[10].split('\n')[0]
        yield item


def main(page, results):
    url = 'http://sh.lianjia.com/zufang/d' + str(page)
    html = get_one_page(url)
    for item in parse_one_page(html):
        results.append(item)


if __name__ == '__main__':
    results = []
    for i in range(100):
        sleep(1)
        print(i)
        main(i+1, results)
    write_to_file(results)