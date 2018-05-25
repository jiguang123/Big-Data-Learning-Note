# -*- coding: utf-8 -*-

'''
描述：11条数据化运营不得不知道的数据预处理经验
时间：2017-7-1
程序开发环境：win 64位
Python版本：32位 2.7.12
python IDE：PyCharm
依赖库：具体查看各模块
程序输入：具体查看各模块
程序输出：具体查看各模块
注意：Python的工作目录当前文件夹目录，如果不是请使用如下方法切换：
    点击PyCharm底部调试栏中的Python Console，如果按照本书的正常安装部署会调用iPython交互窗口；在打开的交互环境中输入cd [路径]。
    例如，在windows环境下输入：
    cd D:\4_附件\chapter3

'''
####################################################################
# 3.1 数据清洗：缺失值、异常值和重复值的处理
## 缺失值处理
import pandas as pd  # 导入pandas库
import numpy as np  # 导入numpy库
from sklearn.preprocessing import Imputer  # 导入sklearn.preprocessing中的Imputer库

# 生成缺失数据
df = pd.DataFrame(np.random.randn(6, 4), columns=['col1', 'col2', 'col3', 'col4'])  # 生成一份数据
df.iloc[1:2, 1] = np.nan  # 增加缺失值
df.iloc[4, 3] = np.nan  # 增加缺失值
print (df)

# 查看哪些值缺失
nan_all = df.isnull()  # 获得所有数据框中的N值
print (nan_all)  # 打印输出
# 查看哪些列缺失
nan_col1 = df.isnull().any()  # 获得含有NA的列
nan_col2 = df.isnull().all()  # 获得全部为NA的列
print (nan_col1)  # 打印输出
print (nan_col2)  # 打印输出

# 丢弃缺失值
df2 = df.dropna()  # 直接丢弃含有NA的行记录
print (df2)  # 打印输出

# 使用sklearn将缺失值替换为特定值
nan_model = Imputer(missing_values='NaN', strategy='mean', axis=0)  # 建立替换规则：将值为Nan的缺失值以均值做替换
nan_result = nan_model.fit_transform(df)  # 应用模型规则
print (nan_result)  # 打印输出

# 使用pandas将缺失值替换为特定值
nan_result_pd1 = df.fillna(method='backfill')  # 用后面的值替换缺失值
nan_result_pd2 = df.fillna(method='bfill', limit=1)  # 用后面的值替代缺失值,限制每列只能替代一个缺失值
nan_result_pd3 = df.fillna(method='pad')  # 用前面的值替换缺失值
nan_result_pd4 = df.fillna(0)  # 用0替换缺失值
nan_result_pd5 = df.fillna({'col2': 1.1, 'col4': 1.2})  # 用不同值替换不同列的缺失值
nan_result_pd6 = df.fillna(df.mean()['col2':'col4'])  # 用平均数代替,选择各自列的均值替换缺失值
# 打印输出
print (nan_result_pd1)  # 打印输出
print (nan_result_pd2)  # 打印输出
print (nan_result_pd3)  # 打印输出
print (nan_result_pd4)  # 打印输出
print (nan_result_pd5)  # 打印输出
print (nan_result_pd6)  # 打印输出

## 异常值处理
import pandas as pd  # 导入pandas库

# 生成异常数据
df = pd.DataFrame({'col1': [1, 120, 3, 5, 2, 12, 13],
                   'col2': [12, 17, 31, 53, 22, 32, 43]})
print (df)  # 打印输出

# 通过Z-Score方法判断异常值
df_zscore = df.copy()  # 复制一个用来存储Z-score得分的数据框
cols = df.columns  # 获得数据框的列名
for col in cols:  # 循环读取每列
    df_col = df[col]  # 得到每列的值
    z_score = (df_col - df_col.mean()) / df_col.std()  # 计算每列的Z-score得分
    df_zscore[col] = z_score.abs() > 2.2  # 判断Z-score得分是否大于2.2，如果是则是True，否则为False
print (df_zscore)  # 打印输出

## 重复值处理
import pandas as pd  # 导入pandas库

# 生成重复数据
data1 = ['a', 3]
data2 = ['b', 2]
data3 = ['a', 3]
data4 = ['c', 2]
df = pd.DataFrame([data1, data2, data3, data4], columns=['col1', 'col2'])
print (df)

# 判断重复数据
isDuplicated = df.duplicated()  # 判断重复数据记录
print (isDuplicated)  # 打印输出

# 删除重复值
new_df1 = df.drop_duplicates()  # 删除数据记录中所有列值相同的记录
new_df2 = df.drop_duplicates(['col1'])  # 删除数据记录中col1值相同的记录
new_df3 = df.drop_duplicates(['col2'])  # 删除数据记录中col2值相同的记录
new_df4 = df.drop_duplicates(['col1', 'col2'])  # 删除数据记录中指定列（col1/col2）值相同的记录
print (new_df1)  # 打印输出
print (new_df2)  # 打印输出
print (new_df3)  # 打印输出
print (new_df4)  # 打印输出

