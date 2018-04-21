# Python学习者最易上手的机器学习漫游指南

毋庸置疑，近来机器学习人气日益高涨，逐渐在流行词榜单上占据一席之地。机器学习算法繁多，到底该选择哪一种处理相关数据是困扰很多学习者的问题。本文将以一种清晰简明的方式，解释并实践最常见的几种机器学习算法。

接下来，我们将罗列8种最常见火爆的机器学习算法，通过Python，将它们分别适用同一个经典数据集Iris（线性回归和逻辑回归除外），进而分辨出不同算法在预测准确率、模型建立过程、对数据集的使用方式等方向的异同。每一种算法后都将附上Python实现代码和演示视频。

![image](https://mmbiz.qpic.cn/mmbiz_gif/wc7YNPm3YxX6Ywia9cSvC45bfUh1ZoQC91iboA1j3WsL9MIPO3NOTd4pBIC0PNibrRwhM67Mn9ey4h8jmxU79zAMw/0?wx_fmt=gif&tp=webp&wxfrom=5&wx_lazy=1)


---

本文中将覆盖共8种不同的机器学习算法（后续会有更多）。阅读时本指南时，你可以自由的随意翻翻或跳过任何一个已经熟悉的算法。请根据着个人需求使用这份指南。闲话少说，本文将分为以下及部分。

- 线性回归
- 逻辑回归

- 决策树

- 支持向量机

- KNN 临近算法

- 随机森林

- K-Means聚类

- 主成分分析

若尝试使用他人的代码时，结果你发现需要三个新的模块包而且本代码是用旧版本的语言写出的，这将让人感到无比沮丧。为了大家更加方便，我将使用Python3.5.2并会在下方列出了我在做这些练习前加载的模块包。我也从UCI机器学习库中下载了Diabetes和Iris数据集作为样本数据。

如果你希望跳过这些内容，仅想看看全部代码，你可以直接前往Github上查看（https://github.com/conordewey3/HitchHikers-Guide-Machine-Learning）。


---
## 线性回归

线性回归应该是机器学习原理中最流行也是最不受重视的算法了。在比较模型表现时，许多数据科学家总是会忽略这一事实，即比起复杂更应该选择简单的方法。

总之，线性回归是一种基于连续型变量进行预测的有监督学习算法。线性回归适用范围广泛，它既能对单一变量做回归（简单线性回归）也可以对多维特征做回归（多元线性回归）。他的工作原理是，对变量分配最佳权重以产生的一条直线（ax+b)用于预测结果。请查看以下视频了解更多详尽内容。


```
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn aas sns
from sklearn import linear_model

df = pd.read_csv(‘linear_regression_df.csv’)
df.columns = [‘X’, ‘Y’]
df.head()

sns.set_context(“notebook”, font_scale=1.1)
sns.set_style(“ticks”)
sns.lmplot(‘X’,’Y’, data=df)
plt.ylabel(‘Response’)
plt.xlabel(‘Explanatory’)

linear = linear_model.LinearRegression()
trainX = np.asarray(df.X[20:len(df.X)]).reshape(-1, 1)
trainY = np.asarray(df.Y[20:len(df.Y)]).reshape(-1, 1)
testX = np.asarray(df.X[:20]).reshape(-1, 1)
testY = np.asarray(df.Y[:20]).reshape(-1, 1)
linear.fit(trainX, trainY)
linear.score(trainX, trainY)
print(‘Coefficient: \n’, linear.coef_)
print(‘Intercept: \n’, linear.intercept_)
print(‘R² Value: \n’, linear.score(trainX, trainY))
predicted = linear.predict(testX)
```

---

## 逻辑回归
逻辑回归是有监督分类算法的一种，对预测离散变量非常有效。一种典型的用法是用逻辑回归方程预测事件在0到1之间发生的概率。

当我第一次学习逻辑回归时，以为是这只是一个小众工具，并没有引起十分的注意。后来我才发现，这种想法真是大错特错。逻辑回归的一些潜在概念在机器学习其他算法例如神经网络中也有用到。


