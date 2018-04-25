# -*- coding: utf-8 -*-

import requests
import json
import pandas as pd 

url = "https://www.panda.tv/live_lists?status=2&order=person_num&token=&pageno=%d&pagenum=120&_=%d".format(a=range(0,35),b=range(1501946526480,1501946526880))

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:54.0) Gecko/20100101 Firefox/54.0'
    ,
    'Cookie': '__guid=96554777.3243119502220345300.1500627276199.6702; smid=608e0bde-ffe2-4251-90ca-2938cabdc074; monitor_count=18'
    ,
}


def getHtml(url):
    req = requests.get(url, headers=headers)
    print(req.text)
    return req.text


def printInfos(data):
    jsondata = json.loads(data, "utf-8")
    # print(jsondata)
    itemsinfo = jsondata['data']['items']
    items_list = []
    for pinfo in itemsinfo:
        name = pinfo['name']
        person_num = pinfo['person_num']
        nickName = pinfo['userinfo']['nickName']
        lelvel = pinfo['host_level_info']
        lable = pinfo['label']       
        cname = pinfo['classification']
        item_list = [name, person_num, nickName, lelvel, label, cname]
        items_list.append(item_list)
    df = pd.DataFrame(items_list, columns = ['name','person_num','nickName','host_level_info','label','classification'])
    df.to_csv('熊猫直播用户信息.csv')

	
def mainStart():
    for n in range(0, 3):
        pageindex = 1 + n
        pagetime = int(1501946526480 + n)
        url = "https://www.panda.tv/live_lists?status=2&order=person_num&token=&pageno=%d&pagenum=120&_=%d"%(pageindex,pagetime)
        data = getHtml(url)
        printInfos(data)

mainStart()