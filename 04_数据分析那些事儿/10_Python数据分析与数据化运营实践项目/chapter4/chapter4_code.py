# -*- coding: utf-8 -*-

'''
描述：跳过运营数据分析和挖掘的“大坑”
时间：2017-8-1
程序开发环境：win 64位
Python版本：32位 2.7.12
python IDE：PyCharm
依赖库：具体查看各模块
程序输入：具体查看各模块
程序输出：具体查看各模块
注意：Python的工作目录当前文件夹目录，如果不是请使用如下方法切换：
    点击PyCharm底部调试栏中的Python Console，如果按照本书的正常安装部署会调用iPython交互窗口；在打开的交互环境中输入cd [路径]。
    例如，在windows环境下输入：
    cd D:\4_附件\chapter4

'''
####################################################################
# 4.1 聚类分析
# 导入库
import numpy as np  # 导入numpy库
import matplotlib.pyplot as plt  # 导入matplotlib库
from sklearn.cluster import KMeans  # 导入sklearn聚类模块
from sklearn import metrics  # 导入sklearn效果评估模块

# 数据准备
raw_data = np.loadtxt('cluster.txt')  # 导入数据文件
X = raw_data[:, :-1]  # 分割要聚类的数据
y_true = raw_data[:, -1]

# 训练聚类模型
n_clusters = 3  # 设置聚类数量
model_kmeans = KMeans(n_clusters=n_clusters, random_state=0)  # 建立聚类模型对象
model_kmeans.fit(X)  # 训练聚类模型
y_pre = model_kmeans.predict(X)  # 预测聚类模型

# 模型效果指标评估
n_samples, n_features = X.shape  # 总样本量,总特征数
inertias = model_kmeans.inertia_  # 样本距离最近的聚类中心的总和
adjusted_rand_s = metrics.adjusted_rand_score(y_true, y_pre)  # 调整后的兰德指数
mutual_info_s = metrics.mutual_info_score(y_true, y_pre)  # 互信息
adjusted_mutual_info_s = metrics.adjusted_mutual_info_score(y_true, y_pre)  # 调整后的互信息
homogeneity_s = metrics.homogeneity_score(y_true, y_pre)  # 同质化得分
completeness_s = metrics.completeness_score(y_true, y_pre)  # 完整性得分
v_measure_s = metrics.v_measure_score(y_true, y_pre)  # V-measure得分
silhouette_s = metrics.silhouette_score(X, y_pre, metric='euclidean')  # 平均轮廓系数
calinski_harabaz_s = metrics.calinski_harabaz_score(X, y_pre)  # Calinski和Harabaz得分
print ('samples: %d \t features: %d' % (n_samples, n_features))  # 打印输出样本量和特征数量
print (70 * '-')  # 打印分隔线
print ('ine\tARI\tMI\tAMI\thomo\tcomp\tv_m\tsilh\tc&h')  # 打印输出指标标题
print ('%d\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%d' % (
inertias, adjusted_rand_s, mutual_info_s, adjusted_mutual_info_s, homogeneity_s, completeness_s, v_measure_s,
silhouette_s, calinski_harabaz_s))  # 打印输出指标值
print (70 * '-')  # 打印分隔线
print ('short name \t full name')  # 打印输出缩写和全名标题
print ('ine \t inertias')
print ('ARI \t adjusted_rand_s')
print ('MI \t mutual_info_s')
print ('AMI \t adjusted_mutual_info_s')
print ('homo \t homogeneity_s')
print ('comp \t completeness_s')
print ('v_m \t v_measure_s')
print ('silh \t silhouette_s')
print ('c&h \t calinski_harabaz_s')

# 模型效果可视化
centers = model_kmeans.cluster_centers_  # 各类别中心
colors = ['#4EACC5', '#FF9C34', '#4E9A06']  # 设置不同类别的颜色
plt.figure()  # 建立画布
for i in range(n_clusters):  # 循环读类别
    index_sets = np.where(y_pre == i)  # 找到相同类的索引集合
    cluster = X[index_sets]  # 将相同类的数据划分为一个聚类子集
    plt.scatter(cluster[:, 0], cluster[:, 1], c=colors[i], marker='.')  # 展示聚类子集内的样本点
    plt.plot(centers[i][0], centers[i][1], 'o', markerfacecolor=colors[i], markeredgecolor='k',
             markersize=6)  # 展示各聚类子集的中心
plt.show()  # 展示图像

# 模型应用
new_X = [1, 3.6]
cluster_label = model_kmeans.predict(np.array(new_X).reshape(1,-1))
print ('cluster of new data point is: %d' % cluster_label)

