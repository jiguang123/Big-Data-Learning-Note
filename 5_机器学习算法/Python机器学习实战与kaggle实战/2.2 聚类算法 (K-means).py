import pandas as pd
import numpy as np

titanic = pd.read_csv('http://biostat.mc.vanderbilt.edu/wiki/pub/Main/DataSets/titanic.txt')

print titanic.info()
# 还是这组数据
titanic.head()

# 我们丢掉一些过于特异的，不利于找到共同点的数据列， row.names, name, 同时分离出预测列。

y = titanic['survived']
X = titanic.drop(['row.names', 'name', 'survived'], axis = 1)

# 对于连续的数值特征，我们采用补完的方式
X['age'].fillna(X['age'].mean(), inplace=True)

X.fillna('UNKNOWN', inplace=True)


# 剩下的类别类型数据，我们直接向量化，这样的话，对于有空白特征的列，我们也单独视作一个特征

from sklearn.cross_validation import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=33)

from sklearn.feature_extraction import DictVectorizer
vec = DictVectorizer()
X_train = vec.fit_transform(X_train.to_dict(orient='record'))
X_test = vec.transform(X_test.to_dict(orient='record'))

print len(vec.feature_names_)

X_train.toarray()

from sklearn.tree import DecisionTreeClassifier

dt = DecisionTreeClassifier(criterion='entropy')
dt.fit(X_train, y_train)
dt.score(X_test, y_test)
# 采用所有特征的测试精度

from sklearn import feature_selection
fs = feature_selection.SelectPercentile(feature_selection.chi2, percentile=20)

X_train_fs = fs.fit_transform(X_train, y_train)
dt.fit(X_train_fs, y_train)
X_test_fs = fs.transform(X_test)
dt.score(X_test_fs, y_test)
# 采用20%高预测性特征的测试精度

from sklearn.cross_validation import cross_val_score
percentiles = range(1, 100, 2)

results = []

for i in percentiles:
    fs = feature_selection.SelectPercentile(feature_selection.chi2, percentile = i)
    X_train_fs = fs.fit_transform(X_train, y_train)
    scores = cross_val_score(dt, X_train_fs, y_train, cv=5)
    results = np.append(results, scores.mean())
print results

opt = np.where(results == results.max())[0]
print 'Optimal number of features %d' %percentiles[opt]
import pylab as pl

pl.plot(percentiles, results)
pl.show()


from sklearn import feature_selection
fs = feature_selection.SelectPercentile(feature_selection.chi2, percentile=7)

X_train_fs = fs.fit_transform(X_train, y_train)
dt.fit(X_train_fs, y_train)
X_test_fs = fs.transform(X_test)
dt.score(X_test_fs, y_test)
# 选取搜索到的最好特征比例的测试精度