####################################################################
# 3.2 将分类数据和顺序数据转换为标志变量
import pandas as pd  # 导入pandas库
from sklearn.preprocessing import OneHotEncoder  # 导入OneHotEncoder库

# 生成数据
df = pd.DataFrame({'id': [3566841, 6541227, 3512441],
                   'sex': ['male', 'Female', 'Female'],
                   'level': ['high', 'low', 'middle']})
print (df)  # 打印输出原始数据框

# 自定义转换主过程
df_new = df.copy()  # 复制一份新的数据框用来存储转换结果
for col_num, col_name in enumerate(df):  # 循环读出每个列的索引值和列名
    col_data = df[col_name]  # 获得每列数据
    col_dtype = col_data.dtype  # 获得每列dtype类型
    if col_dtype == 'object':  # 如果dtype类型是object（非数值型），执行条件
        df_new = df_new.drop(col_name, 1)  # 删除df数据框中要进行标志转换的列
        value_sets = col_data.unique()  # 获取分类和顺序变量的唯一值域
        for value_unique in value_sets:  # 读取分类和顺序变量中的每个值
            col_name_new = col_name + '_' + value_unique  # 创建新的列名，使用原标题+值的方式命名
            col_tmp = df.iloc[:, col_num]  # 获取原始数据列
            new_col = (col_tmp == value_unique)  # 将原始数据列与每个值进行比较，相同为True，否则为False
            df_new[col_name_new] = new_col  # 为最终结果集增加新列值
print (df_new)  # 打印输出转换后的数据框

# 使用sklearn进行标志转换
df2 = pd.DataFrame({'id': [3566841, 6541227, 3512441],
                    'sex': [1, 2, 2],
                    'level': [3, 1, 2]})
id_data = df2.values[:, :1]  # 获得ID列
transform_data = df2.values[:, 1:]  # 指定要转换的列
enc = OneHotEncoder()  # 建立模型对象
df2_new = enc.fit_transform(transform_data).toarray()  # 标志转换
df2_all = pd.concat((pd.DataFrame(id_data), pd.DataFrame(df2_new)), axis=1)  # 组合为数据框
print (df2_all)  # 打印输出转换后的数据框

####################################################################
# 3.3 大数据时代，数据化运营还需要降维吗
import numpy as np
from sklearn.tree import DecisionTreeClassifier
from sklearn.decomposition import PCA

# 读取数据文件
data = np.loadtxt('data1.txt')  # 读取文本数据文件
x = data[:, :-1]  # 获得输入的x
y = data[:, -1]  # 获得目标变量y
print (x[0], y[0])  # 打印输出x和y的第一条记录

# 使用sklearn的DecisionTreeClassifier判断变量重要性
model_tree = DecisionTreeClassifier(random_state=0)  # 建立分类决策树模型对象
model_tree.fit(x, y)  # 将数据集的维度和目标变量输入模型
feature_importance = model_tree.feature_importances_  # 获得所有变量的重要性得分
print (feature_importance)  # 打印输出

# 使用sklearn的PCA进行维度转换
model_pca = PCA()  # 建立PCA模型对象
model_pca.fit(x)  # 将数据集输入模型
model_pca.transform(x)  # 对数据集进行转换映射
components = model_pca.components_  # 获得转换后的所有主成分
components_var = model_pca.explained_variance_  # 获得各主成分的方差
components_var_ratio = model_pca.explained_variance_ratio_  # 获得各主成分的方差占比
print (components[:2])  # 打印输出前2个主成分
print (components_var[:2])  # 打印输出前2个主成分的方差
print (components_var_ratio)  # 打印输出所有主成分的方差占比

####################################################################
# 3.4 解决样本类别分布不均衡的问题
import pandas as pd
from imblearn.over_sampling import SMOTE  # 过抽样处理库SMOTE
from imblearn.under_sampling import RandomUnderSampler  # 欠抽样处理库RandomUnderSampler
from sklearn.svm import SVC  # SVM中的分类算法SVC
from imblearn.ensemble import EasyEnsemble  # 简单集成方法EasyEnsemble

# 导入数据文件
df = pd.read_table('data2.txt', sep=' ', names=['col1', 'col2', 'col3', 'col4', 'col5', 'label'])  # 读取数据文件
x = df.iloc[:, :-1]  # 切片，得到输入x
y = df.iloc[:, -1]  # 切片，得到标签y
groupby_data_orgianl = df.groupby('label').count()  # 对label做分类汇总
print (groupby_data_orgianl)  # 打印输出原始数据集样本分类分布