####################################################################
# 4.2 回归分析
# 导入库
import numpy as np  # numpy库
from sklearn.linear_model import BayesianRidge, LinearRegression, ElasticNet  # 批量导入要实现的回归算法
from sklearn.svm import SVR  # SVM中的回归算法
from sklearn.ensemble.gradient_boosting import GradientBoostingRegressor  # 集成算法
from sklearn.model_selection import cross_val_score  # 交叉检验
from sklearn.metrics import explained_variance_score, mean_absolute_error, mean_squared_error, r2_score  # 批量导入指标算法
import pandas as pd  # 导入pandas
import matplotlib.pyplot as plt  # 导入图形展示库

# 数据准备
raw_data = np.loadtxt('regression.txt')  # 读取数据文件
X = raw_data[:, :-1]  # 分割自变量
y = raw_data[:, -1]  # 分割因变量

# 训练回归模型
n_folds = 6  # 设置交叉检验的次数
model_br = BayesianRidge()  # 建立贝叶斯岭回归模型对象
model_lr = LinearRegression()  # 建立普通线性回归模型对象
model_etc = ElasticNet()  # 建立弹性网络回归模型对象
model_svr = SVR()  # 建立支持向量机回归模型对象
model_gbr = GradientBoostingRegressor()  # 建立梯度增强回归模型对象
model_names = ['BayesianRidge', 'LinearRegression', 'ElasticNet', 'SVR', 'GBR']  # 不同模型的名称列表
model_dic = [model_br, model_lr, model_etc, model_svr, model_gbr]  # 不同回归模型对象的集合
cv_score_list = []  # 交叉检验结果列表
pre_y_list = []  # 各个回归模型预测的y值列表
for model in model_dic:  # 读出每个回归模型对象
    scores = cross_val_score(model, X, y, cv=n_folds)  # 将每个回归模型导入交叉检验模型中做训练检验
    cv_score_list.append(scores)  # 将交叉检验结果存入结果列表
    pre_y_list.append(model.fit(X, y).predict(X))  # 将回归训练中得到的预测y存入列表

# 模型效果指标评估
n_samples, n_features = X.shape  # 总样本量,总特征数
model_metrics_name = [explained_variance_score, mean_absolute_error, mean_squared_error, r2_score]  # 回归评估指标对象集
model_metrics_list = []  # 回归评估指标列表
for i in range(5):  # 循环每个模型索引
    tmp_list = []  # 每个内循环的临时结果列表
    for m in model_metrics_name:  # 循环每个指标对象
        tmp_score = m(y, pre_y_list[i])  # 计算每个回归指标结果
        tmp_list.append(tmp_score)  # 将结果存入每个内循环的临时结果列表
    model_metrics_list.append(tmp_list)  # 将结果存入回归评估指标列表
df1 = pd.DataFrame(cv_score_list, index=model_names)  # 建立交叉检验的数据框
df2 = pd.DataFrame(model_metrics_list, index=model_names, columns=['ev', 'mae', 'mse', 'r2'])  # 建立回归指标的数据框
print ('samples: %d \t features: %d' % (n_samples, n_features))  # 打印输出样本量和特征数量
print (70 * '-')  # 打印分隔线
print ('cross validation result:')  # 打印输出标题
print (df1)  # 打印输出交叉检验的数据框
print (70 * '-')  # 打印分隔线
print ('regression metrics:')  # 打印输出标题
print (df2)  # 打印输出回归指标的数据框
print (70 * '-')  # 打印分隔线
print ('short name \t full name')  # 打印输出缩写和全名标题
print ('ev \t explained_variance')
print ('mae \t mean_absolute_error')
print ('mse \t mean_squared_error')
print ('r2 \t r2')
print (70 * '-')  # 打印分隔线

# 模型效果可视化
plt.figure()  # 创建画布
plt.plot(np.arange(X.shape[0]), y, color='k', label='true y')  # 画出原始值的曲线
color_list = ['r', 'b', 'g', 'y', 'c']  # 颜色列表
linestyle_list = ['-', '.', 'o', 'v', '*']  # 样式列表
for i, pre_y in enumerate(pre_y_list):  # 读出通过回归模型预测得到的索引及结果
    plt.plot(np.arange(X.shape[0]), pre_y_list[i], color_list[i], label=model_names[i])  # 画出每条预测结果线
plt.title('regression result comparison')  # 标题
plt.legend(loc='upper right')  # 图例位置
plt.ylabel('real and predicted value')  # y轴标题
plt.show()  # 展示图像

# 模型应用
print ('regression prediction')
new_point_set = [[1.05393, 0., 8.14, 0., 0.538, 5.935, 29.3, 4.4986, 4., 307., 21., 386.85, 6.58],
                 [0.7842, 0., 8.14, 0., 0.538, 5.99, 81.7, 4.2579, 4., 307., 21., 386.75, 14.67],
                 [0.80271, 0., 8.14, 0., 0.538, 5.456, 36.6, 3.7965, 4., 307., 21., 288.99, 11.69],
                 [0.7258, 0., 8.14, 0., 0.538, 5.727, 69.5, 3.7965, 4., 307., 21., 390.95, 11.28]]  # 要预测的新数据集
