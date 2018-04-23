#### 一、项目背景

当一个电影在没有上映之前，如何判断它是否会成功呢？可以基于以往的电影信息情况可以做出一些分析和预测。本次案例用到的数据集是Kaggle上TMDb项目中的数据。


#### 二、分析的问题

确定要分析的问题如下：

- 各类电影比较情况
- 电影类型是如何随着时间的推移发生变化的？
- Universal Pictures 和 Paramount Pictures 之间的对比情况如何？
- 改编电影和原创电影的对比情况如何？
- 电影库关键词云
- 电影受欢迎程度与评分次数的相关关系？

#### 三、理解数据

1、导入数据：

import json
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from wordcloud import WordCloud
import numpy as np
plt.rcParams['font.sans-serif']=['SimHei']
plt.rcParams['axes.unicode_minus']=False
导入数据
credits = pd.read_csv('tmdb_5000_credits.csv')
movies = pd.read_csv('tmdb_5000_movies.csv')

2、观察数据：

credits.head()
movies.head()

从观察两个数据集发现：

- 两个数据集中均有json编码的数据
- 两个数据集可以通过credits的movie_id变量和movies中的id变量关联起来

3、合并数据集并观察

fullData=pd.concat([movies,credits],axis=1)
fullData.head(1)
fullData.info()

共有24个变量，

● budget：预算（美元）

● genres：风格列表

● homepage：电影首页的 URL

● id：标识号

● keywords：与电影相关的关键字

● original_language：原始语言

● original_title：原始电影名称

● overview：剧情摘要

● popularity：受欢迎程度

● production_companies:制作电影公司

● production_countries：制作国家

● release_date：首次上映日期

● revenue：收入（美元）

● runtime：电影时长

● spoken_languages：输出语言

● status：电影状态

● tagline：电影的标语

● title：电影名称

● vote_average：平均评分

● vote_count：评分次数

● movie_id：标识号

● cast：演员列表

● crew：剧组


fullData.describe() #数值变量的统计信息

总结：从以上观察可以得出：数据中有json格式的数据需要进行转换，包括genres、keywords、production_companies、production_countries、spoken_languages、cast、crew，数据集中每个观测应有4801个数据，homepage、overview、release_date、runtime、tagline列均有数据缺失。budget、vote_count、 vote_average、revenue、popularity最小值为0，列中可能有异常值。


#### 四、数据清洗

1、删除多余数据

由于数据集中的变量较多，有一些变量与分析的问题无关，因此可以删除。

delete_column = ['homepage', 'original_language', 'overview', 'production_countries', 'spoken_languages', 'status', 'original_title','tagline','movie_id','crew','cast']

fullData.drop(delete_column,axis=1, inplace = True)

fullData.info()

2、缺失值填补

从上面的统计看出release_date有1个缺失值，runtime有两个缺失值。

#对电影时长缺失值用均值进行处理
fullData['runtime']=fullData['runtime'].fillna(fullData['runtime'].mean())

#对电影发布时间缺失可以先列出相关信息，再通过搜索得出，再填补
fullData.loc[fullData['release_date'].isnull(),:]
fullData['release_date']=fullData['release_date'].fillna('2014-06-01')



3、格式转换

将release_date转换为date格式：

fullData['release_date'] = pd.to_datetime(fullData['release_date'])

由于json是以对象来保存数据的，且对象表示为键值对，先用json.loads将字典转换为字符串

fullData['genres']=fullData['genres'].apply(json.loads)
fullData['production_companies']=fullData['production_companies'].apply(json.loads)
fullData['keywords']=fullData['keywords'].apply(json.loads)


再定义函数将值取出并构建一个列表

def getvalue(x):
    n=[]
    for value in x:
        n.append(value['name'])
    return ','.join(n)

fullData['genres']=fullData['genres'].apply(getvalue)
fullData['production_companies']=fullData['production_companies'].apply(getvalue)
fullData['keywords']=fullData['keywords'].apply(getvalue)


4、异常值处理

# 对预算、票房、电影时长、受欢迎程度、评分、评分次数中为0的数值用平均值替代
fullData['budget']=fullData['budget'].replace(0, fullData['budget'].mean())

fullData['revenue']=fullData['revenue'].replace(0, fullData['revenue'].mean())

fullData['runtime']=fullData['runtime'].replace(0, fullData['runtime'].mean())