# 使用SMOTE方法进行过抽样处理
model_smote = SMOTE()  # 建立SMOTE模型对象
x_smote_resampled, y_smote_resampled = model_smote.fit_sample(x, y)  # 输入数据并作过抽样处理
x_smote_resampled = pd.DataFrame(x_smote_resampled, columns=['col1', 'col2', 'col3', 'col4', 'col5'])  # 将数据转换为数据框并命名列名
y_smote_resampled = pd.DataFrame(y_smote_resampled, columns=['label'])  # 将数据转换为数据框并命名列名
smote_resampled = pd.concat([x_smote_resampled, y_smote_resampled], axis=1)  # 按列合并数据框
groupby_data_smote = smote_resampled.groupby('label').count()  # 对label做分类汇总
print (groupby_data_smote)  # 打印输出经过SMOTE处理后的数据集样本分类分布

# 使用RandomUnderSampler方法进行欠抽样处理
model_RandomUnderSampler = RandomUnderSampler()  # 建立RandomUnderSampler模型对象
x_RandomUnderSampler_resampled, y_RandomUnderSampler_resampled = model_RandomUnderSampler.fit_sample(x,
                                                                                                     y)  # 输入数据并作欠抽样处理
x_RandomUnderSampler_resampled = pd.DataFrame(x_RandomUnderSampler_resampled,
                                              columns=['col1', 'col2', 'col3', 'col4', 'col5'])  # 将数据转换为数据框并命名列名
y_RandomUnderSampler_resampled = pd.DataFrame(y_RandomUnderSampler_resampled, columns=['label'])  # 将数据转换为数据框并命名列名
RandomUnderSampler_resampled = pd.concat([x_RandomUnderSampler_resampled, y_RandomUnderSampler_resampled],
                                         axis=1)  # 按列合并数据框
groupby_data_RandomUnderSampler = RandomUnderSampler_resampled.groupby('label').count()  # 对label做分类汇总
print (groupby_data_RandomUnderSampler)  # 打印输出经过RandomUnderSampler处理后的数据集样本分类分布

# 使用SVM的权重调节处理不均衡样本
model_svm = SVC(class_weight='balanced')  # 创建SVC模型对象并指定类别权重
model_svm.fit(x, y)  # 输入x和y并训练模型

# 使用集成方法EasyEnsemble处理不均衡样本
model_EasyEnsemble = EasyEnsemble()  # 建立EasyEnsemble模型对象
x_EasyEnsemble_resampled, y_EasyEnsemble_resampled = model_EasyEnsemble.fit_sample(x, y)  # 输入数据并应用集成方法处理
print (x_EasyEnsemble_resampled.shape)  # 打印输出集成方法处理后的x样本集概况
print (y_EasyEnsemble_resampled.shape)  # 打印输出集成方法处理后的y标签集概况

# 抽取其中一份数据做审查
index_num = 1  # 设置抽样样本集索引
x_EasyEnsemble_resampled_t = pd.DataFrame(x_EasyEnsemble_resampled[index_num],
                                          columns=['col1', 'col2', 'col3', 'col4', 'col5'])  # 将数据转换为数据框并命名列名
y_EasyEnsemble_resampled_t = pd.DataFrame(y_EasyEnsemble_resampled[index_num], columns=['label'])  # 将数据转换为数据框并命名列名
EasyEnsemble_resampled = pd.concat([x_EasyEnsemble_resampled_t, y_EasyEnsemble_resampled_t], axis=1)  # 按列合并数据框
groupby_data_EasyEnsemble = EasyEnsemble_resampled.groupby('label').count()  # 对label做分类汇总
print (groupby_data_EasyEnsemble)  # 打印输出经过EasyEnsemble处理后的数据集样本分类分布

####################################################################
# 3.6 数据化运营要抽样还是全量数据
import random  # 导入标准库
import numpy as np  # 导入第三方库

# 简单随机抽样
data = np.loadtxt('data3.txt')  # 导入普通数据文件
data_sample = random.sample(data, 2000)  # 随机抽取2000个样本
print (data_sample[:2])  # 打印输出前2条数据
print (len(data_sample))  # 打印输出抽样样本量

# 等距抽样
data = np.loadtxt('data3.txt')  # 导入普通数据文件
sample_count = 2000  # 指定抽样数量
record_count = data.shape[0]  # 获取最大样本量
width = record_count / sample_count  # 计算抽样间距
data_sample = []  # 初始化空白列表，用来存放抽样结果数据
i = 0  # 自增计数以得到对应索引值
while len(data_sample) <= sample_count and i * width <= record_count - 1:  # 当样本量小于等于指定抽样数量并且矩阵索引在有效范围内时
    data_sample.append(data[i * width])  # 新增样本
    i += 1  # 自增长
print (data_sample[:2])  # 打印输出前2条数据
print (len(data_sample))  # 打印输出样本数量

