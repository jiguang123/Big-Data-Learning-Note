# -*- coding: utf-8 -*-

'''
描述：案例-基于自动节点树的数据异常原因下探分析
时间：2017-11-1
程序开发环境：win 64位
Python版本：32位 2.7.12
python IDE：PyCharm
依赖库：sys、numpy、pandas、datetime、graphviz
程序输入：advertising_data.csv
程序输出：打印输出并保存节点树图
注意：Python的工作目录当前文件夹目录，如果不是请使用如下方法切换：
    点击PyCharm底部调试栏中的Python Console，如果按照本书的正常安装部署会调用iPython交互窗口；在打开的交互环境中输入cd [路径]。
    例如，在windows环境下输入：
    cd D:\4_附件\chapter7

'''

# 导入库
import sys

reload(sys)
sys.setdefaultencoding('utf-8')
import datetime
import pandas as pd
import numpy as np
from graphviz import Digraph  # 画图用库

# 读取数据
raw_data = pd.read_csv('advertising_data.csv')

# 数据审查和校验
print ('{:*^60}'.format('Data overview:'))
print (raw_data.head(2))  # 数据概览
print ('{:*^60}'.format('Data dtypes:'))
print (raw_data.dtypes)  # 数据类型

# 数据预处理
raw_data['visit'] = raw_data['visit'].replace('-', 0).astype(np.int64)  # 替换字符为0然后转换为整数型
raw_data['date'] = pd.to_datetime(raw_data['date'], format='%Y/%m/%d')  # 将字符串转换为日期格式
print ('{:*^60}'.format('Data overview:'))
print (raw_data.head(2))
print ('{:*^60}'.format('Data dtypes:'))
print (raw_data.dtypes)

# 计算整体波动量
day_summary = raw_data.ix[:, -1].groupby(raw_data.ix[:, 0]).sum()  # 按天求和汇总
day_change_value = day_summary.diff(1).rename('change')  # 通过差分求平移1天后的变化量
day_change_rate = (day_change_value.shift(-1) / day_summary).round(3).rename('change_rate').shift(1)  # 求相对昨天的环比变化率
day_summary_total = pd.concat((day_summary, day_change_value, day_change_rate), axis=1)  # 整合为完整数据框
print ('{:*^60}'.format('Data change summary:'))
print (day_summary_total)

# 指定日期自动下探分解
the_day = pd.datetime(2017, 6, 7)  # 指定要分析的日期
previous_day = the_day - datetime.timedelta(1)  # 自动获取前1天日期
the_data_tmp = raw_data[raw_data['date'] == the_day].rename(columns={'visit': the_day})  # 获得指定日期数据
previous_data_tmp = raw_data[raw_data['date'] == previous_day].rename(columns={'visit': previous_day})  # 获得前1天日期数据

dimension_list = ['source', 'site', 'channel', 'media']  # 指定要分析的维度：4个层级
split_node_list = ['全站']  # 每层分裂节点名称列表
change_list = list()  # 每层分裂节点对应的总变化量
increase_node_list = []  # 每层最大增长贡献最大的1个维度
decrease_node_list = []  # 每层最小增长贡献最大的1个维度

