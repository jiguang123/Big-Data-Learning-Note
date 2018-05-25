# -*- coding: utf-8 -*-

'''
描述：案例-基于多项式贝叶斯的增量学习的文本分类
时间：2017-12-1
程序开发环境：win 64位
Python版本：32位 2.7.12
python IDE：PyCharm
依赖库：sys、re、tarfile、os、numpy、bs4、sklearn
程序输入：article.txt、news_data.tar.gz
程序输出：打印输出18个主题及新文本的预测主题归属
注意：Python的工作目录当前文件夹目录，如果不是请使用如下方法切换：
    点击PyCharm底部调试栏中的Python Console，如果按照本书的正常安装部署会调用iPython交互窗口；在打开的交互环境中输入cd [路径]。
    例如，在windows环境下输入：
    cd D:\4_附件\chapter8

'''

# 导入库
import re
import tarfile  # tar压缩包出库
import os  # 操作系统功能模块
import numpy as np
from bs4 import BeautifulSoup  # 用于XML格式化处理
from sklearn.feature_extraction.text import HashingVectorizer  # 文本转稀疏矩阵
from sklearn.naive_bayes import MultinomialNB  # 贝叶斯分类器
from sklearn.metrics import accuracy_score  # 分类评估指标


# 全角转半角
def str_convert(content):
    '''
    将内容中的全角字符，包含英文字母、数字键、符号等转换为半角字符
    :param content: 要转换的字符串内容
    :return: 转换后的半角字符串
    '''
    new_str = ''  # 新字符串
    for each_char in content:  # 循环读取每个字符
        code_num = ord(each_char)  # 读取字符的ASCII值或Unicode值
        if code_num == 12288:  # 全角空格直接转换
            code_num = 32
        elif (code_num >= 65281 and code_num <= 65374):  # 全角字符（除空格）根据关系转化
            code_num -= 65248
        new_str += unichr(code_num)
    return new_str


# 解析文件内容
def data_parse(data):
    '''
    从原始文件中解析出文本内容和标签数据
    :param data: 包含代码的原始内容
    :return: 以列表形式返回文本中的所有内容和对应标签
    '''
    raw_code = BeautifulSoup(data, "lxml")  # 建立BeautifulSoup对象
    doc_code = raw_code.find_all('doc')  # 从包含文本的代码块中找到doc标签
    content_list = []  # 建立空列表，用来存储每个content标签的内容
    label_list = []  # 建立空列表，用来存储每个content对应的label的内容
    for each_doc in doc_code:  # 循环读出每个doc标签
        if len(each_doc) > 0:  # 如果dco标签的内容不为空
            content_code = each_doc.find('content')  # 从包含文本的代码块中找到doc标签
            raw_content = content_code.text  # 获取原始内容字符串
            convert_content = str_convert(raw_content)  # 将全角转换为半角
            content_list.append(convert_content)  # 将content文本内容加入列表

            label_code = each_doc.find('url')  # 从包含文本的代码块中找到url标签
            label_content = label_code.text  # 获取url信息
            label = re.split('[/|.]', label_content)[2]  # 将URL做分割并提取子域名
            label_list.append(label)  # 将子域名加入列表
    return content_list, label_list


# 交叉检验
def cross_val(model_object, data, label):
    '''
    通过交叉检验计算每次增量学习后的模型得分
    :param model_object: 每次增量学习后的模型对象
    :param data: 训练数据集
    :param label: 训练数据集对应的标签
    :return: 交叉检验得分
    '''
    predict_label = model_object.predict(data)  # 预测测试集标签
    score_tmp = round(accuracy_score(label, predict_label), 4)  # 计算预测准确率
    return score_tmp


# word to vector
def word_to_vector(data):
    '''
    将训练集文本数据转换为稀疏矩阵
    :param data: 输入的文本列表
    :return: 稀疏矩阵
    '''
    model_vector = HashingVectorizer(non_negative=True)  # 建立HashingVectorizer对象
    vector_data = model_vector.fit_transform(data)  # 将输入文本转化为稀疏矩阵
    return vector_data


# label to vecotr
def label_to_vector(label, unique_list):
    '''
    将文本标签转换为向量标签
    :param label: 文本列表
    :unique_list: 唯一值列表
    :return: 向量标签列表
    '''
    for each_index, each_data in enumerate(label):  # 循环读取每个标签的索引及对应值
        label[each_index] = unique_list.index(each_data)  # 将值替换为其索引
    return label


# 解压缩文件
if not os.path.exists('./news_data'):  # 如果不存在数据目录，则先解压数据文件
    print ('extract data from news_data.tar.gz...')
    tar = tarfile.open('news_data.tar.gz')  # 打开tar.gz压缩包对象
    names = tar.getnames()  # 获得压缩包内的每个文件对象的名称
    for name in names:  # 循环读出每个文件
        tar.extract(name, path='./')  # 将文件解压到指定目录
    tar.close()  # 关闭压缩包对象

# 定义对象
all_content = []  # 列表，用于存储所有训练集的文本内容
all_label = []  # 列表，用于存储所有训练集的标签
score_list = list()  # 列表，用于存储每次交叉检验得分
pre_list = list()  # 列表，用于存储每次增量计算后的预测标签
unique_list = ['sports', 'house', 'news']  # 标签唯一值列表
print ('unique label:', unique_list)
model_nb = MultinomialNB()  # 建立MultinomialNB模型对象

# 交叉检验和预测数据集预处理
# 交叉检验集
with open('test_sets.txt') as f:
    test_data = f.read()
test_content, test_label = data_parse(test_data)  # 解析文本内容和标签
test_data_vector = word_to_vector(test_content)  # 将文本内容向量化
test_label_vecotr = label_to_vector(test_label, unique_list)  # 将标签内容向量化
# 预测集
with open('article.txt') as f:
    new_data = f.read()
new_content, new_label = data_parse(new_data)  # 解析文本内容和标签
new_data_vector = word_to_vector(new_content)  # 将文本内容向量化

# 增量学习
print ('{:*^60}'.format('incremental learning...'))
for root, dirs, files in os.walk('./news_data'):  # 分别读取遍历目录下的根目录、子目录和文件列表
    for file in files:  # 读取每个文件
        file_name = os.path.join(root, file)  # 将目录路径与文件名合并为带有完整路径的文件名
        print ('training file: %s' % file)
        # 增量训练
        with open(file_name) as f:  # 以只读方式打开文件
            data = f.read()  # 读取文件内容
        content, label = data_parse(data)  # 解析文本内容和标签
        data_vector = word_to_vector(content)  # 将文本内容向量化
        label_vecotr = label_to_vector(label, unique_list)  # 将标签内容向量化
        model_nb.partial_fit(data_vector, label_vecotr, classes=np.array([0, 1, 2]))  # 增量学习
        # 交叉检验
        score_list.append(cross_val(model_nb, test_data_vector, test_label_vecotr))  # 将交叉检验结果存入列表
        # 增量预测
        predict_y = model_nb.predict(new_data_vector)  # 预测内容标签
        pre_list.append(predict_y.tolist())

print ('{:*^60}'.format('cross validation score:'))
print (score_list)  # 打印输出每次交叉检验得分
print ('{:*^60}'.format('predicted labels:'))
print (pre_list)  # 打印输出每次预测标签索引值
print ('{:*^60}'.format('true labels:'))
print (new_label)  # 打印输出正确的标签值