# 分层抽样
# 导入有标签的数据文件
data2 = np.loadtxt('data2.txt')  # 导入带有分层逻辑的数据
each_sample_count = 200  # 定义每个分层的抽样数量
label_data_unique = np.unique(data2[:, -1])  # 定义分层值域
sample_list = []  # 定义空列表，用于存放临时分层数据
sample_data = []  # 定义空列表，用于存放最终抽样数据
sample_dict = {}  # 定义空字典，用来显示各分层样本数量
for label_data in label_data_unique:  # 遍历每个分层标签
    for data_tmp in data2:  # 读取每条数据
        if data_tmp[-1] == label_data:  # 如果数据最后一列等于标签
            sample_list.append(data_tmp)  # 将数据加入到分层数据中
    each_sample_data = random.sample(sample_list, each_sample_count)  # 对每层数据都随机抽样
    sample_data.extend(each_sample_data)  # 将抽样数据追加到总体样本集
    sample_dict[label_data] = len(each_sample_data)  # 样本集统计结果
print (sample_dict)  # 打印输出样本集统计结果

# 整群抽样
data3 = np.loadtxt('data4.txt')  # 导入已经划分好整群的数据集
label_data_unique = np.unique(data3[:, -1])  # 定义整群标签值域
print (label_data_unique)  # 打印输出所有整群标签
sample_label = random.sample(label_data_unique, 2)  # 随机抽取2个整群
sample_data = []  # 定义空列表，用来存储最终抽样数据
for each_label in sample_label:  # 遍历每个整群标签值域
    for data_tmp in data3:  # 遍历每个样本
        if data_tmp[-1] == each_label:  # 判断样本是否属于抽样整群
            sample_data.append(data_tmp)  # 样本添加到最终抽样数据集
print (sample_label)  # 打印输出样本整群标签
print (len(sample_data))  # 打印输出总抽样数据记录条数

####################################################################
# 3.7 解决运营数据的共线性问题
# 导入相关库
import numpy as np
from sklearn.linear_model import Ridge
from sklearn.decomposition import PCA
from sklearn.linear_model import LinearRegression

# 读取数据
data = np.loadtxt('data5.txt', delimiter='\t')  # 读取数据文件
x = data[:, :-1]  # 切分自变量
y = data[:, -1]  # 切分预测变量

# 使用岭回归算法进行回归分析
model_ridge = Ridge(alpha=1.0)  # 建立岭回归模型对象
model_ridge.fit(x, y)  # 输入x/y训练模型
print (model_ridge.coef_)  # 打印输出自变量的系数
print (model_ridge.intercept_)  # 打印输出截距

# 使用主成分回归进行回归分析
model_pca = PCA()  # 建立PCA模型对象
data_pca = model_pca.fit_transform(x)  # 将x进行主成分分析
ratio_cumsm = np.cumsum(model_pca.explained_variance_ratio_)  # 得到所有主成分方差占比的累积数据
print (ratio_cumsm)  # 打印输出所有主成分方差占比累积
rule_index = np.where(ratio_cumsm > 0.8)  # 获取方差占比超过0.8的所有索引值
min_index = rule_index[0][0]  # 获取最小索引值
data_pca_result = data_pca[:, :min_index + 1]  # 根据最小索引值提取主成分
model_liner = LinearRegression()  # 建立回归模型对象
model_liner.fit(data_pca_result, y)  # 输入主成分数据和预测变量y并训练模型
print (model_liner.coef_)  # 打印输出自变量的系数
print (model_liner.intercept_)  # 打印输出截距

####################################################################
# 3.8 有关相关性分析的混沌
import numpy as np  # 导入库

data = np.loadtxt('data5.txt', delimiter='\t')  # 读取数据文件
x = data[:, :-1]  # 切分自变量
correlation_matrix = np.corrcoef(x, rowvar=0)  # 相关性分析
print (correlation_matrix.round(2))  # 打印输出相关性结果

####################################################################
# 3.9 标准化，让运营数据落入相同的区间
import numpy as np
from sklearn import preprocessing
import matplotlib.pyplot as plt

data = np.loadtxt('data6.txt', delimiter='\t')  # 读取数据

# Z-Score标准化
zscore_scaler = preprocessing.StandardScaler()  # 建立StandardScaler对象
data_scale_1 = zscore_scaler.fit_transform(data)  # StandardScaler标准化处理

# Max-Min标准化
minmax_scaler = preprocessing.MinMaxScaler()  # 建立MinMaxScaler模型对象
data_scale_2 = minmax_scaler.fit_transform(data)  # MinMaxScaler标准化处理

# MaxAbsScaler标准化
maxabsscaler_scaler = preprocessing.MaxAbsScaler()  # 建立MaxAbsScaler对象
data_scale_3 = maxabsscaler_scaler.fit_transform(data)  # MaxAbsScaler标准化处理

