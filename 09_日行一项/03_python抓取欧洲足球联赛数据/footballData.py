#!/usr/bin/python
#-*- coding: utf-8 -*-

import requests
import urlparse
import bs4
import csv
 
BASE_URL = "http://soccerdata.sports.qq.com"
PLAYER_LIST_QUERY = "/playerSearch.aspx?lega=%s&pn=%d"
league = ['epl','seri','bund','liga','fran','scot','holl','belg']
page_number_limit = 100
player_fields = ['league_cn','img','name_cn','name','team','age','position_cn','nation','birth','query','id','teamid','league']

def get_players(baseurl):
    html = requests.get(baseurl).text
    soup = bs4.BeautifulSoup(html, "lxml")
    players = [ dd for dd in soup.select('.searchResult tr') if dd.contents[1].name != 'th']
    result = []
    for player in players:
        record = []
        link = ''
        query = []
        for item in player.contents:
            if type(item) is bs4.element.Tag:
                if not item.string and item.img:
                    record.append(item.img['src'])
                else :
                     record.append(item.string and item.string.strip() or 'na')
                try:
                    o = urlparse.urlparse(item.a['href']).query
                    if len(link) == 0:
                        link = o
                        query = dict([(k,v[0]) for k,v in urlparse.parse_qs(o).items()])
                except:
                    pass
             
        if len(record) != 10:
            for i in range(0, 10 - len(record)):
                record.append('na')
        record.append(unicode(link,'utf-8'))
        record.append(unicode(query["id"],'utf-8'))
        record.append(unicode(query["teamid"],'utf-8'))
        record.append(unicode(query["lega"],'utf-8'))
        result.append(record)
    return result
    
result = []
for url in [ BASE_URL + PLAYER_LIST_QUERY % (l,n) for l in league for n in range(page_number_limit) ]:
    result = result +  get_players(url)


for i in league:
    for j in range(0, 100):
        url = BASE_URL + PLAYER_LIST_QUERY % (l,n)
        ## send request to url and do scraping


def write_csv(filename, content, header = None): 
    file = open(filename, "wb")
    file.write('\xEF\xBB\xBF')
    writer = csv.writer(file, delimiter=',')
    if header:
        writer.writerow(header)
    for row in content:
        encoderow = [dd.encode('utf8') for dd in row]
        writer.writerow(encoderow)
 
write_csv('players.csv',result,player_fields)

def get_player_match(url):
    html = requests.get(url).text
    soup = bs4.BeautifulSoup(html, "lxml")
    matches = [ dd for dd in soup.select('.shtdm tr') if dd.contents[1].name != 'th']
    records = []
    for item in [ dd for dd in matches if len(dd.contents) > 11]: ## filter out the personal part
        record = []
        for match in [ dd for dd in item.contents if type(dd) is bs4.element.Tag]:
            if match.string:
                record.append(match.string)
            else:
                for d in [ dd for dd in match.contents if type(dd) is bs4.element.Tag]:
                    query = dict([(k,v[0]) for k,v in urlparse.parse_qs(d['href']).items()])
                    record.append('teamid' in query and query['teamid'] or query['id'])   
                    record.append(d.string and d.string or 'na')                    
        records.append(record)
    return records[1:]  ##remove the first record as the header
 
def get_players_match(playerlist, baseurl = BASE_URL + '/player.aspx?'):
    result = []
    for item in playerlist:
        url =  baseurl + item[10]
        print (url)
        result = result + get_player_match(url)
    return result
match_fields = ['date_cn','homeid','homename_cn','matchid','score','awayid','awayname_cn','league_cn','firstteam','playtime','goal','assist','shoot','run','corner','offside','foul','violation','yellowcard','redcard','save']    
write_csv('m.csv',get_players_match(result),match_fields)