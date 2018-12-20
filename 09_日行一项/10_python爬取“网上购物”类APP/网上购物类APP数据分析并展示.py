# =========== Python3.X Jupyter ===========

# 导入第三方包
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# 读取外部数据源
app_info = pd.read_csv('apps.csv')

# 数据集的观测数量及变量数
app_info.shape

# 窥探数据前5行信息
app_info.head()

# 查看数据集各变量的类型
app_info.dtypes

# 检查数据是否有重复（一般对于爬虫数据都需要检查）
any(app_info.duplicated())

# 数值变量的描述性分析
app_info.describe()



# 剔除重复观测
app_info.drop_duplicates(inplace=True)
app_info.shape

# 删除评论人数为-1的观测（因为只有2条记录）
app_info = app_info.loc[app_info.comments != -1,]

# 离散变量的统计描述
app_info.describe(include = ['object'])



# 自定义函数，处理安装人数的单位
def func(x):
    if x.find('亿') != -1:
        y = float(x[:-1])*10000
    elif x.find('万') != -1:
        y = float(x[:-1])
    else:
        y = float(x)/10000
    return(y) 
# 安装人数变量的类型转换
app_info['install_new'] = app_info.install.apply(func)

# 自定义匿名函数
y = lambda x : float(x[:-2]) if x.find('MB') != -1 else float(x[:-2])/1024
# 软件大小变量的类型转换 
app_info['size_new'] = app_info['size'].apply(y)

# 自定义匿名函数，将“暂无”设置为缺失值
y = lambda x : np.nan if x == '暂无' else float(x[:-1])/100
app_info['love_new'] = app_info['love'].apply(y)

# 用中位数对好评率进行填补
app_info['love_new'] = app_info.love_new.fillna(app_info.love_new.median())

# 日期类型的转换
app_info['update_new'] = pd.to_datetime(app_info['update'], format = '%Y年%m月%d日')



# 数值变量的描述性统计
app_info.describe()

# 删除不必要的变量
app_info.drop(['install','size','love','update'], axis = 1, inplace=True)
app_info.head()



# 各类应用安装量最多的前5个APP（产生绘图数据）
ls = []

categories = ['商城','团购','优惠','快递','全球导购']
for cate in categories:
    sub = app_info.loc[app_info.appcategory.apply(lambda x : x.find(cate) != -1),['appname','install_new']]
    
    # 取前5的安装量
    sub = sub.sort_values(by = ['install_new'],ascending=False)[:5]
    sub['type'] = cate
    ls.append(sub)
# 合并数据集    
app_install_cat = pd.concat(ls)    
    

# 设置绘图风格
plt.style.use('ggplot')
# 中文处理
plt.rcParams['font.sans-serif'] = 'Microsoft YaHei'

# 为了让多张子图在一张图中完成，设置子图的位置
ax1 = plt.subplot2grid((3,2),(0,0))
ax2 = plt.subplot2grid((3,2),(0,1))
ax3 = plt.subplot2grid((3,2),(1,0))
ax4 = plt.subplot2grid((3,2),(1,1))
ax5 = plt.subplot2grid((3,2),(2,0), colspan=2) # colspan指定跨过的列数

# 将图框存放起来，用于循环使用
axes = [ax1,ax2,ax3,ax4,ax5]
types = app_install_cat.type.unique()

# 循环的方式完成5张图的绘制
for i in range(5):
    # 准备绘图数据
    data = app_install_cat.loc[app_install_cat.type == types[i]]
    # 绘制条形图
    axes[i].bar(range(5), data.install_new, color = 'steelblue', alpha = 0.7)
    # 设置图框大小
    gcf = plt.gcf()
    gcf.set_size_inches(8, 6)
    # 添加标题
    axes[i].set_title(types[i]+'类APP下载量前5的应用', size = 9)
    # 设置刻度位置
    axes[i].set_xticks(np.arange(5) + 0.4)
    # 为刻度添加标签值
    axes[i].set_xticklabels(data.appname, fontdict={'fontsize':7},  color = 'red')
    # 删除各子图上、右和下的边界刻度标记
    axes[i].tick_params(top = 'off', bottom = 'off', right = 'off')
   
# 调整子图之间的水平间距和高度间距
plt.subplots_adjust(hspace=0.6, wspace=0.3)

# 显示图形
plt.show()



# 各类应用好评率最低的前5个APP（产生绘图数据）
ls = []
categories = ['商城','团购','优惠','快递','全球导购']
for cate in categories:
    sub = app_info.loc[app_info.appcategory.apply(lambda x : x.find(cate) != -1),['appname','love_new']]
    # 取前5的安装量
    sub = sub.sort_values(by = ['love_new'])[:5]
    sub['type'] = cate
    ls.append(sub)