# RobustScaler标准化
robustscalerr_scaler = preprocessing.RobustScaler()  # 建立RobustScaler标准化对象
data_scale_4 = robustscalerr_scaler.fit_transform(data)  # RobustScaler标准化标准化处理

# 展示多网格结果
data_list = [data, data_scale_1, data_scale_2, data_scale_3, data_scale_4]  # 创建数据集列表
scalar_list = [15, 10, 15, 10, 15, 10]  # 创建点尺寸列表
color_list = ['black', 'green', 'blue', 'yellow', 'red']  # 创建颜色列表
merker_list = ['o', ',', '+', 's', 'p']  # 创建样式列表
title_list = ['source data', 'zscore_scaler', 'minmax_scaler', 'maxabsscaler_scaler', 'robustscalerr_scaler']  # 创建标题列表
for i, data_single in enumerate(data_list):  # 循环得到索引和每个数值
    plt.subplot(2, 3, i + 1)  # 确定子网格
    plt.scatter(data_single[:, :-1], data_single[:, -1], s=scalar_list[i], marker=merker_list[i],
                c=color_list[i])  # 子网格展示散点图
    plt.title(title_list[i])  # 设置子网格标题
plt.suptitle("raw data and standardized data")  # 设置总标题
plt.show()  # 展示图形

####################################################################
# 3.10 离散化，对连续运营数据做逻辑分层
import pandas as pd
from sklearn.cluster import KMeans
from sklearn import preprocessing

# 读取数据
df = pd.read_table('data7.txt', names=['id', 'amount', 'income', 'datetime', 'age'])  # 读取数据文件
print (df.head(5))  # 打印输出前5条数据

# 针对时间数据的离散化
for i, signle_data in enumerate(df['datetime']):  # 循环得到索引和对应值
    single_data_tmp = pd.to_datetime(signle_data)  # 将时间转换为datetime格式
    df['datetime'][i] = single_data_tmp.weekday()  # 离散化为周几
print (df.head(5))  # 打印输出前5条数据

# 针对多值离散数据的离散化
map_df = pd.DataFrame([['0-10', '0-40'], ['10-20', '0-40'], ['20-30', '0-40'], ['30-40', '0-40'], ['40-50', '40-80'],
                       ['50-60', '40-80'], ['60-70', '40-80'], ['70-80', '40-80'], ['80-90', '>80'], ['>90', '>80']],
                      columns=['age', 'age2'])  # 定义一个要转换的新区间
df_tmp = df.merge(map_df, left_on='age', right_on='age', how='inner')  # 数据框关联匹配
df = df_tmp.drop('age', 1)  # 丢弃名为age的列
print (df.head(5))  # 打印输出前5条数据

# 针对连续数据的离散化
# 方法1：自定义分箱区间实现离散化
bins = [0, 200, 1000, 5000, 10000]  # 自定义区间边界
df['amount1'] = pd.cut(df['amount'], bins)  # 使用边界做离散化
print (df.head(5))  # 打印输出前5条数据
# 方法2 使用聚类法实现离散化
data = df['amount']  # 获取要聚类的数据，名为amount的列
data_reshape = data.reshape((data.shape[0], 1))  # 转换数据形状
model_kmeans = KMeans(n_clusters=4, random_state=0)  # 创建KMeans模型并指定要聚类数量
keames_result = model_kmeans.fit_predict(data_reshape)  # 建模聚类
df['amount2'] = keames_result  # 新离散化的数据合并到原数据框
print (df.head(5))  # 打印输出前5条数据
# 方法3：使用4分位数实现离散化
df['amount3'] = pd.qcut(df['amount'], 4, labels=['bad', 'medium', 'good', 'awesome'])  # 按四分位数进行分隔
df = df.drop('amount', 1)  # 丢弃名为amount的列
print (df.head(5))  # 打印输出前5条数据

# 针对连续数据的二值化
binarizer_scaler = preprocessing.Binarizer(threshold=df['income'].mean())  # 建立Binarizer模型对象
income_tmp = binarizer_scaler.fit_transform(df['income'])  # Binarizer标准化转换
income_tmp.resize(df['income'].shape)  # 转换数据形状
df['income'] = income_tmp  # Binarizer标准化转换
print (df.head(5))  # 打印输出前5条数据

####################################################################
# 3.12.1 网页数据解析
# 导入库
import requests  # 用于请求
from bs4 import BeautifulSoup  # 用于HTML格式化处理
import re  # 用于HTML配合查找条件
import time  # 用于文件名保存


