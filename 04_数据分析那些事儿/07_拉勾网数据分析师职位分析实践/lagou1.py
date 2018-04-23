# /usr/bin/env python3
# -*- coding:utf-8 -*-


import requests
from bs4 import BeautifulSoup


def do_request(url, headers=None):
    """"""
    if headers is None:
        req = requests.get(url)
    else:
        req = requests.get(url, headers=headers)

    if req.status_code not in [200, ]:
        with open('error_url.log', 'w') as f:
            f.write(url)
            return False
    return req.content


def do_soup(content):
    """return company, company id, hrid, positionid, positionname, salary"""

    soups = BeautifulSoup(content, "html.parser")
    # soup_list = soups.find(id='s_position_list').find_all('li')
    soups = soups.find(id='s_position_list').ul.find_all('li')
    soup_list = []
    for idx, soup in enumerate(soups):
        soup_list.append({'company': soup['data-company'],
                          'company_id': soup['data-companyid'],
                          'hrid': soup['data-hrid'],
                          'positionid': soup['data-positionid'],
                          'positionname': soup['data-positionname'],
                          'salary': soup['data-salary']})
    return soup_list


def save_csv(soup_list):
    with open('jobs.csv', 'a') as f:
        line_tpl = '''"{company_id}","{company}","{hrid}","{positionid}","{positionname}","{salary}"\n'''

        for soup in soup_list:
            f.write(line_tpl.format(**soup))


def main():
    host = 'https://www.lagou.com'
    path = '/zhaopin/Python/{page_id}/'

    headers = {'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
               'Accept-Encoding': 'gzip, deflate, sdch, br',
               'Cache-Control': 'no-cache',
               'Connection': 'keep-alive',
               'DNT': '1',
               'Host': 'www.lagou.com',
               'Pragma': 'no-cache',
               'Upgrade-Insecure-Requests': '1',
               'Cookie': 'user_trace_token=20170529170535-f9c2c61d-444d-11e7-9468-5254005c3644; PRE_UTM=; PRE_HOST=; PRE_SITE=; PRE_LAND=https%3A%2F%2Fpassport.lagou.com%2Flogin%2Flogin.html%3Fmsg%3Dvalidation%26uStatus%3D2%26clientIp%3D223.20.35.98; LGUID=20170529170535-f9c2ca34-444d-11e7-9468-5254005c3644; JSESSIONID=ABAAABAAADEAAFI755D3A01C2C01F7BBAD36A9C10003482; _gat=1; index_location_city=%E5%8C%97%E4%BA%AC; TG-TRACK-CODE=index_navigation; SEARCH_ID=f6eb83ea6f014ca5b22bad098089c4fa; _gid=GA1.2.1479464309.1496050214; Hm_lvt_4233e74dff0ae5bd0a3d81c6ccf756e6=1496048733; Hm_lpvt_4233e74dff0ae5bd0a3d81c6ccf756e6=1496050214; _ga=GA1.2.1251572620.1496048733; LGSID=20170529170535-f9c2c89c-444d-11e7-9468-5254005c3644; LGRID=20170529173016-6c7f3d70-4451-11e7-b9f1-525400f775ce',
               'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36',
               }

    for i in range(1, 31):
        print(i)
        url = '{}/{}'.format(host, path.format(page_id=i))
        text = do_request(url, headers=headers)

        if text:
            soup_list = do_soup(text)
            save_csv(soup_list)


if __name__ == '__main__':
    main()