from sklearn.datasets import load_iris
from sklearn.cross_validation import train_test_split
from sklearn import preprocessing

# 读取数据
iris = load_iris()

# 选取特征与标签
X_iris, y_iris = iris.data, iris.target

# 选择前两列数据作为特征
X, y = X_iris[:, :2], y_iris

# 选取一部分，25%的训练数据作为测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state = 33)

# 对原特征数据进行标准化预处理，这个其实挺重要，但是经常被一些选手忽略
scaler = preprocessing.StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

from sklearn.linear_model import SGDClassifier

# 选择使用SGD分类器，适合大规模数据，随机梯度下降方法估计参数
clf = SGDClassifier()

clf.fit(X_train, y_train)

# 导入评价包
from sklearn import metrics

y_train_predict = clf.predict(X_train)

# 内测，使用训练样本进行准确性能评估
print (metrics.accuracy_score(y_train, y_train_predict))

# 标准外测，使用测试样本进行准确性能评估
y_predict = clf.predict(X_test)
print (metrics.accuracy_score(y_test, y_predict))

# 如果需要更加详细的性能报告，比如precision, recall, accuracy，可以使用如下的函数。
print (metrics.classification_report(y_test, y_predict, target_names = iris.target_names))
# 如果想详细探查SGDClassifier的分类性能，我们需要充分利用数据，因此需要把数据切分为N个部分，每个部分都用于测试一次模型性能。

from sklearn.cross_validation import cross_val_score, KFold
from sklearn.pipeline import Pipeline 
from sklearn.preprocessing import StandardScaler
# 这里使用Pipeline，便于精简模型搭建，一般而言，模型在fit之前，对数据需要feature_extraction, preprocessing, 等必要步骤。
# 这里我们使用默认的参数配置
clf = Pipeline([('scaler', StandardScaler()), ('sgd_classifier', SGDClassifier())])

# 5折交叉验证整个数据集合
cv = KFold(X.shape[0], 5, shuffle=True, random_state = 33)

scores = cross_val_score(clf, X, y, cv=cv)
print (scores)

# 计算一下模型综合性能，平均精度和标准差
print (scores.mean(), scores.std())

from scipy.stats import sem
import numpy as np

# 这里使用的偏差计算函数略有不同，参考链接http://www.graphpad.com/guides/prism/6/statistics/index.htm?stat_semandsdnotsame.htm
print (np.mean(scores), sem(scores))