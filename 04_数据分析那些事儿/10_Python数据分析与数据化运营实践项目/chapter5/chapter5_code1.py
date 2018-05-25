# -*- coding: utf-8 -*-

'''
描述：案例-基于RFM的用户价值度模型
时间：2017-9-1
程序开发环境：win 64位
Python版本：32位 2.7.12
python IDE：PyCharm
依赖库：time、numpy、pandas、mysql.connector
程序输入：sales.csv
程序输出：RFM得分数据写本地文件sales_rfm_score.csv和数据表（sales_rfm_score）
注意：Python的工作目录当前文件夹目录，如果不是请使用如下方法切换：
    点击PyCharm底部调试栏中的Python Console，如果按照本书的正常安装部署会调用iPython交互窗口；在打开的交互环境中输入cd [路径]。
    例如，在windows环境下输入：
    cd D:\4_附件\chapter5

'''
# 导入库
import time  # 导入时间库
import numpy as np  # 导入numpy库
import pandas as pd  # 导入pandas库
import mysql.connector  # 导入mysql连接库

# 读取数据
dtypes = {'ORDERDATE': object, 'ORDERID': object, 'AMOUNTINFO': np.float32}  # 设置每列数据类型
raw_data = pd.read_csv('sales.csv', dtype=dtypes, index_col='USERID')  # 读取数据文件

# 数据审查和校验
# 数据概览
print ('Data Overview:')
print (raw_data.head(4))  # 打印原始数据前4条
print ('-' * 30)
print ('Data DESC:')
print (raw_data.describe())  # 打印原始数据基本描述性信息
print ('-' * 60)

# 缺失值审查
na_cols = raw_data.isnull().any(axis=0)  # 查看每一列是否具有缺失值
print ('NA Cols:')
print (na_cols)  # 查看具有缺失值的列
print ('-' * 30)
na_lines = raw_data.isnull().any(axis=1)  # 查看每一行是否具有缺失值
print ('NA Recors:')
print ('Total number of NA lines is: {0}'.format(na_lines.sum()))  # 查看具有缺失值的行总记录数
print (raw_data[na_lines])  # 只查看具有缺失值的行信息
print ('-' * 60)

# 数据异常、格式转换和处理
# 异常值处理
sales_data = raw_data.dropna()  # 丢弃带有缺失值的行记录
sales_data = sales_data[sales_data['AMOUNTINFO'] > 1]  # 丢弃订单金额<=1的记录

# 日期格式转换
sales_data['ORDERDATE'] = pd.to_datetime(sales_data['ORDERDATE'], format='%Y-%m-%d')  # 将字符串转换为日期格式
print ('Raw Dtypes:')
print (sales_data.dtypes)  # 打印输出数据框所有列的数据类型
print ('-' * 60)

# 数据转换
recency_value = sales_data['ORDERDATE'].groupby(sales_data.index).max()  # 计算原始最近一次订单时间
frequency_value = sales_data['ORDERDATE'].groupby(sales_data.index).count()  # 计算原始订单频率
monetary_value = sales_data['AMOUNTINFO'].groupby(sales_data.index).sum()  # 计算原始订单总金额

# 计算RFM得分
# 分别计算R、F、M得分
deadline_date = pd.datetime(2017, 01, 01)  # 指定一个时间节点，用于计算其他时间与该时间的距离
r_interval = (deadline_date - recency_value).dt.days  # 计算R间隔
r_score = pd.cut(r_interval, 5, labels=[5, 4, 3, 2, 1])  # 计算R得分
f_score = pd.cut(frequency_value, 5, labels=[1, 2, 3, 4, 5])  # 计算F得分
m_score = pd.cut(monetary_value, 5, labels=[1, 2, 3, 4, 5])  # 计算M得分

# R、F、M数据合并
rfm_list = [r_score, f_score, m_score]  # 将r、f、m三个维度组成列表
rfm_cols = ['r_score', 'f_score', 'm_score']  # 设置r、f、m三个维度列名
rfm_pd = pd.DataFrame(np.array(rfm_list).transpose(), dtype=np.int32, columns=rfm_cols,
                      index=frequency_value.index)  # 建立r、f、m数据框
