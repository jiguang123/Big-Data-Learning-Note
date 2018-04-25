# -*- coding: utf-8 -*-
# @Time    : 2018/4/25 11:15
# @File    : test_douban_qianren3.py（再见前任3的影评）

import csv
import requests
from lxml import etree
import time


url = 'https://movie.douban.com/subject/26662193/comments?start=0&limit=20&sort=new_score&status=P&percent_type='

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/57.0.2987.110 Safari/537.36',
    'Cookie': 'gr_user_id=ffdf2f63-ec37-49b5-99e8-0e0d28741172; bid=qh9RXgIGopg; viewed="26826540_24703171"; ap=1; ll="118172"; ct=y; _vwo_uuid_v2=8C5B24903B1D1D3886FE478B91C5DE97|7eac18658e7fecbbf3798b88cfcf6113; _pk_ref.100001.4cf6=%5B%22%22%2C%22%22%2C1522129522%2C%22https%3A%2F%2Fwww.baidu.com%2Flink%3Furl%3DdnHqCRiT1HlhToCp0h1cpdyV8rB9f_OfOvJhjRPO3p1jrl764LGvi7gbYSdskDMh%26wd%3D%26eqid%3De15db1bb0000e3cd000000045ab9b6fe%22%5D; _pk_id.100001.4cf6=4e61f4192b9486a8.1485672092.10.1522130672.1522120744.; _pk_ses.100001.4cf6=*'}


def get_html(current_url):
    time.sleep(2)
    r = requests.get(current_url, headers=headers)
    r.raise_for_status()
    return etree.HTML(r.text)


def parse_html(content,writer):
    links = content.xpath("//*[@class='comment-item']")
    for link in links:
        content = link.xpath("./div[@class='comment']/p/text()")[0].strip()
        author = link.xpath("./div[@class='comment']/h3/span[@class='comment-info']/a/text()")[0].strip()
        time = link.xpath("./div[@class='comment']/h3/span[@class='comment-info']/span[@class='comment-time ']/text()")[
            0].strip()
        is_useful = link.xpath("./div[@class='comment']/h3/span[@class='comment-vote']/span[@class='votes']/text()")[0]
        print('content：', content)
        print('time：', time)
        print('is_useful：', is_useful)
        # detail = (author, time, is_useful, content)
        detail = (is_useful,content)
        writer.writerow(detail)


if __name__ == '__main__':
    with open('douban.txt', 'a+', encoding='utf-8', newline='') as csvf:
        writer = csv.writer(csvf)
        writer.writerow(('作者', '时间', '有用数', '内容'))
        for page in range(0, 260, 20):
            url = 'https://movie.douban.com/subject/26662193/comments?start={}&limit=20&sort=new_score&status=P&percent_type='.format(
                page)
            r = get_html(url)
            parse_html(r,writer)