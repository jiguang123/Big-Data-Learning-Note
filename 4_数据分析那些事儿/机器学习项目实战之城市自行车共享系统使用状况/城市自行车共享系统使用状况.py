# Kaggle比赛：城市自行车共享系统使用状况。
# 提供的数据为2年内按小时做的自行车租赁数据，其中训练集由每个月的前19天组成，测试集由20号之后的时间组成。
#先把数据读进来
import pandas as pd
data = pd.read_csv('kaggle_bike_competition_train.csv', header = 0, error_bad_lines=False)

#看一眼数据长什么样
print (data.head())

#把datetime域切成日期和时间两部分
temp = pd.DatetimeIndex(data['datetime'])
data['date'] = temp.date
data['time'] = temp.time
print (data.head())

# 设定hour这个小时字段
data['hour'] = pd.to_datetime(data.time, format="%H:%M:%S")
data['hour'] = pd.Index(data['hour']).hour
print (data.head())

# 我们对时间类的特征做处理，产出一个星期几的类别型变量
data['dayofweek'] = pd.DatetimeIndex(data.date).dayofweek

# 对时间类特征处理，产出一个时间长度变量
data['dateDays'] = (data.date - data.date[0]).astype('timedelta64[D]')

print (data.head())

byday = data.groupby('dayofweek')
# 统计下没注册的用户租赁情况
print (byday['casual'].sum().reset_index())

# 统计下注册的用户的租赁情况
print (byday['registered'].sum().reset_index())

data['Saturday']=0
data.Saturday[data.dayofweek==5]=1

data['Sunday']=0
data.Sunday[data.dayofweek==6]=1

print (data.head())

#从数据中把原始的时间字段等踢掉
# remove old data features
dataRel = data.drop(['datetime', 'count','date','time','dayofweek'], axis=1)
print (dataRel.head())




from sklearn.feature_extraction import DictVectorizer
# 我们把连续值的属性放入一个dict中
featureConCols = ['temp','atemp','humidity','windspeed','dateDays','hour']
dataFeatureCon = dataRel[featureConCols]
dataFeatureCon = dataFeatureCon.fillna( 'NA' ) #in case I missed any
X_dictCon = dataFeatureCon.T.to_dict().values() 

# 把离散值的属性放到另外一个dict中
featureCatCols = ['season','holiday','workingday','weather','Saturday', 'Sunday']
dataFeatureCat = dataRel[featureCatCols]
dataFeatureCat = dataFeatureCat.fillna( 'NA' ) #in case I missed any
X_dictCat = dataFeatureCat.T.to_dict().values() 

# 向量化特征
vec = DictVectorizer(sparse = False)
X_vec_cat = vec.fit_transform(X_dictCat)
X_vec_con = vec.fit_transform(X_dictCon)


print (dataFeatureCon.head())

print (X_vec_con)

print (dataFeatureCat.head())

print (X_vec_cat)


from sklearn import preprocessing
# 标准化连续值数据
scaler = preprocessing.StandardScaler().fit(X_vec_con)
X_vec_con = scaler.transform(X_vec_con)
print (X_vec_con)


from sklearn import preprocessing
# one-hot编码
enc = preprocessing.OneHotEncoder()
enc.fit(X_vec_cat)
X_vec_cat = enc.transform(X_vec_cat).toarray()
print (X_vec_cat)


import numpy as np
# combine cat & con features
X_vec = np.concatenate((X_vec_con,X_vec_cat), axis=1)
print (X_vec)


# 对Y向量化
Y_vec_reg = dataRel['registered'].values.astype(float)
Y_vec_cas = dataRel['casual'].values.astype(float)

print (Y_vec_reg)
print (Y_vec_cas)