```
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn aas sns
from sklearn.linear_model import LogisticRegression

df = pd.read_csv(‘logistic_regression_df.csv’)
df.columns = [‘X’, ‘Y’]
df.head()

sns.set_context(“notebook”, font_scale=1.1)
sns.set_style(“ticks”)
sns.regplot(‘X’,’Y’, data=df, logistic=True)
plt.ylabel(‘Probability’)
plt.xlabel(‘Explanatory’)

logistic = LogisticRegression()
X = (np.asarray(df.X)).reshape(-1, 1)
Y = (np.asarray(df.Y)).ravel()
logistic.fit(X, Y)
logistic.score(X, Y)
print(‘Coefficient: \n’, logistic.coef_)
print(‘Intercept: \n’, logistic.intercept_)
print(‘R² Value: \n’, logistic.score(X, Y))


```


---
## 决策树

决策树也是有监督学习的一种，即可用于分类也可用于回归。在我的经验里，他们主要用于分类。模型先接受输入的一种情况，然后沿着树枝向下走，依据设计的条件检测重要变量。根据结果，选择继续往左边的子枝走还是往右边的子枝走，如此重复。一般整个过程中，最重要的特征会更靠近树的根部。

决策树正变得越来越受欢迎，而且任何项目的数据科学家都能用它作为一种强分类算法，尤其与随机是森林，Boosting 算法和Bagging 算法一起使用时。再一次，使用下方的视频更深入了解决策树的基础功能。


```
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn aas sns
from sklearn import tree

df = pd.read_csv(‘iris_df.csv’)
df.columns = [‘X1’, ‘X2’, ‘X3’, ‘X4’, ‘Y’]
df.head()

from sklearn.cross_validation import train_test_split

decision = tree.DecisionTreeClassifier(criterion=’gini’)
X = df.values[:, 0:4]
Y = df.values[:, 4]
trainX, testX, trainY, testY = train_test_split( X, Y, test_size = 0.3)
decision.fit(trainX, trainY)
print(‘Accuracy: \n’, decision.score(testX, testY))

from sklearn.externals.six import StringIO 
from IPython.display import Image
import pydotplus as pydot

dot_data = StringIO()
tree.export_graphviz(decision, out_file=dot_data)
graph = pydot.graph_from_dot_data(dot_data.getvalue())
Image(graph.create_png())



```

---

## 支持向量机

支持向量机，又称SVM，是一种通过在不同类别的数据间生成一条分界线实现分类的知名的有监督分类算法。简单来说，通过计算最优分割平面，使得属于两个不同类的数据点间隔最大，从而得到分类向量。

分类向量一般被默认或被视为线性，然而不一定非要这样。如果核函数不是默认的高斯函数或线性函数，分类向量也可以是非线性的形式。

现在你已经了解支持向量机了，让我们在Python中一起实践一下。


```
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn aas sns
from sklearn import svm

df = pd.read_csv(‘iris_df.csv’)
df.columns = [‘X4’, ‘X3’, ‘X1’, ‘X2’, ‘Y’]
df = df.drop([‘X4’, ‘X3’], 1)
df.head()

from sklearn.cross_validation import train_test_split

support = svm.SVC()
X = df.values[:, 0:2]
Y = df.values[:, 2]
trainX, testX, trainY, testY = train_test_split( X, Y, test_size = 0.3)
support.fit(trainX, trainY)
print(‘Accuracy: \n’, support.score(testX, testY))
pred = support.predict(testX)

sns.set_context(“notebook”, font_scale=1.1)
sns.set_style(“ticks”)
sns.lmplot(‘X1’,’X2', scatter=True, fit_reg=False, data=df, hue=’Y’)
plt.ylabel(‘X2’)
plt.xlabel(‘X1’)
```


---
## KNN邻近算法
K最邻近分类算法，或缩写为KNN，是一种有监督学习算法，专门用于分类。算法先关注不同类的中心，对比样本和类中心的距离（通常用欧几里得距离方程）。如果一个样本中的大多数属于某一个类别，则该样本都归属于这个类别。