for i, new_point in enumerate(new_point_set):  # 循环读出每个要预测的数据点
    new_pre_y = model_gbr.predict(np.array(new_point).reshape(1,-1))  # 使用GBR进行预测
    print ('predict for new point %d is:  %.2f' % (i + 1, new_pre_y))  # 打印输出每个数据点的预测信息

####################################################################
# 4.3 分类分析
# 导入库
import numpy as np  # 导入numpy库
from sklearn.model_selection import train_test_split  # 数据分区库
from sklearn import tree  # 导入决策树库
from sklearn.metrics import accuracy_score, auc, confusion_matrix, f1_score, precision_score, recall_score, \
    roc_curve  # 导入指标库
import prettytable  # 导入表格库
import pydotplus  # 导入dot插件库
import matplotlib.pyplot as plt  # 导入图形展示库

# 数据准备
raw_data = np.loadtxt('classification.csv', delimiter=',', skiprows=1, )  # 读取数据文件
X = raw_data[:, :-1]  # 分割X
y = raw_data[:, -1]  # 分割y
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=.3, random_state=0)  # 将数据分为训练集和测试集

# 训练分类模型
model_tree = tree.DecisionTreeClassifier(random_state=0)  # 建立决策树模型对象
model_tree.fit(X_train, y_train)  # 训练决策树模型
pre_y = model_tree.predict(X_test)  # 使用测试集做模型效果检验

# 输出模型概况
n_samples, n_features = X.shape  # 总样本量,总特征数
print ('samples: %d \t features: %d' % (n_samples, n_features))  # 打印输出样本量和特征数量
print (70 * '-')  # 打印分隔线

# 混淆矩阵
confusion_m = confusion_matrix(y_test, pre_y)  # 获得混淆矩阵
confusion_matrix_table = prettytable.PrettyTable()  # 创建表格实例
confusion_matrix_table.add_row(confusion_m[0, :])  # 增加第一行数据
confusion_matrix_table.add_row(confusion_m[1, :])  # 增加第二行数据
print ('confusion matrix')
print (confusion_matrix_table)  # 打印输出混淆矩阵

# 核心评估指标
y_score = model_tree.predict_proba(X_test)  # 获得决策树的预测概率
fpr, tpr, thresholds = roc_curve(y_test, y_score[:, 1])  # ROC
auc_s = auc(fpr, tpr)  # AUC
accuracy_s = accuracy_score(y_test, pre_y)  # 准确率
precision_s = precision_score(y_test, pre_y)  # 精确度
recall_s = recall_score(y_test, pre_y)  # 召回率
f1_s = f1_score(y_test, pre_y)  # F1得分
core_metrics = prettytable.PrettyTable()  # 创建表格实例
core_metrics.field_names = ['auc', 'accuracy', 'precision', 'recall', 'f1']  # 定义表格列名
core_metrics.add_row([auc_s, accuracy_s, precision_s, recall_s, f1_s])  # 增加数据
print ('core metrics')
print (core_metrics)  # 打印输出核心评估指标

# 模型效果可视化
names_list = ['age', 'gender', 'income', 'rfm_score']  # 分类模型维度列表
color_list = ['r', 'c', 'b', 'g']  # 颜色列表
plt.figure()  # 创建画布
# 子网格1：ROC曲线
plt.subplot(1, 2, 1)  # 第一个子网格
plt.plot(fpr, tpr, label='ROC')  # 画出ROC曲线
plt.plot([0, 1], [0, 1], linestyle='--', color='k', label='random chance')  # 画出随机状态下的准确率线
plt.title('ROC')  # 子网格标题
plt.xlabel('false positive rate')  # X轴标题
plt.ylabel('true positive rate')  # y轴标题
plt.legend(loc=0)
# 子网格2：指标重要性
feature_importance = model_tree.feature_importances_  # 获得指标重要性
plt.subplot(1, 2, 2)  # 第二个子网格
plt.bar(np.arange(feature_importance.shape[0]), feature_importance, tick_label=names_list, color=color_list)  # 画出条形图
plt.title('feature importance')  # 子网格标题
plt.xlabel('features')  # x轴标题
plt.ylabel('importance')  # y轴标题
plt.suptitle('classification result')  # 图形总标题
plt.show()  # 展示图形

# 保存决策树规则图为PDF文件
dot_data = tree.export_graphviz(model_tree, out_file=None, max_depth=5, feature_names=names_list, filled=True,
                                rounded=True)  # 将决策树规则生成dot对象
graph = pydotplus.graph_from_dot_data(dot_data)  # 通过pydotplus将决策树规则解析为图形
graph.write_pdf("tree.pdf")  # 将决策树规则保存为PDF文件

# 模型应用
X_new = [[40, 0, 55616, 0], [17, 0, 55568, 0], [55, 1, 55932, 1]]
print ('classification prediction')
for i, data in enumerate(X_new):
    y_pre_new = model_tree.predict(np.array(data).reshape(1,-1))
    print ('classification for %d record is: %d' % (i + 1, y_pre_new))

