import pandas as pd
import re
import numpy as np
import requests
import time
import random
from bs4 import BeautifulSoup
 
s=requests.session()
 
headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36'}
#根据浏览器下自行修改
 
headers['Cookie'] = 'gr_user_id=022d0f46-4981-4224-9895-18bfe32d9276; rrdLoginCartoon=rrdLoginCartoon; pgv_pvi=905847926; Hm_lvt_16f9bb97b83369e62ee1386631124bb1=1474288518,1474332677,1474336816,1474368269; Hm_lpvt_16f9bb97b83369e62ee1386631124bb1=1474372985; JSESSIONID=7EB90C9967D8C42B08DFB18EB9A9F74ED2ACC468B7D56B9372E2A20684713847; jforumUserInfo=bEAY23pgyLLLjII69w9oS%2BtK2jljmxa8%0A; IS_MOBLIE_IDPASS=true-false; activeTimestamp=5195275; gr_session_id_9199126ed94d770d=70bbe285-4ac6-42c9-a49b-9255d0eb9c46; gr_cs1_70bbe285-4ac6-42c9-a49b-9255d0eb9c46=user_id%3A5195275'
#根据浏览器F12下的Request Headers->Cookie自行复制上去即可
 
 
def parse_userinfo(loanid):#自定义解析借贷人信息的函数
    timestamp=str(int(time.time())) + '%03d' % random.randint(0,999)<br>
    urll="http://www.we.com/lend/detailPage.action?loanId=%.0f&timestamp=" % loanid+timestamp<br>    #这个urll我也不知道怎么来的，貌似可以用urll="http://www.we.com/loan/%f" % loanid+timestamp  <br>    #(就是页面本身，我也没试过)
    result = s.get(urll,headers=headers)
    html = BeautifulSoup(result.text,'lxml')
    info = html.find_all('table',class_="ui-table-basic-list")
    info1= info[0]
    info2 = info1.find_all('div',class_="basic-filed")
    userinfo = {}
    for item in info2:
        vartag = item.find('span')
        var = vartag.string
        if var == '信用评级':
            var = '信用评分'
            pf1 = repr(item.find('em'))
            value = re.findall(r'\d+',pf1)
        else:
            valuetag = item.find('em')
            value = valuetag.string
        userinfo[var]=value
    data = pd.DataFrame(userinfo)
    return data
 
rrd=pd.read_csv('loanId.csv') #loanId是之前散标数据中的loanId,将其单独整理为一个csv文档
loanId=rrd.ix[:,'loanId']
user_info = ['昵称', '信用评分',
 
            '年龄', '学历', '婚姻',
 
            '申请借款', '信用额度', '逾期金额', '成功借款', '借款总额', '逾期次数','还清笔数', '待还本息', '严重逾期',
 
            '收入', '房产', '房贷', '车产', '车贷',
 
'公司行业', '公司规模', '岗位职位', '工作城市', '工作时间']
 
table = pd.DataFrame(np.array(user_info).reshape(1, 24), columns=user_info)
 
i = 1
 
for loanid in loanId:
    table = pd.concat([table, parse_userinfo(loanid)])
    print(i)
    i += 1 #看一下循环多少次
 
table.to_csv('userinfo.csv',header=False)