# 获取总页面数量
def get_total_page_number():
    user_agent = 'Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36'
    headers = {'User-Agent': user_agent}  # 定义头信息
    url = 'https://www.amazon.cn/s/ref=sa_menu_digita_l3_siphone?ie=UTF8&page=1&rh=n%3A665002051%2Cp_89%3AApple%2Cn%3A664978051'  # 寻找页码的URL
    res = requests.get(url, headers=headers)  # 发送请求
    html = res.text  # 获得请求中的返回文本信息
    html_soup = BeautifulSoup(html)  # 建立soup对象，用于处理HTML
    page_number_span = html_soup.find('h2', id="s-result-count")  # 查找id="s-result-count"的h2标签
    page_number_code = page_number_span.text  # 读出该标签的文本信息
    number_list = re.findall(r'(\w*[0-9]+)\w*', page_number_code)  # 使用正则表达式解析出文本中的3个数字
    total_page_number = (int(number_list[-1]) / int(number_list[-2])) + 1  # 计算得出总页码
    return int(total_page_number)  # 返回页面数字


# 解析单页面
def parse_single_page(i):
    url_part1 = 'https://www.amazon.cn/s/ref=sa_menu_digita_l3_siphone?ie=UTF8&page=%d' % i  # 定义URL动态前半部分
    url_part2 = '&rh=n%3A665002051%2Cp_89%3AApple%2Cn%3A664978051'  # 定义URL静态后半部分
    url = url_part1 + url_part2  # 拼接成完整URL
    print ('parse url: %s' % url)  # 输出URL信息
    user_agent = 'Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36'
    headers = {'User-Agent': user_agent}  # 定义头信息，用于发送请求
    res = requests.get(url, headers=headers)  # 发送请求
    html = res.text  # 获得请求中的返回文本信息
    html_soup = BeautifulSoup(html)  # 建立soup对象，用于处理HTML
    tag_list = html_soup.find_all('li', id=re.compile('^result.*'))  # 查找id以result开始的li标签，返回列表
    for tag_info in tag_list:  # 读取列表每个标签（一个标签对应一个商品）
        # 解析价格
        # print (tag_info)
        price_code = tag_info.find('span', class_="a-size-base a-color-price s-price a-text-bold")  # 查找价格标签
        if price_code != None:  # 如果非空则继续
            price = price_code.text  # 取出价格标签文字
            # 解析商品标题
            title_code = tag_info.find('h2')  # 查找标题标签
            title = title_code.text  # 取出标题标签文字
            write_data(title, price)  # 每次解析完成写入文件


# 将数据写入文件
def write_data(title, price):
    file_date = time.strftime('%Y-%m-%d', time.localtime(time.time()))  # 当前日期，用于文件命名
    fn = open('%s.txt' % file_date, 'a+')  # 新建文件对象，以追加模式打开
    content = title + '\t' + price + '\n'  # 写内容，标题和价格以tab分割，末尾增加换行符
    fn.write(content)  # 写入文件
    fn.close()  # 关闭文件对象


# 解析多页面并写文件
def main():
    total_page_number = get_total_page_number()  # 获得总页面数
    for i in range(1, int(total_page_number) + 1):  # 循环读出每个页面
        parse_single_page(i)


main()


####################################################################
# 3.12.2 网络用户日志解析
# 去除爬虫功能
def remove_spider_data(single_log):
    # 定义排除爬虫规则集
    exclude_set = [
        'AhrefsBot',
        'archive.org_bot',
        'baiduspider',
        'Baiduspider',
        'bingbot',
        'DeuSu',
        'DotBot',
        'Googlebot',
        'iaskspider',
        'MJ12bot',
        'msnbot',
        'Slurp',
        'Sogou web spider',
        'Sogou Push Spider',
        'SputnikBot',
        'Yahoo! Slurp China',
        'Yahoo! Slurp',
        'YisouSpider',
        'YodaoBot',
        'bot.html'
    ]
    count = 0  # 初始计数用于计算日志中是否包含爬虫
    for spider in exclude_set:  # 循环读取每个爬虫
        if single_log.find(spider) != -1:  # 如果爬虫出现在日志里面
            count += 1  # count + 1
    if count > 0:  # 如果结果不为0，意味着日志中有爬虫
        return 0  # 返回 0
    else:  # 否则
        return 1  # 返回1


# 读取日志数据
def get_raw_log(file):
    fn_read = open(file, 'r')  # 打开要读取的日志文件对象
    content = fn_read.readlines()  # 以列表形式读取日志数据
    fn_read.close()  # 关闭文件对象
    for single_log in content:  # 循环判断每天记录
        rule1 = single_log.find('GET /__ua.gif?') != -1  # 定义日志规则：含ua.gif的请求
        rule2 = remove_spider_data(single_log)
        if rule1 == True and rule2 == True:  # 如果同时符合2条规则，则执行
            fn_write = open('ua_data.txt', 'a+')  # 打开要保存的ua日志文件对象
            fn_write.writelines(single_log)  # 写入符合规则的日志
            fn_write.close()  # 关闭文件对象


