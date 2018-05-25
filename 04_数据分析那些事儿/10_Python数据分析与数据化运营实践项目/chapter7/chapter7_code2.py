# -*- coding: utf-8 -*-

'''
描述：案例-基于自动K值的KMeans广告效果聚类分析
时间：2017-11-1
程序开发环境：win 64位
Python版本：32位 2.7.12
python IDE：PyCharm
依赖库：sys、numpy、pandas、sklearn
程序输入：ad_performance.txt
程序输出：打印输出不同聚类类别的信息
注意：Python的工作目录当前文件夹目录，如果不是请使用如下方法切换：
    点击PyCharm底部调试栏中的Python Console，如果按照本书的正常安装部署会调用iPython交互窗口；在打开的交互环境中输入cd [路径]。
    例如，在windows环境下输入：
    cd D:\4_附件\chapter7

'''

# 导入库
import sys

reload(sys)
sys.setdefaultencoding('utf-8')
import pandas as pd
import numpy as np
from sklearn.feature_extraction import DictVectorizer  # 字符串分类转整数分类库
from sklearn.preprocessing import MinMaxScaler  # MinMaxScaler库
from sklearn.cluster import KMeans  # KMeans模块
from sklearn import metrics  # 导入sklearn效果评估模块
import matplotlib.pyplot as plt  # 图形库

# 读取数据
raw_data = pd.read_table('ad_performance.txt', delimiter='\t')

# 数据审查和校验
print ('{:*^60}'.format('Data overview:'))
print (raw_data.head(2))  # 打印输出前2条数据
print ('{:*^60}'.format('Data dtypes:'))
print (pd.DataFrame(raw_data.dtypes).T)  # 打印数据类型分布
print ('{:*^60}'.format(' NA counts:'))
print (pd.DataFrame(raw_data.isnull().sum()).T)  # 查看缺失值情况
print ('{:*^60}'.format('Data DESC:'))
print (raw_data.describe().round(2).T)  # 打印原始数据基本描述性信息
print ('{:*^60}'.format('Correlation analysis:'))
print (raw_data.corr().round(2).T)  # 打印原始数据相关性信息

# 数据预处理
# 缺失值替换为均值
data_fillna = raw_data.fillna(raw_data['平均停留时间'].mean())  # 用均值替换缺失值

# 字符串分类转整数分类
# part1
conver_cols = ['素材类型', '广告类型', '合作方式', '广告尺寸', '广告卖点']
convert_matrix = data_fillna[conver_cols]  # 获得要转换的数组
lines = data_fillna.shape[0]  # 获得总记录数
dict_list = []  # 总空列表，用于存放字符串与对应索引组成的字典
unique_list = []  # 总唯一值列表，用于存储每个列的唯一值列表
# part2
for col_name in conver_cols:  # 循环读取每个列名
    cols_unqiue_value = data_fillna[col_name].unique().tolist()  # 获取列的唯一值列表
    unique_list.append(cols_unqiue_value)  # 将唯一值列表追加到总列表
# part3
for line_index in range(lines):  # 读取每行索引
    each_record = convert_matrix.iloc[line_index]  # 获得每行数据，是一个Series
    for each_index, each_data in enumerate(each_record):  # 读取Series每行对应的索引值
        list_value = unique_list[each_index]  # 读取该行索引对应到总唯一值列表列索引下的数据(其实是相当于原来的列做了转置成了行，目的是查找唯一值在列表中的位置)
        each_record[each_index] = list_value.index(each_data)  # 获得每个值对应到总唯一值列表中的索引
    each_dict = dict(zip(conver_cols, each_record))  # 将每个值和对应的索引组合字典
    dict_list.append(each_dict)  # 将字典追加到总列表
# part4
model_dvtransform = DictVectorizer(sparse=False, dtype=np.int64)  # 建立转换模型对象
data_dictvec = model_dvtransform.fit_transform(dict_list)  # 应用分类转换训练

# 数据标准化
sacle_matrix = data_fillna.ix[:, 1:8]  # 获得要转换的矩阵
minmax_scaler = MinMaxScaler()  # 建立MinMaxScaler模型对象
data_scaled = minmax_scaler.fit_transform(sacle_matrix)  # MinMaxScaler标准化处理

# 合并所有输入维度
X = np.hstack((data_scaled, data_dictvec))

