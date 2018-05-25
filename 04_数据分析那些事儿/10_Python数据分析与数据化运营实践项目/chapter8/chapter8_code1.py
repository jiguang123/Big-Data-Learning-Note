# -*- coding: utf-8 -*-

'''
描述：案例-基于潜在狄利克雷分配（LDA）模型的内容主题挖掘
时间：2017-12-1
程序开发环境：win 64位
Python版本：32位 2.7.12
python IDE：PyCharm
依赖库：sys、tarfile、os、jieba、gensim、bs4
程序输入：article.txt、news_data.tar.gz
程序输出：打印输出18个主题及新文本的预测主题归属
注意：Python的工作目录当前文件夹目录，如果不是请使用如下方法切换：
    点击PyCharm底部调试栏中的Python Console，如果按照本书的正常安装部署会调用iPython交互窗口；在打开的交互环境中输入cd [路径]。
    例如，在windows环境下输入：
    cd D:\4_附件\chapter8

'''

# 导入库
import sys

reload(sys)
sys.setdefaultencoding('utf-8')
import tarfile  # tar压缩包库
import os  # 操作系统功能模块
import jieba.posseg as pseg  # 带词性标注的分词模块
from gensim import corpora, models  # gensim的词频统计和主题建模模块
from bs4 import BeautifulSoup  # 用于XML格式化处理


# 中文分词
def jieba_cut(text):
    '''
    将输入的文本句子根据词性标注做分词
    :param text: 文本句子，字符串型
    :return: 符合规则的分词结果
    '''
    rule_words = ['z', 'vn', 'v', 't', 'nz', 'nr', 'ns', 'n', 'l', 'i', 'j', 'an',
                  'a']  # 只保留状态词、名动词、动词、时间词、其他名词、人名、地名、名词、习用语、简称略语、成语、形容词、名形词
    words = pseg.cut(text)  # 分词
    seg_list = []  # 列表用于存储每个文件的分词结果
    for word in words:  # 循环得到每个分词
        if word.flag in rule_words:
            seg_list.append(word.word)  # 将分词追加到列表
    return seg_list


# 文本预处理
def text_pro(words_list, tfidf_object=None, training=True):
    '''
    gensim主题建模预处理过程，包含分词类别转字典、生成语料库和TF-IDF转换
    :param words_list: 分词列表，列表型
    :param tfidf_object: TF-IDF模型对象，该对象在训练阶段生成
    :param training: 是否训练阶段，用来针对训练和预测两个阶段做预处理
    :return: 如果是训练阶段，返回词典、TF-IDF对象和TF-IDF向量空间数据；如果是预测阶段，返回TF-IDF向量空间数据
    '''
    # 分词列表转字典
    dic = corpora.Dictionary(words_list)  # 将分词列表转换为字典形式
    print ('{:*^60}'.format('token & word mapping review:'))
    for i, w in dic.items()[:5]:  # 循环读出字典前5条的每个key和value，对应的是索引值和分词
        print ('token:%s -- word:%s' % (i, w))
    # 生成语料库
    corpus = []  # 建立一个用于存储语料库的列表
    for words in words_list:  # 读取每个分词列表
        corpus.append(dic.doc2bow(words))  # 将每个分词列表转换为语料库词袋（bag of words）形式的列表
    print ('{:*^60}'.format('bag of words review:'))
    print (corpus[0])  # 打印输出第一条语料库
    # TF-IDF转换
    if training == True:
        tfidf = models.TfidfModel(corpus)  # 建立TF-IDF模型对象
        corpus_tfidf = tfidf[corpus]  # 得到TF-IDF向量稀疏矩阵
        print ('{:*^60}'.format('TF-IDF model review:'))
        for doc in corpus_tfidf:  # 循环读出每个向量
            print doc  # 打印第一条向量
            break  # 跳出循环
        return dic, corpus_tfidf, tfidf
    else:
        return tfidf_object[corpus]


# 全角转半角
def str_convert(content):
    '''
    将内容中的全角字符，包含英文字母、数字键、符号等转换为半角字符
    :param content: 要转换的字符串内容
    :return: 转换后的半角字符串
    '''
    new_str = ''
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
    从原始文件中解析出文本内容数据
    :param data: 包含代码的原始内容
    :return: 文本中的所有内容，列表型
    '''
    raw_code = BeautifulSoup(data, "lxml")  # 建立BeautifulSoup对象
    content_code = raw_code.find_all('content')  # 从包含文本的代码块中找到content标签
    content_list = []  # 建立空列表，用来存储每个content标签的内容
    for each_content in content_code:  # 循环读出每个content标签
        if len(each_content) > 0:  # 如果content标签的内容不为空
            raw_content = each_content.text  # 获取原始内容字符串
            convert_content = str_convert(raw_content)  # 将全角转换为半角
            content_list.append(convert_content)  # 将content文本内容加入列表
    return content_list


# 解压缩文件
if not os.path.exists('./news_data'):  # 如果不存在数据目录，则先解压数据文件
    print ('extract data from news_data.tar.gz...')
    tar = tarfile.open('news_data.tar.gz')  # 打开tar.gz压缩包对象
    names = tar.getnames()  # 获得压缩包内的每个文件对象的名称
    for name in names:  # 循环读出每个文件
        tar.extract(name, path='./')  # 将文件解压到指定目录
    tar.close()  # 关闭压缩包对象

# 汇总所有内容
print ('walk files and get content...')
all_content = []  # 总列表，用于存储所有文件的文本内容
for root, dirs, files in os.walk('./news_data'):  # 分别读取遍历目录下的根目录、子目录和文件列表
    for file in files:  # 读取每个文件
        file_name = os.path.join(root, file)  # 将目录路径与文件名合并为带有完整路径的文件名
        with open(file_name) as f:  # 以只读方式打开文件
            data = f.read()  # 读取文件内容
        all_content.extend(data_parse(data))  # 从文件内容中获取文本并将结果追加到总列表

# 获取每条内容的分词结果
print ('get word list...')
words_list = []  # 分词列表，用于存储所有文件的分词结果
for each_content in all_content:  # 循环读出每个文本内容
    words_list.append(list(jieba_cut(each_content)))  # 将文件内容的分词结果以列表的形式追加到列表

# 建立主题模型
print ('train topic model...')
dic, corpus_tfidf, tfidf = text_pro(words_list, tfidf_object=None, training=True)  # 训练集的文本预处理
num_topics = 3  # 设置主题个数
lda = models.LdaModel(corpus_tfidf, id2word=dic, num_topics=num_topics)  # 通过LDA进行主题建模
print ('{:*^60}'.format('topic model review:'))
for i in range(num_topics):  # 输出每一类主题的结果
    print (lda.print_topic(i))  # 输出对应主题

# 新数据集的主题模型预测
print ('topic forecast...')
with open('article.txt') as f:  # 打开新的文本
    text_new = f.read()  # 读取文本数据
text_content = data_parse(data)  # 解析新的文本
words_list_new = jieba_cut(text_new)  # 将文本转换为分词列表
corpus_tfidf_new = text_pro([words_list_new], tfidf_object=tfidf, training=False)  # 新文本数据集的预处理
corpus_lda_new = lda[corpus_tfidf_new]  # 获取新的分词列表（文档）的主题概率分布
print ('{:*^60}'.format('topic forecast:'))
print (list(corpus_lda_new))
