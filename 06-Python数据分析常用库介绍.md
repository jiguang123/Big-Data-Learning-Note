## 数据分析常用python库的使用

	1、Numpy



	2、Pandas
	
		df：任意的Pandas DataFrame对象
		同时我们需要做如下的引入：
		import pandas as pd

		2.1导入数据
			pd.read_csv(filename)：从CSV文件导入数据
			pd.read_table(filename)：从限定分隔符的文本文件导入数据
			pd.read_excel(filename)：从Excel文件导入数据
			pd.read_sql(query, connection_object)：从SQL表/库导入数据
			pd.read_json(json_string)：从JSON格式的字符串导入数据
			pd.read_html(url)：解析URL、字符串或者HTML文件，抽取其中的tables表格
			pd.read_clipboard()：从你的粘贴板获取内容，并传给read_table()
			pd.DataFrame(dict)：从字典对象导入数据，Key是列名，Value是数据

		2.2导出数据
			df.to_csv(filename)：导出数据到CSV文件
			df.to_excel(filename)：导出数据到Excel文件
			df.to_sql(table_name, connection_object)：导出数据到SQL表
			df.to_json(filename)：以Json格式导出数据到文本文件

		2.3创建测试对象
			pd.DataFrame(np.random.rand(20,5))：创建20行5列的随机数组成的DataFrame对象
			pd.Series(my_list)：从可迭代对象my_list创建一个Series对象
			df.index = pd.date_range('1900/1/30', periods=df.shape[0])：增加一个日期索引

		2.4查看、检查数据
			df.head(n)：查看DataFrame对象的前n行
			df.tail(n)：查看DataFrame对象的最后n行
			df.shape()：查看行数和列数
			http:// df.info() ：查看索引、数据类型和内存信息
			df.describe()：查看数值型列的汇总统计
			s.value_counts(dropna=False)：查看Series对象的唯一值和计数
			df.apply(pd.Series.value_counts)：查看DataFrame对象中每一列的唯一值和计数

		2.5数据选取
			df[col]：根据列名，并以Series的形式返回列
			df[[col1, col2]]：以DataFrame形式返回多列
			s.iloc[0]：按位置选取数据
			s.loc['index_one']：按索引选取数据
			df.iloc[0,:]：返回第一行
			df.iloc[0,0]：返回第一列的第一个元素

		2.6数据清理
			df.columns = ['a','b','c']：重命名列名
			pd.isnull()：检查DataFrame对象中的空值，并返回一个Boolean数组
			pd.notnull()：检查DataFrame对象中的非空值，并返回一个Boolean数组
			df.dropna()：删除所有包含空值的行
			df.dropna(axis=1)：删除所有包含空值的列
			df.dropna(axis=1,thresh=n)：删除所有小于n个非空值的行
			df.fillna(x)：用x替换DataFrame对象中所有的空值
			s.astype(float)：将Series中的数据类型更改为float类型
			s.replace(1,'one')：用‘one’代替所有等于1的值
			s.replace([1,3],['one','three'])：用'one'代替1，用'three'代替3
			df.rename(columns=lambda x: x + 1)：批量更改列名
			df.rename(columns={'old_name': 'new_ name'})：选择性更改列名
			df.set_index('column_one')：更改索引列
			df.rename(index=lambda x: x + 1)：批量重命名索引

		2.7数据处理：Filter、Sort和GroupBy
			df[df[col] > 0.5]：选择col列的值大于0.5的行
			df.sort_values(col1)：按照列col1排序数据，默认升序排列
			df.sort_values(col2, ascending=False)：按照列col1降序排列数据
			df.sort_values([col1,col2], ascending=[True,False])：先按列col1升序排列，后按col2降序排列数据
			df.groupby(col)：返回一个按列col进行分组的Groupby对象
			df.groupby([col1,col2])：返回一个按多列进行分组的Groupby对象
			df.groupby(col1)[col2]：返回按列col1进行分组后，列col2的均值
			df.pivot_table(index=col1, values=[col2,col3], aggfunc=max)：创建一个按列col1进行分组，并计算col2和col3的最大值的数据透视表
			df.groupby(col1).agg(np.mean)：返回按列col1分组的所有列的均值
			data.apply(np.mean)：对DataFrame中的每一列应用函数np.mean
			data.apply(np.max,axis=1)：对DataFrame中的每一行应用函数np.max

		2.8数据合并
			df1.append(df2)：将df2中的行添加到df1的尾部
			df.concat([df1, df2],axis=1)：将df2中的列添加到df1的尾部
			df1.join(df2,on=col1,how='inner')：对df1的列和df2的列执行SQL形式的join

		2.9数据统计
			df.describe()：查看数据值列的汇总统计
			df.mean()：返回所有列的均值
			df.corr()：返回列与列之间的相关系数
			df.count()：返回每一列中的非空值的个数
			df.max()：返回每一列的最大值
			df.min()：返回每一列的最小值
			df.median()：返回每一列的中位数
			df.std()：返回每一列的标准差

	3、Matplotlib
		3.1、散点图
			import matplotlib.pyplot as plt
			import numpy as np
			import matplotlib

			# Fixing random state for reproducibility
			np.random.seed(19680801)


			x = np.arange(0.0, 50.0, 2.0)
			y = x ** 1.3 + np.random.rand(*x.shape) * 30.0
			s = np.random.rand(*x.shape) * 800 + 500

			plt.scatter(x, y, s, c="g", alpha=0.5, marker=r'$\clubsuit$',
			            label="Luck")
			plt.xlabel("Leprechauns")
			plt.ylabel("Gold")
			plt.legend(loc=2)
			plt.show()

		3.2、条形图
			import numpy as np 
			import matplotlib.pyplot as plt 

			index = np.arange(6)

			sales_BJ = [34, 56, 14, 98, 31, 61]
			sales_SH = [98, 67, 54, 76, 23, 59]
			sales_SZ = [80, 58, 34, 23, 99, 11]

			bar_width = 0.25

			plt.bar(index, sales_BJ, bar_width, color='r', label='sales_BJ')
			plt.bar(index+bar_width, sales_SH, bar_width, color='g', label='sales_SH')
			plt.bar(index+bar_width*2, sales_SZ, bar_width, color='b', label='sales_SZ')

			# plt.barh(index, sales_BJ, bar_width, color='r', label='sales_BJ')
			# plt.barh(index+bar_width, sales_SH, bar_width, color='g', label='sales_SH')
			# plt.barh(index+bar_width*2, sales_SZ, bar_width, color='b', label='sales_SZ')

			plt.title("the table of student's grades")
			plt.xlabel('student')
			plt.ylabel('grade')
			plt.legend()
			plt.show()

		3.3、直方图
			import numpy as np
			import matplotlib.pyplot as plt

			# Fixing random state for reproducibility
			np.random.seed(19680801)

			mu, sigma = 100, 15
			x = mu + sigma * np.random.randn(10000)

			# the histogram of the data
			n, bins, patches = plt.hist(x, 50, density=True, facecolor='g', alpha=0.75)


			plt.xlabel('Smarts')
			plt.ylabel('Probability')
			plt.title('Histogram of IQ')
			plt.text(60, .025, r'$\mu=100,\ \sigma=15$')
			plt.axis([40, 160, 0, 0.03])
			plt.grid(True)
			plt.show()

		3.4、折线图
			import matplotlib.pyplot as plt
			import numpy as np

			t = np.arange(0.0, 2.0, 0.2)
			s1 = np.sin(2*np.pi*t)
			s2 = np.sin(4*np.pi*t)

			plt.figure()
			plt.subplot(211)
			plt.plot(t, s1)
			plt.subplot(212)
			plt.plot(t, 2*s1)
			plt.show()

		3.5、扇形图
			import matplotlib.pyplot as plt

			labels = 'Frogs', 'Hogs', 'Dogs', 'Logs'
			sizes = [15, 30, 45, 10]
			explode = (0, 0.1, 0, 0)  

			fig1, ax1 = plt.subplots()
			ax1.pie(sizes, explode=explode, labels=labels, autopct='%1.1f%%',
			        shadow=True, startangle=90)
			ax1.axis('equal')

			plt.show()

		3.6、极坐标图
			import numpy as np
			import matplotlib.pyplot as plt

			r = np.arange(0, 2, 0.01)
			theta = 2 * np.pi * r

			ax = plt.subplot(111, projection='polar')
			ax.plot(theta, r)
			ax.set_rmax(2)
			ax.set_rticks([0.5, 1, 1.5, 2])  
			ax.set_rlabel_position(-22.5)  
			ax.grid(True)
			ax.set_title("A line plot on a polar axis", va='bottom')

			plt.show()	

		3.7、雷达图
			import numpy as np
			import matplotlib.pyplot as plt

			#=======自己设置开始============
			#标签
			labels = np.array(['艺术A','调研I','实际R','常规C','企业E','社会S'])
			#数据个数
			dataLenth = 6
			#数据
			data = np.array([6,4,5,6,7,8])
			#========自己设置结束============

			angles = np.linspace(0, 2*np.pi, dataLenth, endpoint=False)
			data = np.concatenate((data, [data[0]])) # 闭合
			angles = np.concatenate((angles, [angles[0]])) # 闭合

			fig = plt.figure()
			ax = fig.add_subplot(111, polar=True)# polar参数！！
			ax.plot(angles, data, 'bo-', linewidth=2)# 画线
			ax.fill(angles, data, facecolor='r', alpha=0.25)# 填充
			ax.set_thetagrids(angles * 180/np.pi, labels, fontproperties="SimHei")
			ax.set_title("matplotlib雷达图", va='bottom', fontproperties="SimHei")
			ax.set_rlim(0,10)
			ax.grid(True)

			plt.show()


	4、requests

		import requests
		url = http://baidu.com
		headers = {'user-agent': 'my-app/0.0.1'}
		html = requests.get(url, headers=headers)
		html.text
		html.encoding
		html.status_code


	5、re
		

	6、BeautifulSoup


	7、tushare

