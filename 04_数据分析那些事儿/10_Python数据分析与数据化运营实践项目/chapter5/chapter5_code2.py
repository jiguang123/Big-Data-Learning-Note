# -*- coding: utf-8 -*-

'''
描述：案例-基于AdaBoost的营销响应预测
时间：2017-9-1
程序开发环境：win 64位
Python版本：32位 2.7.12
python IDE：PyCharm
依赖库：time、numpy、pandas、sklearn
程序输入：order.xlsx
程序输出：预测数据写本地文件order_predict_result.xlsx
注意：Python的工作目录当前文件夹目录，如果不是请使用如下方法切换：
    点击PyCharm底部调试栏中的Python Console，如果按照本书的正常安装部署会调用iPython交互窗口；在打开的交互环境中输入cd [路径]。
    例如，在windows环境下输入：
    cd D:\4_附件\chapter5

'''

# 导入库
import time  # 导入自带时间库

import numpy as np  # numpy库
import pandas as pd  # pandas库
from sklearn.preprocessing import OneHotEncoder  # 导入OneHotEncoder库
from sklearn.model_selection import StratifiedKFold, cross_val_score  # 导入交叉检验算法
from sklearn.feature_selection import SelectPercentile, f_classif  # 导入特征选择方法库
from sklearn.ensemble import AdaBoostClassifier  # 导入集成算法
from sklearn.pipeline import Pipeline  # 导入Pipeline库
from sklearn.metrics import accuracy_score  # 准确率指标


# 基本状态查看
def set_summary(df):
    '''
    查看数据集的记录数、维度数、前2条数据、描述性统计和数据类型
    :param df: 数据框
    :return: 无
    '''
    print ('Data Overview')
    print ('Records: {0}\tDimension{1}'.format(df.shape[0], (df.shape[1] - 1)))  # 打印数据集X形状
    print ('-' * 30)
    print (df.head(2))  # 打印前2条数据
    print ('-' * 30)
    print ('Data DESC')
    print (df.describe())  # 打印数据基本描述性信息
    print ('Data Dtypes')
    print (df.dtypes)  # 打印数据类型
    print ('-' * 60)


# 缺失值审查
def na_summary(df):
    '''
    查看数据集的缺失数据列、行记录数
    :param df: 数据框
    :return: 无
    '''
    na_cols = df.isnull().any(axis=0)  # 每一列是否具有缺失值
    print ('NA Cols:')
    print (na_cols)  # 查看具有缺失值的列
    print ('-' * 30)
    print ('valid records for each Cols:')
    print (df.count())  # 查看每一列有效值（非NA）的记录数
    print ('-' * 30)
    na_lines = df.isnull().any(axis=1)  # 查看每一行是否具有缺失值
    print ('Total number of NA lines is: {0}'.format(na_lines.sum()))  # 查看具有缺失值的行总记录数
    print ('-' * 30)


# 类样本均衡审查
def label_summary(df):
    '''
    查看每个类的样本量分布
    :param df: 数据框
    :return: 无
    '''
    print ('Labesl samples count:')
    print (df['value_level'].groupby(df['response']).count())  # 以response为分类汇总维度对value_level列计数统计
    print ('-' * 60)


# 数据预处理
# 变量类型转换
def type_con(df):
    '''
    转换目标列的数据为特定数据类型
    :param df: 数据框
    :return: 类型转换后的数据框
    '''
    var_list = {'edu': 'int32',
                'user_level': 'int32',
                'industry': 'int32',
                'value_level': 'int32',
                'act_level': 'int32',
                'sex': 'int32',
                'region': 'int32'
                }  # 字典：定义要转换的列及其数据类型
    for var, type in var_list.iteritems():  # 循环读出列名和对应的数据类型
        df[var] = df[var].astype(type)  # 数据类型转换
    print ('Data Dtypes')
    print (df.dtypes)  # 打印数据类型
    print ('-' * 30)
    return df