####################################################################
# 4.4 关联分析
# 导入库
import sys

sys.path.append('../chapter4')
import pandas as pd
from graphviz import Digraph
import apriori

# 定义数据文件
fileName = 'association.txt'

# 通过调用自定义的apriori做关联分析
minS = 0.1  # 定义最小支持度阀值
minC = 0.38  # 定义最小置信度阀值
dataSet = apriori.createData(fileName)  # 获取格式化的数据集
L, suppData = apriori.apriori(dataSet, minSupport=minS)  # 计算得到满足最小支持度的规则
rules = apriori.generateRules(fileName, L, suppData, minConf=minC)  # 计算满足最小置信度的规则

# 关联结果报表评估
model_summary = 'data record: {1} \nassociation rules count: {0}'  # 展示数据集记录数和满足阀值定义的规则数量
print (model_summary.format(len(rules), len(dataSet)))  # 使用str.format做格式化输出
df = pd.DataFrame(rules, columns=['item1', 'itme2', 'instance', 'support', 'confidence', 'lift'])  # 创建频繁规则数据框
df_lift = df[df['lift'] > 1.0]  # 只选择提升度>1的规则
print (df_lift.sort('instance', ascending=False))  # 打印排序后的数据框

# 关联结果图形展示
dot = Digraph()  # 创建有向图
graph_data = df_lift[['item1', 'itme2', 'instance']]  # 切分画图用的前项、后项和实例数数据
for each_data in graph_data.values:  # 循环读出每条规则
    node1, node2, weight = each_data  # 分割每条数据画图用的前项、后项和实例数
    node1 = str(node1)  # 转化为字符串
    node2 = str(node2)  # 转化为字符串
    label = '%s' % weight  # 创建一个标签用于展示实例数
    dot.node(node1, node1, shape='record')  # 增加节点（规则中的前项）
    dot.edge(node1, node2, label=label, constraint='true')  # 增加有向边
dot.render('apriori', view=True)  # 保存规则为pdf文件

####################################################################
# 4.5 异常检测分析
# 导入库
from sklearn.svm import OneClassSVM  # 导入OneClassSVM
import numpy as np  # 导入numpy库
import matplotlib.pyplot as plt  # 导入Matplotlib
from mpl_toolkits.mplot3d import Axes3D  # 导入3D样式库

# 数据准备
raw_data = np.loadtxt('outlier.txt', delimiter=' ')  # 读取数据
train_set = raw_data[:900, :]  # 训练集
test_set = raw_data[900:, :]  # 测试集

# 异常数据检测
model_onecalsssvm = OneClassSVM(nu=0.1, kernel="rbf", random_state=0)  # 创建异常检测算法模型对象
model_onecalsssvm.fit(train_set)  # 训练模型
pre_test_outliers = model_onecalsssvm.predict(test_set)  # 异常检测

# 异常结果统计
toal_test_data = np.hstack((test_set, pre_test_outliers.reshape(test_set.shape[0], 1)))  # 将测试集和检测结果合并
normal_test_data = toal_test_data[toal_test_data[:, -1] == 1]  # 获得异常检测结果中正常数据集
outlier_test_data = toal_test_data[toal_test_data[:, -1] == -1]  # 获得异常检测结果中异常数据
n_test_outliers = outlier_test_data.shape[0]  # 获得异常的结果数量
total_count_test = toal_test_data.shape[0]  # 获得测试集样本量
print ('outliers: {0}/{1}'.format(n_test_outliers, total_count_test))  # 输出异常的结果数量
print ('{:*^60}'.format(' all result data (limit 5) '))  # 打印标题
print (toal_test_data[:5])  # 打印输出前5条合并后的数据集

# 异常检测结果展示
plt.style.use('ggplot')  # 使用ggplot样式库
fig = plt.figure()  # 创建画布对象
ax = Axes3D(fig)  # 将画布转换为3D类型
s1 = ax.scatter(normal_test_data[:, 0], normal_test_data[:, 1], normal_test_data[:, 2], s=100, edgecolors='k', c='g',
                marker='o')  # 画出正常样本点
s2 = ax.scatter(outlier_test_data[:, 0], outlier_test_data[:, 1], outlier_test_data[:, 2], s=100, edgecolors='k', c='r',
                marker='o')  # 画出异常样本点
ax.w_xaxis.set_ticklabels([])  # 隐藏x轴标签，只保留刻度线
ax.w_yaxis.set_ticklabels([])  # 隐藏y轴标签，只保留刻度线
ax.w_zaxis.set_ticklabels([])  # 隐藏z轴标签，只保留刻度线
ax.legend([s1, s2], ['normal points', 'outliers'], loc=0)  # 设置两类样本点的图例
plt.title('novelty detection')  # 设置图像标题
plt.show()  # 展示图像

