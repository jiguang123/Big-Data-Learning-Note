# /usr/bin/env python3
# -*- coding:utf-8 -*-

import requests
import csv


headers={
'Accept':'application/json, text/javascript, */*; q=0.01',
'Accept-Encoding':'gzip, deflate, br',
'Accept-Language':'zh-CN,zh;q=0.8',
'Connection':'keep-alive',
'Content-Length':'25',
'Content-Type':'application/x-www-form-urlencoded; charset=UTF-8',
'Cookie':'user_trace_token=20170214020222-9151732d-f216-11e6-acb5-525400f775ce; LGUID=20170214020222-91517b06-f216-11e6-acb5-525400f775ce; JSESSIONID=ABAAABAAAGFABEF53B117A40684BFB6190FCDFF136B2AE8; _putrc=ECA3D429446342E9; login=true; unick=yz; showExpriedIndex=1; showExpriedCompanyHome=1; showExpriedMyPublish=1; hasDeliver=0; PRE_UTM=; PRE_HOST=; PRE_SITE=; PRE_LAND=https%3A%2F%2Fwww.lagou.com%2F; TG-TRACK-CODE=index_navigation; Hm_lvt_4233e74dff0ae5bd0a3d81c6ccf756e6=1494688520,1494690499,1496044502,1496048593; Hm_lpvt_4233e74dff0ae5bd0a3d81c6ccf756e6=1496061497; _gid=GA1.2.2090691601.1496061497; _gat=1; _ga=GA1.2.1759377285.1487008943; LGSID=20170529203716-8c254049-446b-11e7-947e-5254005c3644; LGRID=20170529203828-b6fc4c8e-446b-11e7-ba7f-525400f775ce; SEARCH_ID=13c3482b5ddc4bb7bfda721bbe6d71c7; index_location_city=%E6%9D%AD%E5%B7%9E',
'Host':'www.lagou.com',
'Origin':'https://www.lagou.com',
'Referer':'https://www.lagou.com/jobs/list_Python?',
'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36',
'X-Anit-Forge-Code':'0',
'X-Anit-Forge-Token':'None',
'X-Requested-With':'XMLHttpRequest'
}


def get_json(url, page, lang_name):
#修改city更换城市
    data = {'first': 'true', 'pn': page, 'kd': lang_name,'city':'北京'}
#post请求
    json = requests.post(url,data, headers=headers).json()
    list_con = json['content']['positionResult']['result']
    info_list = []
    for i in list_con:
        info = []
        info.append(i['companyId'])#现在没有公司名字，只能看到id
        info.append(i['salary'])
        info.append(i['city'])
        info.append(i['education'])
        info_list.append(info)
    return info_list


def main():
#修改lang_name更换语言类型
    lang_name = 'python'
    page = 1
    url = 'http://www.lagou.com/jobs/positionAjax.json?needAddtionalResult=false'
    info_result = []
    while page < 31:
        info = get_json(url, page, lang_name)
        info_result = info_result + info
        page += 1
   #写入lagou.txt文件中
    with open('lagou_v2.csv','w') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerows(content)
        csvfile.close()


if __name__ == '__main__':
    main()