# NA值替换
def na_replace(df):
    '''
    将数据集中的NA值使用自定义方法替换
    :param df: 数据框
    :return: NA值替换后的数据框
    '''
    na_rules = {'age': df['age'].mean(),
                'total_pageviews': df['total_pageviews'].mean(),
                'edu': df['edu'].median(),
                'edu_ages': df['edu_ages'].median(),
                'user_level': df['user_level'].median(),
                'industry': df['user_level'].median(),
                'act_level': df['act_level'].median(),
                'sex': df['sex'].median(),
                'red_money': df['red_money'].mean(),
                'region': df['region'].median()
                }  # 字典：定义各个列数据转换方法
    df = df.fillna(na_rules)  # 使用指定方法填充缺失值
    print ('Check NA exists:')
    print (df.isnull().any().sum())  # 查找是否还有缺失值
    print ('-' * 30)
    return df


# 标志转换
def symbol_con(df, enc_object=None, train=True):
    '''
    将分类和顺序变量转换为二值化的标志变量
    :param df: 数据框
    :param enc_object: sklearn的标志转换对象，训练阶段设置默认值为None；预测阶段使用从训练阶段获得的转换对象
    :param train: 是否为训练阶段的判断状态，训练阶段为True，预测阶段为False
    :return: 标志转换后的数据框、标志转换对象（如果是训练阶段）
    '''
    convert_cols = ['edu', 'user_level', 'industry', 'value_level', 'act_level', 'sex', 'region']  # 选择要做标志转换的列名
    df_con = df[convert_cols]  # 选择要做标志转换的数据
    df_org = df[['age', 'total_pageviews', 'edu_ages', 'blue_money', 'red_money', 'work_hours']].values  # 设置不作标志转换的列
    if train == True:  # 如果处于训练阶段
        enc = OneHotEncoder()  # 建立标志转换模型对象
        enc.fit(df_con)  # 训练模型
        df_con_new = enc.transform(df_con).toarray()  # 转换数据并输出为数组格式
        new_matrix = np.hstack((df_con_new, df_org))  # 将未转换的数据与转换后的数据合并
        return new_matrix, enc
    else:
        df_con_new = enc_object.transform(df_con).toarray()  # 使用训练阶段获得的转换对象转换数据并输出为数组格式
        new_matrix = np.hstack((df_con_new, df_org))  # 将未转换的数据与转换后的数据合并
        return new_matrix


# 获得最佳模型参数
def get_best_model(X, y):
    '''
    结合交叉检验得到不同参数下的分类模型结果
    :param X: 输入X（特征变量）
    :param y: 预测y（目标变量）
    :return: 特征选择模型对象
    '''
    transform = SelectPercentile(f_classif, percentile=50)  # 使用f_classif方法选择特征最明显的50%数量的特征
    model_adaboost = AdaBoostClassifier()  # 建立AdaBoostClassifier模型对象
    model_pipe = Pipeline(steps=[('ANOVA', transform), ('model_adaboost', model_adaboost)])  # 建立由特征选择和分类模型构成的“管道”对象
    cv = StratifiedKFold(5)  # 设置交叉检验次数
    n_estimators = [20, 50, 80, 100]  # 设置模型参数列表
    score_methods = ['accuracy', 'f1', 'precision', 'recall', 'roc_auc']  # 设置交叉检验指标
    mean_list = list()  # 建立空列表用于存放不同参数方法、交叉检验评估指标的均值列表
    std_list = list()  # 建立空列表用于存放不同参数方法、交叉检验评估指标的标准差列表
    for parameter in n_estimators:  # 循环读出每个参数值
        t1 = time.time()  # 记录训练开始的时间
        score_list = list()  # 建立空列表用于存放不同交叉检验下各个评估指标的详细数据
        print ('set parameters: %s' % parameter)  # 打印当前模型使用的参数
        for score_method in score_methods:  # 循环读出每个交叉检验指标
            model_pipe.set_params(model_adaboost__n_estimators=parameter)  # 通过“管道”设置分类模型参数
            score_tmp = cross_val_score(model_pipe, X, y, scoring=score_method, cv=cv)  # 使用交叉检验计算指定指标的得分
            score_list.append(score_tmp)  # 将交叉检验得分存储到列表
        score_matrix = pd.DataFrame(np.array(score_list), index=score_methods)  # 将交叉检验详细数据转换为矩阵
        score_mean = score_matrix.mean(axis=1).rename('mean')  # 计算每个评估指标的均值
        score_std = score_matrix.std(axis=1).rename('std')  # 计算每个评估指标的标准差
        score_pd = pd.concat([score_matrix, score_mean, score_std], axis=1)  # 将原始详细数据和均值、标准差合并
        mean_list.append(score_mean)  # 将每个参数得到的各指标均值追加到列表
        std_list.append(score_std)  # 将每个参数得到的各指标标准差追加到列表
        print (score_pd.round(2))  # 打印每个参数得到的交叉检验指标数据，只保留2位小数
        print ('-' * 60)
        t2 = time.time()  # 计算每个参数下算法用时
        tt = t2 - t1  # 计算时间间隔
        print ('time: %s' % str(tt))  # 打印时间间隔
    mean_matrix = np.array(mean_list).T  # 建立所有参数得到的交叉检验的均值矩阵
    std_matrix = np.array(std_list).T  # 建立所有参数得到的交叉检验的标准差矩阵
    mean_pd = pd.DataFrame(mean_matrix, index=score_methods, columns=n_estimators)  # 将均值矩阵转换为数据框
    std_pd = pd.DataFrame(std_matrix, index=score_methods, columns=n_estimators)  # 将均值标准差转换为数据框
    print ('Mean values for each parameter:')
    print (mean_pd)  # 打印输出均值矩阵
    print ('Std values for each parameter:')
    print (std_pd)  # 打印输出标准差矩阵
    print ('-' * 60)
    return transform