####################################################################
# 4.6 时间序列分析
# 导入库
import pandas as pd  # pandas库
import numpy as np  # numpy库
from statsmodels.graphics.tsaplots import plot_acf, plot_pacf  # acf和pacf展示库
from statsmodels.tsa.stattools import adfuller  # adf检验库
from statsmodels.stats.diagnostic import acorr_ljungbox  # 随机性检验库
from statsmodels.tsa.arima_model import ARMA  # ARMA库
import matplotlib.pyplot as plt  # matplotlib图形展示库
import prettytable  # 导入表格库


# 多次用到的表格
def pre_table(table_name, table_rows):
    '''
    :param table_name: 表格名称，字符串列表
    :param table_rows: 表格内容，嵌套列表
    :return: 展示表格对象
    '''
    table = prettytable.PrettyTable()  # 创建表格实例
    table.field_names = table_name  # 定义表格列名
    for i in table_rows:  # 循环读多条数据
        table.add_row(i)  # 增加数据
    return table


# 数据平稳处理
def get_best_log(ts, max_log=5, rule1=True, rule2=True):
    '''
    :param ts: 时间序列数据，Series类型
    :param max_log: 最大log处理的次数，int型
    :param rule1: rule1规则布尔值，布尔型
    :param rule2: rule2规则布尔值，布尔型
    :return: 达到平稳处理的最佳次数值和处理后的时间序列
    '''
    if rule1 and rule2:  # 如果两个规则同时满足
        return 0, ts  # 直接返回0和原始时间序列数据
    else:  # 只要有一个规则不满足
        for i in range(1, max_log):  # 循环做log处理
            ts = np.log(ts)  # log处理
            adf, pvalue1, usedlag, nobs, critical_values, icbest = adfuller(ts)  # 稳定性（ADF）检验
            lbvalue, pvalue2 = acorr_ljungbox(ts, lags=1)  # 白噪声（随机性）检验
            rule_1 = (adf < critical_values['1%'] and adf < critical_values['5%'] and adf < critical_values[
                '10%'] and pvalue1 < 0.01)  # 稳定性（ADF）检验规则
            rule_2 = (pvalue2 < 0.05)  # 白噪声（随机性）规则
            rule_3 = (i < 5)
            if rule_1 and rule_2 and rule_3:  # 如果同时满足条件
                print ('The best log n is: {0}'.format(i))  # 打印输出最佳次数
                return i, ts  # 返回最佳次数和处理后的时间序列


# 还原经过平稳处理的数据
def recover_log(ts, log_n):
    '''
    :param ts: 经过log方法平稳处理的时间序列，Series类型
    :param log_n: log方法处理的次数，int型
    :return: 还原后的时间序列
    '''
    for i in range(1, log_n + 1):  # 循环多次
        ts = np.exp(ts)  # log方法还原
    return ts  # 返回时间序列


# 稳定性（ADF）检验
def adf_val(ts, ts_title, acf_title, pacf_title):
    '''
    :param ts: 时间序列数据，Series类型
    :param ts_title: 时间序列图的标题名称，字符串
    :param acf_title: acf图的标题名称，字符串
    :param pacf_title: pacf图的标题名称，字符串
    :return: adf值、adf的p值、三种状态的检验值
    '''
    plt.figure()
    plt.plot(ts)  # 时间序列图
    plt.title(ts_title)  # 时间序列标题
    plt.show()
    plot_acf(ts, lags=20, title=acf_title).show()  # 自相关检测
    plot_pacf(ts, lags=20, title=pacf_title).show()  # 偏相关检测
    adf, pvalue, usedlag, nobs, critical_values, icbest = adfuller(ts)  # 稳定性（ADF）检验
    table_name = ['adf', 'pvalue', 'usedlag', 'nobs', 'critical_values', 'icbest']  # 表格列名列表
    table_rows = [[adf, pvalue, usedlag, nobs, critical_values, icbest]]  # 表格行数据，嵌套列表
    adf_table = pre_table(table_name, table_rows)  # 获得平稳性展示表格对象
    print ('stochastic score')  # 打印标题
    print (adf_table)  # 打印展示表格
    return adf, pvalue, critical_values,  # 返回adf值、adf的p值、三种状态的检验值


# 白噪声（随机性）检验
def acorr_val(ts):
    '''
    :param ts: 时间序列数据，Series类型
    :return: 白噪声检验的P值和展示数据表格对象
    '''
    lbvalue, pvalue = acorr_ljungbox(ts, lags=1)  # 白噪声检验结果
    table_name = ['lbvalue', 'pvalue']  # 表格列名列表
    table_rows = [[lbvalue, pvalue]]  # 表格行数据，嵌套列表
    acorr_ljungbox_table = pre_table(table_name, table_rows)  # 获得白噪声检验展示表格对象
    print ('stationarity score')  # 打印标题
    print (acorr_ljungbox_table)  # 打印展示表格
    return pvalue  # 返回白噪声检验的P值和展示数据表格对象