fullData['popularity']=fullData['popularity'].replace(0, fullData['popularity'].mean())

fullData['vote_average']=fullData['vote_average'].replace(0, fullData['vote_average'].mean())

fullData['vote_count']=fullData['vote_count'].replace(0, fullData['vote_count'].mean())

#### 五、特征提取

1、提取release_time中的年信息，并新增一列release_year

fullData['release_year']=fullData['release_date'].dt.year

2、由于一部电影的种类有多个，因此需要提取genres中的电影类型

genres_list=set()
for i in fullData['genres'].str.split(','):
    genres_list=set().union(i,genres_list)
genres_list=list(genres_list)
genres_list.remove('')

将电影类型进行标记，有该类型的标1，否则标0

genresDf=pd.DataFrame()
for n in genres_list:
    genresDf[n]=fullData['genres'].str.contains(n).apply(lambda x:1 if x else 0)

将发布的年份当做索引，并进行排序

genresDf['release_yearTime']=fullData['release_year']
genresDf.index=fullData['release_year']
genresDf_sort=genresDf.sort_index()

再根据每年进行各类电影的求和

genresDf=genresDf.groupby('release_yearTime').sum()

3、统计各类电影总量

genres_sum=genresDf.sum(axis=0).sort_values(ascending=True)
genres_sum


4、提取原创和改编电影的数量

fullData['if_original']=fullData['keywords'].str.contains('based on novel').apply(lambda x:'not original' if x else 'original')
key_count=fullData['if_original'].value_counts()
key_count



5、提取Universal Pictures和Paramount Picture两家电影制作公司的信息

companyDf=pd.DataFrame()
companyDf['Universal Pictures']=fullData['production_companies'].str.contains('Universal Pictures').apply(lambda x:1 if x else 0)
companyDf['Paramount Pictures']=fullData['production_companies'].str.contains('Paramount Pictures').apply(lambda x:1 if x else 0)
fullData=pd.concat([fullData,companyDf],axis=1)
统计两家公司制作电影的总数量

sum_Uni=fullData['Universal Pictures'].sum()
sum_Par=fullData['Paramount Pictures'].sum()
sum_company={'Universal Pictures':sum_Uni,'Paramount Pictures':sum_Par}
company=pd.Series(sum_company)

统计两家公司的每年的利润

profitDf= fullData[['production_companies','budget','revenue','release_year']].reset_index(drop=True)
profitDf.index = fullData['release_year']

profitDf['Universal_Pictures'] = profitDf['production_companies'].str.contains('Universal Pictures').apply(lambda x:1 if x else 0)
profitDf['Paramount_Pictures'] = profitDf['production_companies'].str.contains('Paramount Pictures').apply(lambda x:1 if x else 0)
profitDf['profit']=profitDf['revenue']-profitDf['budget']

#通过groupby统计每年的利润
profitDf['Universal_profit']=profitDf['profit']*profitDf['Universal_Pictures']
profitDf['Paramount_profit']=profitDf['profit']*profitDf['Paramount_Pictures']

company_Uni = profitDf['Universal_profit'].groupby('release_year').sum()
company_Par = profitDf['Paramount_profit'].groupby('release_year').sum()

#### 六、可视化

- 各类电影比较情况

genres_sum.plot(kind='barh',label='genres',figsize=(14,8))
plt.xticks(fontsize=14)
plt.yticks(fontsize=14)
plt.title('电影类型数量对比',fontsize=20)
plt.xlabel('数量',fontsize=18)
plt.show()


各类电影数量占比
用饼状图来描绘
计算每类电影的占比
genres_per = genres_sum/genres_sum.sum()



将占比小于1%的类型统一归于other类
others = 0.01
genres_perN = genres_per[genres_per>=others]
genres_perN['other'] = genres_per[genres_per < others].sum()


将占比小于等于2%的类型，饼状图稍微高出一点
explode = (genres_perN <= 0.02)/20 + 0.05


绘图
genres_perN.plot(kind = 'pie',label='',startangle=50,shadow = False,figsize = (10,10), autopct = '%1.1f%%',explode=explode)
plt.title('各类电影占比')
plt.show()


小结：从上面两张图可以得出Drama,Comedy,Thriller,Action类型的电影占了整个市场的百分之五十，市场份额最多的为Drama类型的电影。