for dimension in dimension_list:  # 遍历每个维度
    # part1
    the_data_merge = the_data_tmp[[dimension, the_day]]  # 获得指定日期的特定维度和访问量
    previous_data_merge = previous_data_tmp[[dimension, previous_day]]  # 获得指定日期前1天的特定维度和访问量
    the_day_groupby = pd.DataFrame(the_data_merge.ix[:, -1].groupby(the_data_merge.ix[:, 0]).sum())  # 对指定日期特定维度汇总求和
    previous_day_groupby = pd.DataFrame(
        previous_data_merge.ix[:, -1].groupby(previous_data_merge.ix[:, 0]).sum())  # 对指定日期前1天特定维度汇总求和
    # part2
    merge_data = pd.merge(the_day_groupby, previous_day_groupby, how='outer', left_index=True,
                          right_index=True)  # 合并2天的数据
    merge_data = merge_data.fillna(0)  # 将缺失值（没有匹配的值）替换为0
    merge_data['change'] = merge_data[the_day] - merge_data[previous_day]  # 计算环比变化量
    merge_data['change_rate'] = merge_data['change'] / merge_data[previous_day]  # 计算环比变化率
    total_chage = merge_data['change'].sum()  # 获得分裂节点的总变化值
    change_list.append(total_chage)  # 将每个节点的变化值加入列表
    # part3
    merge_data = merge_data.sort_values(by='change')  # 按环比变化量正向排序
    max_increase_node = merge_data.ix[-1].name  # 获得增长变化量最大值节点名称
    max_value, max_rate = merge_data.ix[-1][2:4]  # 获得最大值节点变化量以及变化比例
    increase_node_list.append([max_increase_node, int(max_value), max_rate])  # 将最大值信息追加到列表
    # part4
    min_increase_node = merge_data.ix[0].name  # 获得增长变化量最小值节点名称
    min_value, min_rate = merge_data.ix[0][2:4]  # 获得最小值节点变化量以及变化比例
    decrease_node_list.append([min_increase_node, int(min_value), min_rate])  # 将最小值信息追加到列表
    # part5
    if total_chage >= 0:  # 判断为增长方向
        split_node_list.append(max_increase_node)  # 将分裂节点定义为增长最大值节点
        rules_len = len(split_node_list)  # 通过分裂节点的个数判断所处分裂层级
        if rules_len == 2:  # 第二层source，第一层为全站整体
            the_data_tmp = the_data_tmp[the_data_tmp['source'] == max_increase_node]  # 以source为维度过滤出指定日期符合最大节点条件的数据
            previous_data_tmp = previous_data_tmp[
                previous_data_tmp['source'] == max_increase_node]  # 以source为维度过滤出前1天符合最大节点条件的数据
        elif rules_len == 3:  # 第三层site
            the_data_tmp = the_data_tmp[the_data_tmp['site'] == max_increase_node]  # 以site为维度过滤出指定日期符合最大节点条件的数据
            previous_day_data_tmp = previous_data_tmp[
                previous_data_tmp['site'] == max_increase_node]  # 以site为维度过滤出前1天符合最大节点条件的数据
        elif rules_len == 4:  # 第四层channel
            the_data_tmp = the_data_tmp[the_data_tmp['channel'] == max_increase_node]  # 以channel为维度过滤出指定日期符合最大节点条件的数据
            previous_data_tmp = previous_data_tmp[
                previous_data_tmp['channel'] == max_increase_node]  # 以channel为维度过滤出前1天符合最大节点条件的数据
        elif rules_len == 5:  # 第五层media
            the_data_tmp = the_data_tmp[the_data_tmp['media'] == max_increase_node]  # 以media为维度过滤出指定日期符合最大节点条件的数据
            previous_data_tmp = previous_data_tmp[
                previous_data_tmp['media'] == max_increase_node]  # 以media为维度过滤出前1天符合最大节点条件的数据
    # part6
    else:  # 判断为下降方向
        split_node_list.append(min_increase_node)  # 将分裂节点定义为增长最小值节点
        rules_len = len(split_node_list)  # 通过分裂节点的个数判断所处分裂层级
        if rules_len == 2:  # 第二层source
            the_data_tmp = the_data_tmp[the_data_tmp['source'] == min_increase_node]  # 以source为维度过滤出指定日期符合最小节点条件的数据
            previous_data_tmp = previous_data_tmp[
                previous_data_tmp['source'] == min_increase_node]  # 以source为维度过滤出前1天符合最小节点条件的数据
        elif rules_len == 3:  # 第三层site
            the_data_tmp = the_data_tmp[the_data_tmp['site'] == min_increase_node]  # 以site为维度过滤出指定日期符合最大节点条件的数据
            previous_day_data_tmp = previous_data_tmp[
                previous_data_tmp['site'] == min_increase_node]  # 以site为维度过滤出前1天符合最大节点条件的数据
        elif rules_len == 4:  # 第四层channel
            the_data_tmp = the_data_tmp[the_data_tmp['channel'] == min_increase_node]  # 以channel为维度过滤出指定日期符合最大节点条件的数据
            previous_data_tmp = previous_data_tmp[
                previous_data_tmp['channel'] == min_increase_node]  # 以channel为维度过滤出前1天符合最大节点条件的数据
        elif rules_len == 5:  # 第五层media
            the_data_tmp = the_data_tmp[the_data_tmp['media'] == min_increase_node]  # 以media为维度过滤出指定日期符合最大节点条件的数据
            previous_data_tmp = previous_data_tmp[
                previous_data_tmp['media'] == min_increase_node]  # 以media为维度过滤出前1天符合最大节点条件的数据