# arma最优模型训练
def arma_fit(ts):
    '''
    :param ts: 时间序列数据，Series类型
    :return: 最优状态下的p值、q值、arma模型对象、pdq数据框和展示参数表格对象
    '''
    max_count = int(len(ts) / 10)  # 最大循环次数最大定义为记录数的10%
    bic = float('inf')  # 初始值为正无穷
    tmp_score = []  # 临时p、q、aic、bic和hqic的值的列表
    for tmp_p in range(max_count + 1):  # p循环max_count+1次
        for tmp_q in range(max_count + 1):  # q循环max_count+1次
            model = ARMA(ts, order=(tmp_p, tmp_q))  # 创建ARMA模型对象
            try:
                results_ARMA = model.fit(disp=-1, method='css')  # ARMA模型训练
            except:
                continue  # 遇到报错继续
            finally:
                tmp_aic = results_ARMA.aic  # 模型的获得aic
                tmp_bic = results_ARMA.bic  # 模型的获得bic
                tmp_hqic = results_ARMA.hqic  # 模型的获得hqic
                tmp_score.append([tmp_p, tmp_q, tmp_aic, tmp_bic, tmp_hqic])  # 追加每个模型的训练参数和结果
                if tmp_bic < bic:  # 如果模型bic小于最小值，那么获得最优模型ARMA的下列参数：
                    p = tmp_p  # 最优模型ARMA的p值
                    q = tmp_q  # 最优模型ARMA的q值
                    model_arma = results_ARMA  # 最优模型ARMA的模型对象
                    aic = tmp_bic  # 最优模型ARMA的aic
                    bic = tmp_bic  # 最优模型ARMA的bic
                    hqic = tmp_bic  # 最优模型ARMA的hqic
    pdq_metrix = np.array(tmp_score)  # 将嵌套列表转换为矩阵
    pdq_pd = pd.DataFrame(pdq_metrix, columns=['p', 'q', 'aic', 'bic', 'hqic'])  # 基于矩阵创建数据框
    table_name = ['p', 'q', 'aic', 'bic', 'hqic']  # 表格列名列表
    table_rows = [[p, q, aic, bic, hqic]]  # 表格行数据，嵌套列表
    parameter_table = pre_table(table_name, table_rows)  # 获得最佳ARMA模型结果展示表格对象
    print ('each p/q traning record')  # 打印标题
    print (pdq_pd)  # 打印输出每次ARMA拟合结果，包含p、d、q以及对应的AIC、BIC、HQIC
    print ('best p and q')  # 打印标题
    print (parameter_table)  # 输出最佳ARMA模型结果展示表格对象
    return model_arma  # 最优状态下的arma模型对象


# 模型训练和效果评估
def train_test(model_arma, ts, log_n, rule1=True, rule2=True):
    '''
    :param model_arma: 最优ARMA模型对象
    :param ts: 时间序列数据，Series类型
    :param log_n: 平稳性处理的log的次数，int型
    :param rule1: rule1规则布尔值，布尔型
    :param rule2: rule2规则布尔值，布尔型
    :return: 还原后的时间序列
    '''
    train_predict = model_arma.predict()  # 得到训练集的预测时间序列
    if not (rule1 and rule2):  # 如果两个条件有任意一个不满足
        train_predict = recover_log(train_predict, log_n)  # 恢复平稳性处理前的真实时间序列值
        ts = recover_log(ts, log_n)  # 时间序列还原处理
    ts_data_new = ts[train_predict.index]  # 将原始时间序列数据的长度与预测的周期对齐
    RMSE = np.sqrt(np.sum((train_predict - ts_data_new) ** 2) / ts_data_new.size)  # 求RMSE
    # 对比训练集的预测和真实数据
    plt.figure()  # 创建画布
    train_predict.plot(label='predicted data', style='--')  # 以虚线展示预测数据
    ts_data_new.plot(label='raw data')  # 以实线展示原始数据
    plt.legend(loc='best')  # 设置图例位置
    plt.title('raw data and predicted data with RMSE of %.2f' % RMSE)  # 设置标题
    plt.show()  # 展示图像
    return ts  # 返回还原后的时间序列


# 预测未来指定时间项的数据
def predict_data(model_arma, ts, log_n, start, end, rule1=True, rule2=True):
    '''
    :param model_arma: 最优ARMA模型对象
    :param ts: 时间序列数据，Series类型
    :param log_n: 平稳性处理的log的次数，int型
    :param start: 要预测数据的开始时间索引
    :param end: 要预测数据的结束时间索引
    :param rule1: rule1规则布尔值，布尔型
    :param rule2: rule2规则布尔值，布尔型
    :return: 无
    '''
    predict_ts = model_arma.predict(start=start, end=end)  # 预测未来指定时间项的数据
    print ('-----------predict data----------')  # 打印标题
    if not (rule1 and rule2):  # 如果两个条件有任意一个不满足
        predict_ts = recover_log(predict_ts, log_n)  # 还原数据
    print (predict_ts)  # 展示预测数据
    # 展示预测趋势
    plt.figure()  # 创建画布
    ts.plot(label='raw time series')  # 设置推向标签
    predict_ts.plot(label='predicted data', style='--')  # 以虚线展示预测数据
    plt.legend(loc='best')  # 设置图例位置
    plt.title('predicted time series')  # 设置标题
    plt.show()  # 展示图像