- 电影类型是如何随着时间的推移发生变化的？

plt.figure(figsize=(12,6),edgecolor='red',dpi=300)
plt.plot(genresDf, label = genresDf.columns)
plt.legend(genresDf)
plt.xlabel('时间',fontsize = 15)
plt.ylabel('电影类型',fontsize = 15)
plt.title('电影类型随时间的变化趋势',fontsize = 15)
plt.grid(True)
plt.show()


小结：随着时间的推移几乎所有类型的电影都呈增长式发展，尤其在90世纪到21世纪呈井喷式发展，并逐渐趋于平稳。


- Universal Pictures 和 Paramount Pictures 之间的对比情况如何？


两家公司电影数量比较：

company.plot(kind = 'pie',label='',startangle=50,shadow = False,figsize = (7,7), autopct = '%1.1f%%')
plt.title('影片数量：Universal Pictures VS Paramount Pictures')
plt.show()


两家公司每年利润比较：

fg = plt.figure(figsize=(12,8))
ax1 = fg.add_subplot(1,1,1)
company_Uni.plot(x =profitDf.index, y = 'Universal_profit', label = 'Universal_Pictures', ax = ax1)
company_Par.plot(x =profitDf.index, y = 'Paramount_profit', label = 'Paramount_Pictures', ax = ax1)
plt.title('每年利润：Universal Pictures VS Paramount Pictures', fontsize = 16)
plt.xticks(fontsize = 14)
plt.yticks(fontsize = 14)
plt.xlabel('时间', fontsize =16)
plt.ylabel('利润', fontsize =16)
plt.legend(fontsize = 13)
plt.show()


小结：从图上可以看出Paramount比Universal公司的电影产量稍低，从每年盈利的折线可以看出两家公司都在增长，其中Paramount更稳定。




- 改编电影和原创电影的对比情况如何？

key_count.plot(kind = 'pie',label='',startangle=50,shadow = False,figsize = (5,5), autopct = '%1.1f%%')
plt.title('原创与改编电影数量比较')
plt.show()


小结：在市场上原创电影远远多于改编的电影。



- 电影库关键词云

生成关键词云

wordCloud = WordCloud( background_color="black",
                     max_words = 2000, max_font_size = 100, random_state = 30)
wordCloud.generate(wordstr)
plt.figure(figsize = (15,10))
plt.imshow(wordCloud)
plt.axis("off")
plt.show()

小结：从关键词可以看出观众关注的热点，包括“woman”,"independent film","murder"等都是焦点。



- 电影受欢迎程度与评分次数相关关系？

首先我们先观察各个变量之间的相关系数


从上表可以看出popularity与vote_count的相关系数为0.77，关联程度比较高。

通过对原始数据集进行训练集和测试集拆分，并用训练集对线性回归模型进行训练，最后用测试集对模型进行评估。

from sklearn.cross_validation import train_test_split
x = fullData['vote_count']
y = fullData['popularity']
x_train,x_test,y_train,y_test = train_test_split(x,y,train_size = 0.8)
plt.scatter(x_train,y_train,color = "blue",label = "训练集")
plt.scatter(x_test,y_test,color = "red",label = "测试集")
plt.xlabel('评分次数',fontsize=15)
plt.ylabel('受欢迎程度',fontsize = 15)
plt.legend(loc=2)
plt.show()




建立模型并训练

from sklearn.linear_model import LinearRegression
x_train = x_train.reshape(-1,1)
y_train= y_train.reshape(-1,1)
model = LinearRegression()
model.fit(x_train,y_train)
LinearRegression(copy_X =True, fit_intercept = True, n_jobs =1, normalize = False)
a = model.intercept_
b = model.coef_
print('截距a=',a,',回归系数b=',b)


截距a= [7.60127853] ,回归系数b= [[0.01984917]]


画出训练集和拟合线

plt.scatter(x_train,y_train,label = '训练集')
y_train_predic = model.predict(x_train)
plt.plot(x_train,y_train_predic, color = 'red',label = '拟合线')
plt.xlabel('评分次数',fontsize=15)
plt.ylabel('受欢迎程度',fontsize = 15)
plt.legend(loc=2)
plt.show()



评估模型

x_test = x_test.reshape(-1,1)
y_test= y_test.reshape(-1,1)
model.score(x_test,y_test)

0.7584140501531879



