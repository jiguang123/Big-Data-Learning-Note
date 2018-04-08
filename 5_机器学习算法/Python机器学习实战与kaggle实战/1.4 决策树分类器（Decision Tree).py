# 我们使用Titanic（泰坦尼克号的救援记录）这个数据集来实践一个预测某乘客是否获救的分类器。

# 这里为了处理数据方便，我们引入一个新的工具包pandas

import pandas as pd
import numpy as np

titanic = pd.read_csv('http://biostat.mc.vanderbilt.edu/wiki/pub/Main/DataSets/titanic.txt')

#瞧瞧数据，什么数据特征的都有，有数值型的、类别型的，字符串，甚至还有缺失的数据等等。
print (titanic.head())

# 使用pandas，数据都转入pandas独有的dataframe格式（二维数据表格），直接使用info()，查看数据的基本特征
print (titanic.info())

# 这份调查数据是真实的泰坦尼克号乘客个人和登船信息，有助于我们预测每位遇难乘客是否幸免。
# 一共1313条数据，有些特征是完整的（比如 pclass, survived, name），有些是有缺失的；有些是数值类型的信息（age: float64），有些则是字符串。
# 机器学习有一个不太被初学者重视，并且耗时，但是十分重要的一环，特征的选择，这个需要基于一些背景知识。根据我们对这场事故的了解，sex, age, pclass这些都很有可能是决定幸免与否的关键因素。

# we keep pclass, age, sex.

X = titanic[['pclass', 'age', 'sex']]
y = titanic['survived']

X.info()

# 下面有几个对数据处理的任务
# 1) age这个数据列，只有633个
# 2) sex 与 pclass两个数据列的值都是类别型的，需要转化为数值特征，用0/1代替

# 首先我们补充age里的数据，使用平均数或者中位数都是对模型偏离造成最小影响的策略
X['age'].fillna(X['age'].mean(), inplace=True)


X.info()

from sklearn.cross_validation import train_test_split

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state = 33)

# 我们使用scikit-learn中的feature_extraction
from sklearn.feature_extraction import DictVectorizer
vec = DictVectorizer(sparse=False)
X_train = vec.fit_transform(X_train.to_dict(orient='record'))
print (vec.feature_names_)
# 我们发现，凡是类别型的特征都单独剥离出来，独成一列特征，数值型的则保持不变
 
X_test = vec.transform(X_test.to_dict(orient='record'))
from sklearn.tree import DecisionTreeClassifier

dtc = DecisionTreeClassifier(criterion='entropy', max_depth=3, min_samples_leaf=5)
dtc.fit(X_train, y_train)
dtc.score(X_test, y_test)



from sklearn.ensemble import RandomForestClassifier

rfc = RandomForestClassifier(max_depth=3, min_samples_leaf=5)
rfc.fit(X_train, y_train)
rfc.score(X_test, y_test)


from sklearn.ensemble import GradientBoostingClassifier

gbc = GradientBoostingClassifier(max_depth=3, min_samples_leaf=5)

gbc.fit(X_train, y_train)
gbc.score(X_test, y_test)

from sklearn.metrics import classification_report

y_predict = gbc.predict(X_test)
print classification_report(y_predict, y_test)
# 这里的函数可以便于生成分类器性能报告（precision,recall)这些是在二分类背景下才有的指标。