# 读取数据
date_parse = lambda dates: pd.datetime.strptime(dates, '%m-%d-%Y')  # 创建解析列的功能对象
df = pd.read_table('time_series.txt', delimiter='\t', index_col='date', date_parser=date_parse)  # 读取数据
ts_data = df['number'].astype('float32')  # 将列转换为float32类型
print ('data summary')  # 打印标题
print (ts_data.describe())  # 打印输出时间序列数据概况
# 原始数据检验
adf, pvalue1, critical_values = adf_val(ts_data, 'raw time series', 'raw acf', 'raw pacf')  # 稳定性检验
pvalue2 = acorr_val(ts_data)  # 白噪声检验
# 创建用于区分是否进行平稳性处理的规则
rule1 = (adf < critical_values['1%'] and adf < critical_values['5%'] and adf < critical_values[
    '10%'] and pvalue1 < 0.01)  # 稳定性检验
rule2 = (pvalue2[0,] < 0.05)  # 白噪声检验
# 对时间序列做稳定性处理
log_n, ts_data = get_best_log(ts_data, max_log=5, rule1=rule1, rule2=rule2)
# 再次做检验
adf, pvalue1, critical_values = adf_val(ts_data, 'final time series', 'final acf', 'final pacf')  # 稳定性检验
pvalue2 = acorr_val(ts_data)  # 白噪声检验
# 训练最佳ARMA模型并输出相关参数和对象
model_arma = arma_fit(ts_data)
# 模型训练和效果评估
ts_data = train_test(model_arma, ts_data, log_n, rule1=rule1, rule2=rule2)
# 模型预测应用
start = '1991-07-28'  # 设置预测开始的时间索引
end = '1991-08-02'  # 设置预测结束的时间索引
predict_data(model_arma, ts_data, log_n, start, end, rule1=rule1, rule2=rule2)  # 预测时间序列数据

####################################################################
# 4.9.1 词频统计
# 导入库
import re  # 正则表达式库
import collections  # 词频统计库
import numpy as np  # numpy库
import jieba  # 结巴分词
import wordcloud  # 词云展示库
from PIL import Image  # 图像处理库
import matplotlib.pyplot as plt  # 图像展示库

# 读取文本文件
fn = open('article1.txt')  # 以只读方式打开文件
string_data = fn.read()  # 使用read方法读取整段文本
fn.close()  # 关闭文件对象

# 文本预处理
pattern = re.compile(u'\t|\n|\.|-|一|:|;|\)|\(|\?|"')  # 建立正则表达式匹配模式
string_data = re.sub(pattern, '', string_data)  # 将符合模式的字符串替换掉

# 文本分词
seg_list_exact = jieba.cut(string_data, cut_all=False)  # 精确模式分词[默认模式]
object_list = []  # 建立空列表用于存储分词结果
remove_words = [u'的', u'，', u'和', u'是', u'随着', u'对于', ' ', u'对', u'等', u'能', u'都', u'。',
                u'、', u'中', u'与', u'在', u'其', u'了', u'可以', u'进行', u'有', u'更', u'需要', u'提供',
                u'多', u'能力', u'通过', u'会', u'不同', u'一个', u'这个', u'我们', u'将', u'并',
                u'同时', u'看', u'如果', u'但', u'到', u'非常', u'—', u'如何', u'包括', u'这']  # 自定义去除词库
# remove_words = [] #空去除词列表，用于跟关键字提取做效果对比
for word in seg_list_exact:  # 迭代读出每个分词对象
    if word not in remove_words:  # 如果不在去除词库中
        object_list.append(word)  # 分词追加到列表

# 词频统计
word_counts = collections.Counter(object_list)  # 对分词做词频统计
word_counts_top5 = word_counts.most_common(5)  # 获取前10个频率最高的词
for w, c in word_counts_top5:  # 分别读出每条词和出现从次数
    print w, c  # 打印输出

# 词频展示
mask = np.array(Image.open('wordcloud.jpg'))  # 定义词频背景
wc = wordcloud.WordCloud(
    font_path='C:/Windows/Fonts/simhei.ttf',  # 设置字体格式，不设置将无法显示中文
    mask=mask,  # 设置背景图
    max_words=200,  # 设置最大显示的词数
    max_font_size=100  # 设置字体最大值
)
wc.generate_from_frequencies(word_counts)  # 从字典生成词云
image_colors = wordcloud.ImageColorGenerator(mask)  # 从背景图建立颜色方案
wc.recolor(color_func=image_colors)  # 将词云颜色设置为背景图方案
plt.imshow(wc)  # 显示词云
plt.axis('off')  # 关闭坐标轴
plt.show()  # 显示图像