# 画图展示自动下探结果
# patr1
node_style = {'fontname': "SimSun", 'shape': 'box'}  # 定义node节点样式
edge_style = {'fontname': "SimHei", 'fontsize': '11'}  # 定义edge节点样式
top_node_style = '<<table><tr><td bgcolor="black"><font color="white">{0}</font></td></tr><tr><td>环比变化量:{1:d}</td></tr><tr><td>环比变化率:{2:.0%}</td></tr></table>>'  # 定义顶部node节点标签样式
left_node_style = '<<table><tr><td bgcolor="chartreuse"><font color="black">{0}</font></td></tr><tr><td>环比变化量:{1}</td></tr><tr><td>环比变化率:{2:.0%}</td></tr></table>>'  # 定义左侧node节点标签样式
right_node_style = '<<table><tr><td bgcolor="lightblue"><font color="black">{0}</font></td></tr><tr><td>环比变化量:{1}</td></tr><tr><td>环比变化率:{2:.0%}</td></tr></table>>'  # 定义右侧node节点标签样式
dot = Digraph(format='png', node_attr=node_style, edge_attr=edge_style)  # 创建有向图

for i in range(4):  # 循环读取每一层
    # part2
    node_name = split_node_list[i]  # 获得分裂节点名称
    node_left, max_value, max_rate = increase_node_list[i]  # 获得增长最大值名称、变化量和变化率
    node_right, min_value, min_rate = decrease_node_list[i]  # 获得增长最小值名称、变化量和变化率
    node_change = change_list[i]  # 获得分裂节点的总变化量-非分裂节点变化量
    node_label_left = left_node_style.format(node_left, max_value, max_rate)  # 左侧节点显示的信息
    node_label_right = right_node_style.format(node_right, min_value, min_rate)  # 右侧节点显示的信息
    # part3
    if i == 0:  # 如果是顶部节点，则单独增加顶部节点信息
        day_data = day_summary_total[day_summary_total.index == the_day]  # 获得顶部节点的数据
        former_data = day_data.ix[0, 1]  # 获得全站总变化量
        node_lable = top_node_style.format(node_name, int(former_data), day_data.ix[0, 2])  # 分别获取顶部节点名称、变化量和变化率
        dot.node(node_name, label=node_lable)  # 增加顶部节点
    # part4
    contribution_rate_1 = float(max_value) / former_data  # 获得左侧变化量贡献率
    contribution_rate_2 = float(min_value) / former_data  # 获得右侧变化量贡献率
    if node_change >= 0:  # 如果为增长，则左侧为正向
        edge_lablel_left = '正向贡献率:{0:.0%}'.format(contribution_rate_1)  # 左侧边的标签信息
        edge_lablel_right = '反向贡献率:{0:.0%}'.format(contribution_rate_2)  # 右侧边的标签信息
        former_data = max_value  # 获得上一层级变化量最大值
    else:  # 如果为下降，则右侧为正向
        edge_lablel_left = '反向贡献率:{0:.0%}'.format(contribution_rate_1)  # 左侧边的标签信息
        edge_lablel_right = '正向贡献率:{0:.0%}'.format(contribution_rate_2)  # 右侧边的标签信息
        former_data = min_value  # 获得上一层级变化量最大值
    # part5
    dot.node(node_left, label=node_label_left)  # 增加左侧节点
    dot.node(node_right, label=node_label_right)  # 增加右侧节点
    dot.edge(node_name, node_left, label=edge_lablel_left, color='chartreuse')  # 增加左侧边
    dot.edge(node_name, node_right, label=edge_lablel_right, color='lightblue')  # 增加右侧边

dot.view('change summary')  # 展示图形结果
