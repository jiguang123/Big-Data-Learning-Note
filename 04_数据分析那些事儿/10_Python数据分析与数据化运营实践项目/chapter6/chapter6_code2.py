# -*- coding: utf-8 -*-

'''
描述：案例-基于LogisticRegression、RandomForest、Bagging概率投票组合模型的异常检测
时间：2017-10-1
程序开发环境：win 64位
Python版本：32位 2.7.12
python IDE：PyCharm
依赖库：sys、numpy、pandas、sklearn、imblearn
程序输入：new_abnormal_orders.csv、abnormal_orders.txt
程序输出：打印输出预测标签值
注意：Python的工作目录当前文件夹目录，如果不是请使用如下方法切换：
    点击PyCharm底部调试栏中的Python Console，如果按照本书的正常安装部署会调用iPython交互窗口；在打开的交互环境中输入cd [路径]。
    例如，在windows环境下输入：
    cd D:\4_附件\chapter6

'''

# 导入库
import sys

reload(sys)
sys.setdefaultencoding('utf-8')

import numpy as np  # numpy库
import pandas as pd  # pandas库
from sklearn.feature_extraction import DictVectorizer  # 数值分类转整数分类库
from imblearn.over_sampling import SMOTE  # 过抽样处理库SMOTE
from sklearn.model_selection import StratifiedKFold, cross_val_score  # 导入交叉检验算法
from sklearn.linear_model import LogisticRegression  # 导入逻辑回归库
from sklearn.ensemble import VotingClassifier, RandomForestClassifier, BaggingClassifier  # 三种集成分类库和投票方法库


# 数据审查和预处理函数
# 基本状态查看
def set_summary(df):
    '''
    查看数据集后2条数据、数据类型、描述性统计
    :param df: 数据框
    :return: 无
    '''
    print ('{:*^60}'.format('Data overview:'))
    print (df.tail(2))  # 打印原始数据后2条
    print ('{:*^60}'.format('Data dtypes:'))
    print (df.dtypes)  # 打印数据类型
    print ('{:*^60}'.format('Data DESC:'))
    print (df.describe().round(2).T)  # 打印原始数据基本描述性信息


# 缺失值审查
def na_summary(df):
    '''
    查看数据集的缺失数据列、行记录数
    :param df: 数据框
    :return: 无
    '''
    na_cols = df.isnull().any(axis=0)  # 查看每一列是否具有缺失值
    print ('{:*^60}'.format('NA Cols:'))
    print (na_cols)  # 查看具有缺失值的列
    na_lines = df.isnull().any(axis=1)  # 查看每一行是否具有缺失值
    print ('Total number of NA lines is: {0}'.format(na_lines.sum()))  # 查看具有缺失值的行总记录数


# 类样本均衡审查
def label_samples_summary(df):
    '''
    查看每个类的样本量分布
    :param df: 数据框
    :return: 无
    '''
    print ('{:*^60}'.format('Labesl samples count:'))
    print (df.ix[:, 1].groupby(df.ix[:, -1]).count())


# 字符串分类转整数分类
def str2int(set, convert_object, unique_object, training=True):
    '''
    用于将分类变量中的字符串转换为数值索引分类
    :param set: 数据集
    :param convert_object:  DictVectorizer转换对象，当training为True时为空；当training为False时则使用从训练阶段得到的对象
    :param unique_object: 唯一值列表，当training为True时为空；当training为False时则使用从训练阶段得到的唯一值列表
    :param training: 是否为训练阶段
    :return: 训练阶段返回model_dvtransform,unique_list,traing_part_data；预测应用阶段返回predict_part_data
    '''
    convert_cols = ['cat', 'attribution', 'pro_id', 'pro_brand', 'order_source', 'pay_type', 'use_id',
                    'city']  # 定义要转换的列
    final_convert_matrix = set[convert_cols]  # 获得要转换的数据集合
    lines = set.shape[0]  # 获得总记录数
    dict_list = []  # 总空列表，用于存放字符串与对应索引组成的字典
    if training == True:  # 如果是训练阶段
        unique_list = []  # 总唯一值列表，用于存储每个列的唯一值列表
        for col_name in convert_cols:  # 循环读取每个列名
            cols_unqiue_value = set[col_name].unique().tolist()  # 获取列的唯一值列表
            unique_list.append(cols_unqiue_value)  # 将唯一值列表追加到总列表
        for line_index in range(lines):  # 读取每行索引
            each_record = final_convert_matrix.iloc[line_index]  # 获得每行数据，是一个Series
            for each_index, each_data in enumerate(each_record):  # 读取Series每行对应的索引值
                list_value = unique_list[each_index]  # 读取该行索引对应到总唯一值列表列索引下的数据(其实是相当于原来的列做了转置成了行，目的是查找唯一值在列表中的位置)
                each_record[each_index] = list_value.index(each_data)  # 获得每个值对应到总唯一值列表中的索引
            each_dict = dict(zip(convert_cols, each_record))  # 将每个值和对应的索引组合字典
            dict_list.append(each_dict)  # 将字典追加到总列表
        model_dvtransform = DictVectorizer(sparse=False, dtype=np.int64)  # 建立转换模型对象
        model_dvtransform.fit(dict_list)  # 应用分类转换训练
        traing_part_data = model_dvtransform.transform(dict_list)  # 转换训练集
        return model_dvtransform, unique_list, traing_part_data
    else:  # 如果是预测阶段
        for line_index in range(lines):  # 读取每行索引
            each_record = final_convert_matrix.iloc[line_index]  # 获得每行数据，是一个Series
            for each_index, each_data in enumerate(each_record):  # 读取Series每行对应的索引值
                list_value = unique_object[each_index]  # 读取该行索引对应到总唯一值列表列索引下的数据(其实是相当于原来的列做了转置成了行，目的是查找唯一值在列表中的位置)
                each_record[each_index] = list_value.index(each_data)  # 获得每个值对应到总唯一值列表中的索引
            each_dict = dict(zip(convert_cols, each_record))  # 将每个值和对应的索引组合字典
            dict_list.append(each_dict)  # 将字典追加到总列表
        predict_part_data = convert_object.transform(dict_list)  # 转换预测集
        return predict_part_data