####################################################################
# 4.9.2 词性标注
# 导入库
import jieba.posseg as pseg
import pandas as pd

# 读取文本文件
fn = open('article1.txt')  # 以只读方式打开文件
string_data = fn.read()  # 使用read方法读取整段文本
fn.close()  # 关闭文件对象

# 分词+词性标注
words = pseg.cut(string_data)  # 分词
words_list = []  # 空列表用于存储分词和词性分类
for word in words:  # 循环得到每个分词
    words_list.append((word.word, word.flag))  # 将分词和词性分类追加到列表
words_pd = pd.DataFrame(words_list, columns=['word', 'type'])  # 创建结果数据框
print (words_pd.head(4))  # 展示结果前4条

# 词性分类汇总-两列分类
words_gb = words_pd.groupby(['type', 'word'])['word'].count()
print (words_gb.head(4))

# 词性分类汇总-单列分类
words_gb2 = words_pd.groupby('type').count()
words_gb2 = words_gb2.sort_values(by='word', ascending=False)
print (words_gb2.head(4))

# 选择特定类型词语做展示
words_pd_index = words_pd['type'].isin(['n', 'eng'])
words_pd_select = words_pd[words_pd_index]
print (words_pd_select.head(4))

####################################################################
# 4.9.3 关键字提取
# 导入库
import jieba.analyse  # 导入关键字提取库
import pandas as pd  # 导入pandas

# 读取文本数据
fn = open('article1.txt')  # 以只读方式打开文件
string_data = fn.read()  # 使用read方法读取整段文本
fn.close()  # 关闭文件对象

# 关键字提取
tags_pairs = jieba.analyse.extract_tags(string_data, topK=5, withWeight=True, allowPOS=['ns', 'n', 'vn', 'v', 'nr'],
                                        withFlag=True)  # 提取关键字标签
tags_list = []  # 空列表用来存储拆分后的三个值
for i in tags_pairs:  # 打印标签、分组和TF-IDF权重
    tags_list.append((i[0].word, i[0].flag, i[1]))  # 拆分三个字段值
tags_pd = pd.DataFrame(tags_list, columns=['word', 'flag', 'weight'])  # 创建数据框
print (tags_pd)  # 打印数据框

####################################################################
# 4.9.4 文本聚类
# 导入库
import numpy as np
import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer  # 基于TF-IDF的词频转向量库
from sklearn.cluster import KMeans
import jieba.posseg as pseg


# 中文分词
def jieba_cut(comment):
    word_list = []  # 建立空列表用于存储分词结果
    seg_list = pseg.cut(comment)  # 精确模式分词[默认模式]
    for word in seg_list:
        if word.flag in ['a', 'ag', 'an']:  # 只选择形容词
            word_list.append(word.word)  # 分词追加到列表
    return word_list


# 读取数据文件
fn = open('comment.txt')
comment_list = fn.readlines()  # 读取文件内容为列表
fn.close()

# word to vector
stop_words = [u'…', u'。', u'，', u'？', u'！', u'+', u' ', u'、', u'：', u'；', u'（', u'）', u'.', u'-']  # 定义停用词
vectorizer = TfidfVectorizer(stop_words=stop_words, tokenizer=jieba_cut, use_idf=True)  # 创建词向量模型
X = vectorizer.fit_transform(comment_list)  # 将评论关键字列表转换为词向量空间模型

# K均值聚类
model_kmeans = KMeans(n_clusters=3)  # 创建聚类模型对象
model_kmeans.fit(X)  # 训练模型

# 聚类结果汇总
cluster_labels = model_kmeans.labels_  # 聚类标签结果
word_vectors = vectorizer.get_feature_names()  # 词向量
word_values = X.toarray()  # 向量值
comment_matrix = np.hstack((word_values, cluster_labels.reshape(word_values.shape[0], 1)))  # 将向量值和标签值合并为新的矩阵
word_vectors.append('cluster_labels')  # 将新的聚类标签列表追加到词向量后面
comment_pd = pd.DataFrame(comment_matrix, columns=word_vectors)  # 创建包含词向量和聚类标签的数据框
print (comment_pd.head(1))  # 打印输出数据框第1条数据

# 聚类结果分析
comment_cluster1 = comment_pd[comment_pd['cluster_labels'] == 2].drop('cluster_labels', axis=1)  # 选择聚类标签值为2的数据，并删除最后一列
word_importance = np.sum(comment_cluster1, axis=0)  # 按照词向量做汇总统计
print (word_importance.sort_values(ascending=False)[:5])  # 按汇总统计的值做逆序排序并打印输出前5个词
