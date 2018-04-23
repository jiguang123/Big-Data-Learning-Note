# !/usr/bin/python
# -*- coding:utf-8 -*-

import requests
import time
import random
import pandas as pd 


headers = {
    'Accept':'application/json, text/javascript, */*; q=0.01',
    'Accept-Encoding':'gzip, deflate, br',
    'Accept-Language':'zh-CN,zh;q=0.8',
    'Connection':'keep-alive',
    'Content-Length':'26',
    'Content-Type':'application/x-www-form-urlencoded; charset=UTF-8',
    'Cookie':'**Cookie值**',
    'Host':'www.lagou.com',
    'Origin':'https://www.lagou.com',
    'Referer':'https://www.lagou.com/jobs/list_python?labelWords=&fromSearch=true&suginput=',
    'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36',
    'X-Anit-Forge-Code':'0',
    'X-Anit-Forge-Token':'None',
    'X-Requested-With':'XMLHttpRequest'
}

def get_data_info(url,datas):
    response = requests.post(url, data=datas, headers=headers)
    if response.status_code == 200:
        # 获取工作列表的json数据
        page_json_data = response.json()['content']['positionResult']['result']
        # 遍历工作列表

        page_json_datas = pp.DataFrame(page_json_data)
        page_json_datas.to_csv(r'LaGouPython1.csv',header = False, index = False,mode='a+')

        for position in page_json_data:
            print('职位：' + position['positionName'])
            print('工作经验：' + position['workYear'])
            print('学历要求：' + position['education'])
            print('工作性质：' + position['jobNature'])
            print('发布时间：' + position['createTime'])
            print('工作地点：' + position['city'])
            print('行业：' + position['industryField'])
            print('福利：' + position['positionAdvantage'])
            print('薪资：' + position['salary'])
            print('公司名称：' + position['companyFullName'])
            print('公司规模：' + position['companySize'])
            print('\r\n')
    else:
        print("请求失败！:" + datas)

if __name__ == '__main__':

    #访问路径
    url = 'https://www.lagou.com/jobs/positionAjax.json?needAddtionalResult=false&isSchoolJob=0'
    #访问页数
    page = 5
    #查询关键字
    keyword = 'python'

    for n in range(page):
        # 拼接请求数据
        datas = {
            'first': 'false',
            'kd': keyword,
            'pn': str(n+1) # 页数
        }
        #调用获取数据方法
        get_data_info(url,datas)

        #短暂睡眠，防止反爬
        time.sleep(random.random())