# 解析每条日志数据
def split_ua(line):
    import re
    # 定义不同日志分割的正则表达式
    ip_rule = r'[\d.]*'  # 定义IP规则，例如203.208.60.230
    time_rule = r'\[[^\[\]]*\]'  # 定义时间规则，例如[02/Mar/2016:14:00:23 +0800]
    request_rule = r'\"[^\"]*\"'  # 定义请求规则
    status_rule = r'\d+'  # 定义返回的状态码规则，例如200
    bytes_rule = r'\d+'  # 返回的字节数，例如326
    refer_rule = r'\"[^\"]*\"'  # 定义refer规则
    user_agent_rule = r'\"[^\"]*\"'  # 定义user agnet规则
    # 原理：主要通过空格和-来区分各不同项目，各项目内部写各自的匹配表达式
    log_re_pattern = re.compile(r'(%s)\ -\ -\ (%s)\ (%s)\ (%s)\ (%s)\ (%s)\ (%s)' % (
        ip_rule, time_rule, request_rule, status_rule, bytes_rule, refer_rule, user_agent_rule), re.VERBOSE)  # 完整表达式模式
    matchs = log_re_pattern.match(line)  # 匹配
    if matchs != None:  # 如果不为空
        allGroups = matchs.groups()  # 获得所有匹配的列表
        ip_info = allGroups[0]  # IP信息
        time_info = allGroups[1]  # 时间信息
        request_info = allGroups[2]  # 请求信息
        status_info = allGroups[3]  # 状态信息
        bytes_info = allGroups[4]  # 字节数信息
        refer_info = allGroups[5]  # refer信息
        user_agent_info = allGroups[6]  # user agent信息
        return ip_info, time_info, request_info, status_info, bytes_info, refer_info, user_agent_info


# 主程序
def get_final_data():
    file = 'traffic_log_for_dataivy'  # 定义原始日志
    get_raw_log(file)  # 读取非结构化文本数据
    fn_r = open('ua_data.txt', 'r')  # 打开要读取的ua日志文件
    content = fn_r.readlines()  # 读取ua所有日志记录
    fn_r.close()  # 关闭ua文件对象
    fn_w = open('final_data.txt', 'a+')  # 打开要写入的格式化文件
    for line in content:  # 按行循环
        ip_info, time_info, request_info, status_info, bytes_info, refer_info, user_agent_info = split_ua(
            line)  # 获得分割后的数据
        log_line = ip_info + '!' + time_info + '!' + request_info + '!' + status_info + '!' + bytes_info + '!' + refer_info \
                   + '!' + user_agent_info  # 按指定规则组合用于写入文件
        fn_w.writelines(log_line)  # 写入文件
        fn_w.writelines('\n')  # 写入换行符用于换行
    fn_w.close()  # 关闭写入的文件对象


# 执行程序
get_final_data()  # 执行所有程序

####################################################################
# 3.12.3 图像的基本预处理
import cv2  # 导入图像处理库
import numpy as np  # 导入numpy库
from matplotlib import pyplot as plt  # 导入展示库