# 时间属性拓展
def datetime2int(set):
    '''
    将日期和时间数据拓展出其他属性，例如星期几、周几、小时、分钟等。
    :param set: 数据集
    :return: 拓展后的属性矩阵
    '''
    date_set = map(lambda dates: pd.datetime.strptime(dates, '%Y-%m-%d'),
                   set['order_date'])  # 将set中的order_date列转换为特定日期格式
    weekday_data = map(lambda data: data.weekday(), date_set)  # 周几
    daysinmonth_data = map(lambda data: data.day, date_set)  # 当月几号
    month_data = map(lambda data: data.month, date_set)  # 月份

    time_set = map(lambda times: pd.datetime.strptime(times, '%H:%M:%S'),
                   set['order_time'])  # 将set中的order_time列转换为特定时间格式
    second_data = map(lambda data: data.second, time_set)  # 秒
    minute_data = map(lambda data: data.minute, time_set)  # 分钟
    hour_data = map(lambda data: data.hour, time_set)  # 小时

    final_set = []  # 列表，用于将上述拓展属性组合起来
    final_set.extend((weekday_data, daysinmonth_data, month_data, second_data, minute_data, hour_data))  # 将属性列表批量组合
    final_matrix = np.array(final_set).T  # 转换为矩阵并转置
    return final_matrix


# 样本均衡
def sample_balance(X, y):
    '''
    使用SMOTE方法对不均衡样本做过抽样处理
    :param X: 输入特征变量X
    :param y: 目标变量y
    :return: 均衡后的X和y
    '''
    model_smote = SMOTE()  # 建立SMOTE模型对象
    x_smote_resampled, y_smote_resampled = model_smote.fit_sample(X, y)  # 输入数据并作过抽样处理
    return x_smote_resampled, y_smote_resampled


# 数据应用
# 定义特殊字段数据格式
dtypes = {'order_id': np.object,
          'pro_id': np.object,
          'use_id': np.object}
raw_data = pd.read_table('abnormal_orders.txt', delimiter=',', dtype=dtypes)  # 读取数据集

# 数据审查
set_summary(raw_data)  # 基本状态查看
na_summary(raw_data)  # 缺失值审查
label_samples_summary(raw_data)  # 类样本分布审查

# 数据预处理
drop_na_set = raw_data.dropna()  # 丢弃带有NA值的数据行
X_raw = drop_na_set.ix[:, 1:-1]  # 分割输入变量X，并丢弃订单ID列和最后一列目标变量
y_raw = drop_na_set.ix[:, -1]  # 分割目标变量y
model_dvtransform, unique_object, str2int_data = str2int(X_raw, None, None, training=True)  # 字符串分类转整数型分类
datetime2int_data = datetime2int(X_raw)  # 拓展日期时间属性
combine_set = np.hstack((str2int_data, datetime2int_data))  # 合并转换后的分类和拓展后的日期数据集
constant_set = X_raw[['total_money', 'total_quantity']]  # 原始连续数据变量
X_combine = np.hstack((combine_set, constant_set))  # 再次合并数据集
X, y = sample_balance(X_combine, y_raw)  # 样本均衡处理

# 组合分类模型交叉检验
model_rf = RandomForestClassifier(n_estimators=20, random_state=0)  # 随机森林分类模型对象
model_lr = LogisticRegression(random_state=0)  # 逻辑回归分类模型对象
model_BagC = BaggingClassifier(n_estimators=20, random_state=0)  # Bagging分类模型对象
estimators = [('randomforest', model_rf), ('Logistic', model_lr), ('bagging', model_BagC)]  # 建立组合评估器列表
model_vot = VotingClassifier(estimators=estimators, voting='soft', weights=[0.9, 1.2, 1.1], n_jobs=-1)  # 建立组合评估模型
cv = StratifiedKFold(8)  # 设置交叉检验方法
cv_score = cross_val_score(model_vot, X, y, cv=cv)  # 交叉检验
print ('{:*^60}'.format('Cross val socres:'))
print (cv_score)  # 打印每次交叉检验得分
print ('Mean scores is: %.2f' % cv_score.mean())  # 打印平均交叉检验得分
model_vot.fit(X, y)  # 模型训练

# 新数据集做预测
X_raw_data = pd.read_csv('new_abnormal_orders.csv', dtype=dtypes)  # 读取要预测的数据集
X_raw_new = X_raw_data.ix[:, 1:]  # 分割输入变量X，并丢弃订单ID列
str2int_data_new = str2int(X_raw_new, model_dvtransform, unique_object, training=False)  # 字符串分类转整数型分类
datetime2int_data_new = datetime2int(X_raw_new)  # 日期时间转换
combine_set_new = np.hstack((str2int_data_new, datetime2int_data_new))  # 合并转换后的分类和拓展后的日期数据集
constant_set_new = X_raw_new[['total_money', 'total_quantity']]  # 原始连续数据变量
X_combine_new = np.hstack((combine_set_new, constant_set_new))  # 再次合并数据集
y_predict = model_vot.predict(X_combine_new)  # 预测结果
print ('{:*^60}'.format('Predicted Labesls:'))
print (y_predict)  # 打印预测值