你已经了解了KNN算法的内在概念，让我们在Python中实践一下。


```
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn aas sns
from sklearn.neighbors import KNeighborsClassifier

df = pd.read_csv(‘iris_df.csv’)
df.columns = [‘X1’, ‘X2’, ‘X3’, ‘X4’, ‘Y’]
df = df.drop([‘X4’, ‘X3’], 1)
df.head()

sns.set_context(“notebook”, font_scale=1.1)
sns.set_style(“ticks”)
sns.lmplot(‘X1’,’X2', scatter=True, fit_reg=False, data=df, hue=’Y’)
plt.ylabel(‘X2’)
plt.xlabel(‘X1’)

from sklearn.cross_validation import train_test_split

neighbors = KNeighborsClassifier(n_neighbors=5)
X = df.values[:, 0:2]
Y = df.values[:, 2]
trainX, testX, trainY, testY = train_test_split( X, Y, test_size = 0.3)
neighbors.fit(trainX, trainY)
print(‘Accuracy: \n’, neighbors.score(testX, testY))
pred = neighbors.predict(testX)


```


---
## 随机森林

随机森林是一种流行的有监督集成学习算法。集成的意思是把许多”弱学习器”结合在一起，形成一个强预测器。在本例中，每一个随机生成的决策树都是一个弱学习器，放在一起成为了一个强预测器—随机森林。


```
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn aas sns
from sklearn.ensemble import RandomForestClassifier

df = pd.read_csv(‘iris_df.csv’)
df.columns = [‘X1’, ‘X2’, ‘X3’, ‘X4’, ‘Y’]
df.head()

from sklearn.cross_validation import train_test_split
forest = RandomForestClassifier()
X = df.values[:, 0:4]
Y = df.values[:, 4]
trainX, testX, trainY, testY = train_test_split( X, Y, test_size = 0.3)
forest.fit(trainX, trainY)
print(‘Accuracy: \n’, forest.score(testX, testY))
pred = forest.predict(testX)


```


---
## K-Means 聚类算法

K-Means算法是一种流行的无监督学习分类算法，主要用于解决聚类问题。K 是用户预输入的分类数量。算法先随机选择K个点，然后用距离算法将剩下的对象分组，最终达到最优聚类。模型的好坏主要取决于数据科学家对K值的设定。


```
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn aas sns
from sklearn.cluster import KMeans

df = pd.read_csv(‘iris_df.csv’)
df.columns = [‘X1’, ‘X2’, ‘X3’, ‘X4’, ‘Y’]
df = df.drop([‘X4’, ‘X3’], 1)
df.head()

from sklearn.cross_validation import train_test_split

kmeans = KMeans(n_clusters=3)
X = df.values[:, 0:2]
kmeans.fit(X)
df[‘Pred’] = kmeans.predict(X)
df.head()

sns.set_context(“notebook”, font_scale=1.1)
sns.set_style(“ticks”)
sns.lmplot(‘X1’,’X2', scatter=True, fit_reg=False, data=df, hue = ‘Pred’)
```


---
## PCA主成分分析

主成分分析（PCA）是一种降维算法，可以为数据科学家做很多事。最主要的是，当模型有成百上千个不同特征需要处理时，主成分分析能极大地减少模型计算量。这是一种无监督模型，但使用者依然需要分析降维后的结果，确保其能保持原数据集95%左右的信息。


```
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn aas sns
from sklearn import decomposition

df = pd.read_csv(‘iris_df.csv’)
df.columns = [‘X1’, ‘X2’, ‘X3’, ‘X4’, ‘Y’]
df.head()

from sklearn import decomposition

pca = decomposition.PCA()
fa = decomposition.FactorAnalysis()
X = df.values[:, 0:4]
Y = df.values[:, 4]
train, test = train_test_split(X,test_size = 0.3)
train_reduced = pca.fit_transform(train)
test_reduced = pca.transform(test)
pca.n_components_

```


---
## 参考链接
[原文链接] (https://mp.weixin.qq.com/s/tN7KVBA9GqdjpAjW-_WF8Q)

