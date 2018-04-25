# -*- coding: utf-8 -*-

import re
import time

from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.action_chains import ActionChains

from bs4 import BeautifulSoup

import pymongo

# 多进程
from multiprocessing import Pool

# 1 打开数据库连接，mongodb默认端口为27017
conn = pymongo.MongoClient(host='localhost',port=27017)
# 2 选择或创建数据库
jobdata = conn['baidujobs']
# 3 选择或创建数据集合
ver_job = jobdata['verjob']

baidu_baseurl = 'http://zhaopin.baidu.com/quanzhi?tid=4139&ie=utf8&oe=utf8&query=python%E6%9D%AD%E5%B7%9E&city_sug=%E6%9D%AD%E5%B7%9E'
def set_winscroll(driver):
    time.sleep(2)
    driver.execute_script('window.scrollBy(0,2000)')
    time.sleep(3)
    driver.execute_script('window.scrollBy(0,3000)')
    time.sleep(3)


# 1 初始化driver
driver = webdriver.PhantomJS()
# 2 调用get方法
driver.get(baidu_baseurl)
# 3 进入网页
set_winscroll(driver)

# 4 获取资源（第一页的数据）
we_data = driver.page_source
# print('first_we_data ' + we_data)


def parse_html(html):
    soup = BeautifulSoup(html, 'lxml')
    item_url = soup.findAll('a', {'class': 'clearfix item line-bottom'})
    # for item in zip(item_url):
    #     print(item.get('href'))

    # 职位信息
    jobs = soup.findAll('div', {'class': 'title-h3 line-clamp1'})
    # for job in jobs:
    # print(job.string) # 职位信息
    # 地址 + 公司名
    compy = soup.findAll('p', {'class': 'area line-clamp1'})
    # for com in compy:
    #     print(com.string)

    # 薪资
    salarys = soup.findAll('p', {'class': 'salary'})
    # for salary in salarys:
    #     print(salary.string)
    # 发布时间跟发布来源网站
    addresss = soup.findAll('div', {'class': 'right time'})
    # print(addresss)
    reg = r'<p>(.*?)</p>'
    regx = re.compile(reg)
    ads = re.findall(regx, str(addresss))
    # print(ads)
    # for adds in ads:
    #     data = adds.split('|')
    #     print(data)
    for itm_url, job_detail, ver_compny, ver_salary, ver_addres in zip(item_url, jobs, compy, salarys, ads):
        data = {
            'itme_url': 'http://zhaopin.baidu.com'+itm_url.get('href'),
            'job_detail': job_detail.string,
            'ver_compny': str(ver_compny.string),
            'ver_salary': ver_salary.string,
            'ver_addres': str(ver_addres).split('|'),
        }
        print(data)
        # 插入数据库
        ver_job.insert_one(data) # 插入数据库失败
        f.write(str(data))


def get_page_source(page_num):
    time.sleep(2)
    driver.find_element_by_xpath('//*[@id="pagination"]/p/span/a[%s]' % page_num).click()
    # //*[@id="pagination"]/p/span/a[1]  为在第一页的按钮
    # //*[@id="pagination"]/p/span/a[2]  为第二页的按钮
    set_winscroll(driver)
    we_data = driver.page_source
    return we_data

f = open('百度招聘前30页杭州.csv', 'a',encoding='utf-8')
# 首页的数据
def getBaiduHangZhouJob(we_data):
    parse_html(we_data)
    for i in range(1, 50):
        if i==1:
            we_data = get_page_source(1)
            parse_html(we_data)
        elif i<=5:
            we_data = get_page_source(str(2))
            parse_html(we_data)
        else:
            we_data = get_page_source(str(3))
            parse_html(we_data)
    f.close()


if __name__ == '__main__':
    getBaiduHangZhouJob(we_data)
    # pool = Pool(processes=10)
    # pool.map_async(getBaiduHangZhouJob(we_data))
    # pool.close()
    # f.close()