# 通过平均轮廓系数检验得到最佳KMeans聚类模型
score_list = list()  # 用来存储每个K下模型的平局轮廓系数
silhouette_int = -1  # 初始化的平均轮廓系数阀值
for n_clusters in range(2, 10):  # 遍历从2到10几个有限组
    model_kmeans = KMeans(n_clusters=n_clusters, random_state=0)  # 建立聚类模型对象
    cluster_labels_tmp = model_kmeans.fit_predict(X)  # 训练聚类模型
    silhouette_tmp = metrics.silhouette_score(X, cluster_labels_tmp)  # 得到每个K下的平均轮廓系数
    if silhouette_tmp > silhouette_int:  # 如果平均轮廓系数更高
        best_k = n_clusters  # 将最好的K存储下来
        silhouette_int = silhouette_tmp  # 将最好的平均轮廓得分存储下来
        best_kmeans = model_kmeans  # 将最好的模型存储下来
        cluster_labels_k = cluster_labels_tmp  # 将最好的聚类标签存储下来
    score_list.append([n_clusters, silhouette_tmp])  # 将每次K及其得分追加到列表
print ('{:*^60}'.format('K value and silhouette summary:'))
print (np.array(score_list))  # 打印输出所有K下的详细得分
print ('Best K is:{0} with average silhouette of {1}'.format(best_k, silhouette_int.round(4)))

# 针对聚类结果的特征分析
# part1
cluster_labels = pd.DataFrame(cluster_labels_k, columns=['clusters'])  # 获得训练集下的标签信息
merge_data = pd.concat((data_fillna, cluster_labels), axis=1)  # 将原始处理过的数据跟聚类标签整合
# part2
clustering_count = pd.DataFrame(merge_data['渠道代号'].groupby(merge_data['clusters']).count()).T.rename(
    {'渠道代号': 'counts'})  # 计算每个聚类类别的样本量
clustering_ratio = (clustering_count / len(merge_data)).round(2).rename({'counts': 'percentage'})  # 计算每个聚类类别的样本量占比
# part3
cluster_features = []  # 空列表，用于存储最终合并后的所有特征信息
for line in range(best_k):  # 读取每个类索引
    label_data = merge_data[merge_data['clusters'] == line]  # 获得特定类的数据

    part1_data = label_data.ix[:, 1:8]  # 获得数值型数据特征
    part1_desc = part1_data.describe().round(3)  # 得到数值型特征的描述性统计信息
    merge_data1 = part1_desc.ix[2, :]  # 得到数值型特征的均值

    part2_data = label_data.ix[:, 8:-1]  # 获得字符串型数据特征
    part2_desc = part2_data.describe(include='all')  # 获得字符串型数据特征的描述性统计信息
    merge_data2 = part2_desc.ix[2, :]  # 获得字符串型数据特征的最频繁值

    merge_line = pd.concat((merge_data1, merge_data2), axis=0)  # 将数值型和字符串型典型特征沿行合并
    cluster_features.append(merge_line)  # 将每个类别下的数据特征追加到列表
# part4
cluster_pd = pd.DataFrame(cluster_features).T  # 将列表转化为矩阵
print ('{:*^60}'.format('Detailed features for all clusters:'))
all_cluster_set = pd.concat((clustering_count, clustering_ratio, cluster_pd), axis=0)  # 将每个聚类类别的所有信息合并
print (all_cluster_set)

# 各类别显著数值特征对比
# part1
num_sets = cluster_pd.ix[:6, :].T.astype(np.float64)  # 获取要展示的数据
num_sets_max_min = minmax_scaler.fit_transform(num_sets)  # 获得标准化后的数据
# part2
fig = plt.figure()  # 建立画布
ax = fig.add_subplot(111, polar=True)  # 增加子网格，注意polar参数
labels = np.array(merge_data1.index[:-1])  # 设置要展示的数据标签
cor_list = ['r', 'g', 'b', 'y']  # 定义不同类别的颜色
angles = np.linspace(0, 2 * np.pi, len(labels), endpoint=False)  # 计算各个区间的角度
angles = np.concatenate((angles, [angles[0]]))  # 建立相同首尾字段以便于闭合
# part3
for i in range(len(num_sets)):  # 循环每个类别
    data_tmp = num_sets_max_min[i, :]  # 获得对应类数据
    data = np.concatenate((data_tmp, [data_tmp[0]]))  # 建立相同首尾字段以便于闭合
    ax.plot(angles, data, 'o-', c=cor_list[i], label=i)  # 画线
# part4
ax.set_thetagrids(angles * 180 / np.pi, labels, fontproperties="SimHei")  # 设置极坐标轴
ax.set_title("各聚类类别显著特征对比", fontproperties="SimHei")  # 设置标题放置
ax.set_rlim(-0.2, 1.2)  # 设置坐标轴尺度范围
plt.legend(loc=0)  # 设置图例位置
plt.show()  # 展示图像