# 展示图像模块
def img_show(img_name, img):
    cv2.imshow(img_name, img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


# 原始图像
img_file = 'sudoku.png'  # 定义原始数据文件
img = cv2.imread(img_file)  # 以彩色模式读取图像文件
rows, cols, ch = img.shape  # 获取图像形状
img_show('raw img', img)  # 展示彩色图像

# 图像缩放
img_scale = cv2.resize(img, None, fx=0.6, fy=0.6, interpolation=cv2.INTER_CUBIC)  # 图像缩放
img_show('scale img', img_scale)  # 展示缩放后的图像

# 图像平移
M = np.float32([[1, 0, 100], [0, 1, 50]])  # 定义平移中心
img_transform = cv2.warpAffine(img, M, (cols, rows))  # 平移图像
img_show('transform img', img_transform)  # 展示平移后的图像

# 图像旋转
M = cv2.getRotationMatrix2D((cols / 2, rows / 2), 45, 0.6)  # 定义旋转中心
img_rotation = cv2.warpAffine(img, M, (cols, rows))  # 第一个参数为旋转中心，第二个为旋转角度，第三个为旋转后的缩放因子
img_show('rotation img', img_rotation)  # 展示旋转后的图像

# 透视变换
pts1 = np.float32([[76, 89], [490, 74], [37, 515], [520, 522]])  # 定义变换前的四个校准点
pts2 = np.float32([[0, 0], [300, 0], [0, 300], [300, 300]])  # 定义变换后的四个角点
M = cv2.getPerspectiveTransform(pts1, pts2)  # 定义变换中心点
img_perspective = cv2.warpPerspective(img, M, (300, 300))  # 透视变换
img_show('perspective img', img_perspective)  # 展示透视变换后的图像

# 转换为灰度图像
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  # 图像转灰度
img_show('gray img', img_gray)  # 展示灰度图像

# 边缘检测
img_edges = cv2.Canny(img, 100, 200)  # 检测图像边缘
img_show('edges img', img_edges)  # 展示图像边缘

# 图像二值化
ret, th1 = cv2.threshold(img_gray, 127, 255, cv2.THRESH_BINARY)  # 简单阀值
th2 = cv2.adaptiveThreshold(img_gray, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 2)  # 自适应均值阀值
th3 = cv2.adaptiveThreshold(img_gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 2)  # 自适应高斯阀值
titles = ['Gray Image', 'Global Thresholding (v = 127)',
          'Adaptive Mean Thresholding', 'Adaptive Gaussian Thresholding']  # 定义图像标题
images = [img_gray, th1, th2, th3]  # 定义图像集
for i in xrange(4):
    plt.subplot(2, 2, i + 1), plt.imshow(images[i], 'gray')  # 以灰度模式展示每个子网格的图像
    plt.title(titles[i])  # 设置每个子网格标题
    plt.xticks([]), plt.yticks([])  # 设置x轴和y轴标题
plt.show()  # 展示图像

# 图像平滑
kernel = np.ones((5, 5), np.float32) / 25  # 设置平滑内核大小
img_smoth_filter2D = cv2.filter2D(img, -1, kernel)  # 2D卷积法
img_smoth_blur = cv2.blur(img, (5, 5))  # 平均法
img_smoth_gaussianblur = cv2.GaussianBlur(img, (5, 5), 0)  # 高斯模糊
img_smoth_medianblur = cv2.medianBlur(img, 5)  # 中值法
titles = ['filter2D', 'blur', 'GaussianBlur', 'medianBlur']  # 定义标题集
images = [img_smoth_filter2D, img_smoth_blur, img_smoth_gaussianblur, img_smoth_medianblur]  # 定义图像集
for i in xrange(4):
    plt.subplot(2, 2, i + 1), plt.imshow(images[i], 'gray')  # 以灰度模式展示每个子网格的图像
    plt.title(titles[i])  # 设置每个子网格标题
    plt.xticks([]), plt.yticks([])  # 设置x轴和y轴标题
plt.show()  # 展示全部图像

# 形态学处理
img2 = cv2.imread('j.png', 0)  # 以灰度模式读取图像
kernel = np.ones((5, 5), np.uint8)  # 设置形态学处理内核大小
erosion = cv2.erode(img2, kernel, iterations=1)  # 腐蚀
dilation = cv2.dilate(img2, kernel, iterations=1)  # 膨胀
plt.subplot(1, 3, 1), plt.imshow(img2, 'gray')  # 设置子网格1图像
plt.subplot(1, 3, 2), plt.imshow(erosion, 'gray')  # 设置子网格2图像
plt.subplot(1, 3, 3), plt.imshow(dilation, 'gray')  # 设置子网格3图像
plt.show()  # 展示全部图像

####################################################################
# 3.12.4 自然语言文本预处理
# 导入库
import pandas as pd
import jieba  # 结巴分词
from sklearn.feature_extraction.text import TfidfVectorizer  # 基于TF-IDF的词频转向量库


# 分词函数
def jieba_cut(string):
    word_list = []  # 建立空列表用于存储分词结果
    seg_list = jieba.cut(string)  # 精确模式分词
    for word in seg_list:  # 循环读取每个分词
        word_list.append(word)  # 分词追加到列表
    return word_list


# 读取自然语言文件
fn = open('text.txt')
string_lines = fn.readlines()
fn.close()

# 中文分词
seg_list = []  # 建立空列表，用于存储所有分词结果
for string_line in string_lines:  # 读取每行数据
    each_list = jieba_cut(string_line)  # 返回每行的分词结果
    seg_list.append(each_list)  # 分词结果添加到结果列表
for i in range(5):  # 打印输出第一行的前5条数据
    print (seg_list[1][i])

# word to vector
stop_words = [u'\n', u'/', u'“', u'”', u'的', u'，', u'和', u'是', u'随着', u'对于', u'对', u'等', u'能', u'都', u'。', u'、',
              u'中', u'与', u'在', u'其']  # 自定义要去除的无用词
vectorizer = TfidfVectorizer(stop_words=stop_words, tokenizer=jieba_cut)  # 创建词向量模型
X = vectorizer.fit_transform(string_lines)  # 将文本数据转换为向量空间模型
vector = vectorizer.get_feature_names()  # 获得词向量
vector_value = X.toarray()  # 获得词向量值
vector_pd = pd.DataFrame(vector_value, columns=vector)  # 创建用于展示的数据框
print (vector_pd.head(1))  # 打印输出第一条数据