# 数据应用
# 加载数据集
raw_data = pd.read_excel('order.xlsx', sheetname=0)  # 读出Excel的第一个sheet
X = raw_data.drop('response', axis=1)  # 分割X
y = raw_data['response']  # 分割y

# 数据审查和预处理
set_summary(raw_data)  # 基本状态查看
na_summary(raw_data)  # 缺失值审查
label_summary(raw_data)  # 类样本均衡均衡审查
X_t1 = na_replace(X)  # 替换缺失值
X_t2 = type_con(X_t1)  # 数据类型转换
X_new, enc = symbol_con(X_t2, enc_object=None, train=True)  # 将分类和顺序数据转换为标志

# 分类模型训练
transform = get_best_model(X_new, y)  # 获得最佳分类模型参数信息
transform.fit(X_new, y)  # 应用特征选择对象选择要参与建模的特征变量
X_final = transform.transform(X_new)  # 获得具有显著性特征的特征变量
final_model = AdaBoostClassifier(n_estimators=100)  # 从打印的参数均值和标准差信息中确定参数并建立分类模型对象
final_model.fit(X_final, y)  # 训练模型

# 新数据集做预测
new_data = pd.read_excel('order.xlsx', sheetname=1)  # 读取要预测的数据集
final_reponse = new_data['final_response']  # 获取最终的目标变量值
new_data = new_data.drop('final_response', axis=1)  # 获得预测的输入变量X
set_summary(new_data)  # 基本状态查看
na_summary(new_data)  # 缺失值审查
new_X_t1 = na_replace(new_data)  # 替换缺失值
new_X_t2 = type_con(new_X_t1)  # 数据类型转换
new_X_t3 = symbol_con(new_X_t2, enc_object=enc, train=False)  # 将分类和顺序数据转换为标志
new_X_final = transform.transform(new_X_t3)  # 对数据集做特征选择

# 输出预测值以及预测概率
predict_labels = pd.DataFrame(final_model.predict(new_X_final), columns=['labels'])  # 获得预测标签
predict_labels_pro = pd.DataFrame(final_model.predict_proba(new_X_final), columns=['pro1', 'pro2'])  # 获得预测概率
predict_pd = pd.concat((new_data, predict_labels, predict_labels_pro), axis=1)  # 将预测标签、预测数据和原始数据X合并
print ('Predict info')
print (predict_pd.head(2))  # 打印前2条结果
print ('-' * 60)

# 将预测结果写入Excel
writer = pd.ExcelWriter('order_predict_result.xlsx')  # 创建写入文件对象
predict_pd.to_excel(writer, 'Sheet1')  # 将数据写入sheet1
writer.save()  # 保存文件

# 后续--与实际效果的比较
print ('final accuracy: {0}'.format(accuracy_score(final_reponse, predict_labels)))
