# /usr/bin/env python3
# -*- coding:utf-8 -*-

"""
title:抓取拉勾网的数据
time:2018-04-23
author:Tom
"""
import requests
from time import sleep
import random
import pandas

#职位所属地
city='北京'
#职位关键字
job='python'
url='https://www.lagou.com/jobs/positionAjax.json?city='+city+'&needAddtionalResult=false&isSchoolJob=0'

header = {
    'Host': 'www.lagou.com',
    'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.84 Safari/537.36',
    'Accept': 'application/json, text/javascript, */*; q=0.01',
    'Accept-Language': 'zh-CN,en-US;q=0.7,en;q=0.3',
    'Accept-Encoding': 'gzip, deflate, br',
    'Referer': 'https://www.lagou.com/jobs/list_Python?labelWords=&fromSearch=true&suginput=',
    'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8',
    'X-Requested-With': 'XMLHttpRequest',
    'X-Anit-Forge-Token': 'None',
    'X-Anit-Forge-Code': '0',
    'Content-Length': '26',
    'Connection': 'keep-alive',
    'Pragma': 'no-cache',
    'Cache-Control': 'no-cache'
    }
    
for num in range(1,16):
    #取随机延迟
    ran=random.randint(1,3)
    sleep(ran)
    #
    flag='true'
    if num!=1:
           flag='false'
    form = {'first':flag,
            'kd':job,
            'pn':str(num)}
    html=requests.post(url=url,data=form,headers=header)
    result=html.json()
    print('--------------------'+str(num)+'-----------------------')
    data=result['content']['positionResult']['result']
    print(data)
    table = pandas.DataFrame(data)
    table.to_csv(r'LaGouPython.csv',header = False, index = False,mode='a+')