# -*- coding: utf-8 -*-

'''
描述：第一个使用Python完成的数据化运营案例——销售预测
时间：2018-1-31
程序开发环境：win 64位
Python版本：64位 3.6.3
python IDE：PyCharm 2017.3专业版
依赖库：re、numpy、sklearn、matplotlib
程序输入：data.txt
程序输出：预测的销售量
注意：Python的工作目录当前文件夹目录，如果不是请使用如下方法切换：
    点击PyCharm底部调试栏中的Python Console，如果按照本书的正常安装部署会调用iPython交互窗口；在打开的交互环境中输入cd [路径]。
    例如，在windows环境下输入：
    cd D:\4_附件\chapter1
'''

# 导入库
import re
import numpy
from sklearn import linear_model
from matplotlib import pyplot as plt

# 导入数据
fn = open('data.txt', 'r')
all_data = fn.readlines()
fn.close()

# 数据预处理
x = []
y = []
for single_data in all_data:
    tmp_data = re.split('\t|\n', single_data)
    x.append(float(tmp_data[0]))
    y.append(float(tmp_data[1]))

x = numpy.array(x).reshape([-1, 1])
y = numpy.array(y).reshape([-1, 1])

# 数据分析展示
plt.scatter(x, y)
plt.show()

# 数据建模
model = linear_model.LinearRegression()
model.fit(x, y)

# 模型评估
model_coef = model.coef_
model_intercept = model.intercept_
r2 = model.score(x, y)

# 销售预测
new_x = 84610
pre_y = model.predict(new_x)
print (pre_y)