print ('RFM Score Overview:')
print (rfm_pd.head(4))
print ('-' * 60)

# 计算RFM总得分
# 方法一：加权得分
rfm_pd['rfm_wscore'] = rfm_pd['r_score'] * 0.6 + rfm_pd['f_score'] * 0.3 + rfm_pd['m_score'] * 0.1
# 方法二：RFM组合
rfm_pd_tmp = rfm_pd.copy()
rfm_pd_tmp['r_score'] = rfm_pd_tmp['r_score'].astype('string')
rfm_pd_tmp['f_score'] = rfm_pd_tmp['f_score'].astype('string')
rfm_pd_tmp['m_score'] = rfm_pd_tmp['m_score'].astype('string')
rfm_pd['rfm_comb'] = rfm_pd_tmp['r_score'].str.cat(rfm_pd_tmp['f_score']).str.cat(rfm_pd_tmp['m_score'])

# 打印输出和保存结果
# 打印结果
print ('Final RFM Scores Overview:')
print (rfm_pd.head(4))  # 打印数据前4项结果
print ('-' * 30)
print ('Final RFM Scores DESC:')
print (rfm_pd.describe())

# 保存RFM得分到本地文件
rfm_pd.to_csv('sales_rfm_score.csv')  # 保存数据为csv

# 保存RFM得分到MySQL数据库
# 设置要写库的数据库连接信息
table_name = 'sales_rfm_score'  # 要写库的表名
# 数据库基本信息
config = {'host': '127.0.0.1',  # 默认127.0.0.1
          'user': 'root',  # 用户名
          'password': '123456',  # 密码
          'port': 3306,  # 端口，默认为3306
          'database': 'python_data',  # 数据库名称
          'charset': 'gb2312'  # 字符编码
          }
con = mysql.connector.connect(**config)  # 建立mysql连接
cursor = con.cursor()  # 获得游标
# 查找数据库是否存在目标表，如果没有则新建
cursor.execute("show tables")  #
table_object = cursor.fetchall()  # 通过fetchall方法获得所有数据
table_list = []  # 创建库列表
for t in table_object:  # 循环读出所有库
    table_list.append(t[0])  # 每个每个库追加到列表
if not table_name in table_list:  # 如果目标表没有创建
    cursor.execute('''
    CREATE TABLE %s (
    userid               VARCHAR(20),
    r_score               int(2),
    f_score              int(2),
    m_score              int(2),
    rfm_wscore              DECIMAL(10,2),
    rfm_comb              VARCHAR(10),
    insert_date              VARCHAR(20)
    )ENGINE=InnoDB DEFAULT CHARSET=gb2312
    ''' % table_name)  # 创建新表
# 将数据写入数据库
user_id = rfm_pd.index  # 索引列
rfm_wscore = rfm_pd['rfm_wscore']  # RFM加权得分列
rfm_comb = rfm_pd['rfm_comb']  # RFM组合得分列
timestamp = time.strftime('%Y-%m-%d', time.localtime(time.time()))  # 写库日期
print ('Begin to insert data into table {0}...'.format(table_name))  # 输出开始写库的提示信息
for i in range(rfm_pd.shape[0]):  # 设置循环次数并依次循环
    insert_sql = "INSERT INTO `%s` VALUES ('%s',%s,%s,%s,%s,'%s','%s')" % \
                 (table_name, user_id[i], r_score.iloc[i], f_score.iloc[i], m_score.iloc[i], rfm_wscore.iloc[i],
                  rfm_comb.iloc[i], timestamp)  # 写库SQL依据
    cursor.execute(insert_sql)  # 执行SQL语句，execute函数里面要用双引号
    con.commit()  # 提交命令
cursor.close()  # 关闭游标
con.close()  # 关闭数据库连接
print ('Finish inserting, total records is: %d' % (i + 1))  # 打印写库结果