app_love_cat = pd.concat(ls)  

# 为了让多张子图在一张图中完成，设置子图的位置
ax1 = plt.subplot2grid((3,2),(0,0))
ax2 = plt.subplot2grid((3,2),(0,1))
ax3 = plt.subplot2grid((3,2),(1,0))
ax4 = plt.subplot2grid((3,2),(1,1))
ax5 = plt.subplot2grid((3,2),(2,0), colspan=2) # colspan指定跨过的列数

# 将图框存放起来，用于循环使用
axes = [ax1,ax2,ax3,ax4,ax5]
types = app_love_cat.type.unique()

# 循环的方式完成5张图的绘制
for i in range(5):
    # 准备绘图数据
    data = app_love_cat.loc[app_love_cat.type == types[i]]
    # 绘制条形图
    axes[i].bar(range(5), data.love_new, color = 'steelblue', alpha = 0.7)
    # 设置图框大小
    gcf = plt.gcf()
    gcf.set_size_inches(8, 6)
    # 添加标题
    axes[i].set_title(types[i]+'类APP好评率后5的应用', size = 9)
    # 设置x轴刻度位置
    axes[i].set_xticks(np.arange(5) + 0.4)
    # 为x轴刻度添加标签值
    axes[i].set_xticklabels(data.appname, fontdict={'fontsize':7},  color = 'red')
    # 设置y轴刻度位置
    axes[i].set_yticks(np.arange(0,0.6,0.15))
    # 为y轴刻度添加标签值
    axes[i].set_yticklabels([str(i*100) + '%' for i in np.arange(0,0.6,0.15)])
    # 删除各子图上、右和下的边界刻度标记
    axes[i].tick_params(top = 'off', bottom = 'off', right = 'off')
   

# 调整子图之间的水平间距和高度间距
plt.subplots_adjust(hspace=0.6, wspace=0.3)
# 显示图形
plt.show()



# 导入第三方模块
from sklearn.linear_model import LinearRegression

# 评价人数与好评率是否存在关系呢？
# 散点图
plt.scatter(app_info.comments, # 评价人数
            app_info.love_new, # 好评率
            s = 30, # 设置点的大小 
            c = 'black', # 设置点的颜色
            marker = 'o', # 设置点的形状
            alpha = 0.9, # 设置点的透明度
            linewidths = 0.3, # 设置散点边界的粗细
            label = '观测点'
            )

# 建模
reg = LinearRegression().fit(app_info.comments.reshape(-1,1), app_info.love_new)
# 回归预测值
pred = reg.predict(app_info.comments.reshape(-1,1))

# 绘制回归线
plt.plot(app_info.comments, pred, linewidth = 2, label = '回归线')
plt.legend(loc = 'lower right')

# 添加轴标签和标题
plt.title('评论人数与好评率的关系')
plt.xlabel('评论人数')
plt.ylabel('好评率')

# 去除图边框的顶部刻度和右边刻度
plt.tick_params(top = 'off', right = 'off')
# 显示图形
plt.show()



# 评论人数的描述统计
app_info.comments.describe(percentiles=np.arange(0,1.2,0.2))

#&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;有8成的APP，其评论人数不超过53人，数据太过偏态了。这里先筛选出评论人数不超过55人的app，然后，对其研究“评论人数”与“好评率”的关系。

# 散点图
sub_data = app_info.loc[app_info.comments <= 55,]
# sub_data = app_info.loc[app_info.comments > 55,]
plt.scatter(sub_data.comments, # 评价人数
            sub_data.love_new, # 好评率
            s = 30, # 设置点的大小 
            c = 'black', # 设置点的颜色
            marker = 'o', # 设置点的形状
            alpha = 0.9, # 设置点的透明度
            linewidths = 0.3, # 设置散点边界的粗细
            label = '观测点'
            )

# 建模
reg = LinearRegression().fit(sub_data.comments.reshape(-1,1), sub_data.love_new)
# 回归预测值
pred = reg.predict(sub_data.comments.reshape(-1,1))

# 绘制回归线
plt.plot(sub_data.comments, pred, linewidth = 2, label = '回归线')
plt.legend(loc = 'lower right')

# 添加轴标签和标题
plt.title('评论人数与好评率的关系')
plt.xlabel('评论人数')
plt.ylabel('好评率')

# 显示图形
plt.show()