# -*- coding: utf-8 -*-

import requests
import time
from bs4 import BeautifulSoup
import pandas as pd
# 导入pandas库

# 设置列表页面URL的固定部分
url = 'https://bj.lianjia.com/ershoufang/'
BASE_URL_U1 = "http://www.cyzone.cn/event/list-764-0-"
BASE_URL_U2 = "-0-0-0-0/"

# 最好在http请求中设置一个头部信息，否则很容易被封ip
headers = {'User-Agent':'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11',
'Accept':'text/html;q=0.9,*/*;q=0.8',
'Accept-Charset':'ISO-8859-1,utf-8;q=0.7,*;q=0.3',
'Accept-Encoding':'gzip',
'Connection':'close',
'Referer':'http://www.baidu.com/link?url=_andhfsjjjKRgEWkj7i9cFmYYGsisrnm2A-TN3XZDQXxvGsM9k9ZZSnikW2Yds4s&amp;amp;wd=&amp;amp;eqid=c3435a7d00146bd600000003582bfd1f'
}

# 循环抓取列表页信息
for i in range(1,31):  # 分页
        if i == 1:
            i=str(1)
            var_url = (BASE_URL_U1 + i + BASE_URL_U2)
            r = requests.get(url=var_url, headers=headers)
            html = r.content
            #print(html)
        else:
            i=str(i)
            var_url=(BASE_URL_U1 + i + BASE_URL_U2)
            var_url=requests.get(url=var_url,headers=headers)
            html2=r.content
            html = html + html2
            # 每次间隔1秒
            time.sleep(1)
        
        # 解析抓取的页面内容
        res = BeautifulSoup(html, 'html.parser')
        # 获取感兴趣目标信息：
        # 提取公司名称
        # table>tbody>tr.table-plate3>td.tp2>span.tp2_tit>a     
        companys = res.find_all('span', 'tp2_tit')
        cnames = []
        print(len(companys))
        for item in companys:
            cname =  item.a.string
            cnames.append(cname)
    
        #print(cnames)
        # 获取感兴趣目标信息：
        # 提取公司详情url
        companys = res.find_all('span', 'tp2_tit')
        urls = []
        for item in companys:
            url =  item.a['href']
            urls.append(url)
        # 获取感兴趣目标信息：
        # 提取当前融资轮次,行业，投资方和更新时间

        # res = BeautifulSoup(html, 'html5lib')
        # finances = res.select('div#main > div.list-table3 > table > tbody > tr')
        finances = res.find_all('tr', 'table-plate3')
        # 融资轮次,行业,投资方,更新时间
        financing_rounds, businesses, investors, update_times  = [],[],[],[]
        #print(len(finances))
        for i in range(0, len(finances)):
            # 获取第一行数据(范围)
            items = finances[i].find_all('td')
            # print(items)
            # 获取融资轮次
            fround =  items[-5].text.strip()
            #获取行业
            business = items[-4].text.strip()
            #获取投资方
            investor = items[-3].text.strip()
            #获取更新时间
            update_time = items[-2].text.strip()
            financing_rounds.append(fround)
            businesses.append(business)
            investors.append(investor)
            update_times.append(update_time)
            
            # 将获取的数据进行汇总：
            #print(len(cnames))
            #print(len(urls))
            #print(len(financing_rounds))
            #print(len(financing_rounds))
            #print(len(businesses))
            #print(len(investors))
            #print(len(update_times))
    
            # 创建数据表
        resultsDatas = pd.DataFrame({'公司名称':cnames,'详情URL':urls,'融资轮次':financing_rounds,'行业':businesses,'投资方':investors,'更新时间':update_times})
            # 查看数据表内容
        print(resultsDatas)


resultsDatas.to_csv("resultsDatas.csv")