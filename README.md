#数据分析师的知识体系

##################################################################################
	
	Create a new repository on the command line
	echo "# Big-Data-Learning-Note" >> README.md
		git init
		git add README.md
		git commit -m "first commit"
		git remote add origin git@github.com:jiguang123/Big-Data-Learning-Note.git
		git push -u origin master

	Push an existing repository from the command line
	 	git remote add origin git@github.com:jiguang123/Big-Data-Learning-Note.git
		git push -u origin master
##################################################################################

##linux基础知识
	
	1、常用指令
	ls　　        显示文件或目录
	     -l           列出文件详细信息l(list)
	     -a          列出当前目录下所有文件及目录，包括隐藏的a(all)
	mkdir         创建目录
	     -p           创建目录，若无父目录，则创建p(parent)
	cd               切换目录
	touch          创建空文件
	echo            创建带有内容的文件。
	cat              查看文件内容
	cp                拷贝
	mv               移动或重命名
	rm               删除文件
	     -r            递归删除，可删除子目录及文件
	     -f            强制删除
	find              在文件系统中搜索某文件
	wc                统计文本中行数、字数、字符数
	grep             在文本文件中查找某个字符串
	rmdir           删除空目录
	tree             树形结构显示目录，需要安装tree包
	pwd              显示当前目录
	ln                  创建链接文件
	more、less  分页显示文本文件内容
	head、tail    显示文件头、尾内容
	ctrl+alt+F1  命令行全屏模式

	2、系统管理命令
	stat              显示指定文件的详细信息，比ls更详细
	who               显示在线登陆用户
	whoami          显示当前操作用户
	hostname      显示主机名
	uname           显示系统信息
	top                动态显示当前耗费资源最多进程信息
	ps                  显示瞬间进程状态 ps -aux
	du                  查看目录大小 du -h /home带有单位显示目录信息
	df                  查看磁盘大小 df -h 带有单位显示磁盘信息
	ifconfig          查看网络情况
	ping                测试网络连通
	netstat          显示网络状态信息
	man                命令不会用了，找男人  如：man ls
	clear              清屏
	alias               对命令重命名 如：alias showmeit="ps -aux" ，另外解除使用unaliax showmeit
	kill                 杀死进程，可以先用ps 或 top命令查看进程的id，然后再用kill命令杀死进程。

	3、vim使用

	vim三种模式：命令模式、插入模式、编辑模式。使用ESC或i或：来切换模式。
	命令模式下：
	:q                      退出
	:q!                     强制退出
	:wq                   保存并退出
	:set number     显示行号
	:set nonumber  隐藏行号
	/apache            在文档中查找apache 按n跳到下一个，shift+n上一个
	yyp                   复制光标所在行，并粘贴
	h(左移一个字符←)、j(下一行↓)、k(上一行↑)、l(右移一个字符→)


##Git基本命令

	1.安装Git
		Linux ：sudo apt-get install git-all
		OS X  ：最简单的方式是使用homebrew安装，命令行执行 brew install git
	2.配置Git
		$ git config --global user.name "My Name"
		$ git config --global user.email myEmail@example.com
		查看已有配置：git config --list
	3.创建一个新仓库
		在桌面创建一个联系文件夹 git_exercise, 打开终端：
		$ cd Desktop/git_exercise/
		$ git init
	4.检查状态 
		$ git status
	5.暂存 – git add
		git有个概念叫暂存区，你可以把它看成一块空白帆布，包裹着所有你可能会提交的变动。它一开始为空，你可以通过git add 命令添加内容，并使用 git commit 提交。
		这个例子中只有一个文件：
		$ git add hello.txt
		如果需要提交目录下的所有内容，可以这样：
		$ git add .
	6.提交 – git commit
		$ git commit -m "Initial commit."
	7.远端仓库
		1.链接远端仓库 – git remote add
		$ git remote add origin https://github.com/tutorialzine/awesome-project.git
		2.上传到服务器 – git push
		$ git push origin master
		3.克隆仓库 – git clone
		$ git clone https://github.com/tutorialzine/awesome-project.git
	8.创建新分支 – git branch
		每一个仓库的默认分支都叫master, 创建新分支可以这样：
		$ git branch amazing_new_feature
		创建了一个名为amazing_new_feature的新分支，它跟当前分支同一起点
	9.切换分支 – git checkout
		单独使用git branch，可以查看分支状态：
		$ git branch
		  amazing_new_feature
		  * master
		* 号表示当前活跃分支为master，使用git checkout切换分支。
		$ git checkout amazing_new_feature
	10.合并分支 – git merge
		我们的 amazing_new_feature 分支的任务是增加一个featuer.txt。我们来创建，添加到暂存区，提交。
		$ git add feature.txt
		$ git commit -m "New feature complete."
		新分支任务完成了，回到master分支
		$ git checkout master
		现在去查看文件，你会发现，之前创建的feature.txt文件不见了，因为master分支上并没有feature.txt。使用git merge 把 amazing_new_feature 分支合并到master上。
		$ git merge amazing_new_feature
		ok! 然后再把amazing_new_feature 分支删掉吧。
		$ git branch -d amazing_new_feature
	11.查看日志 - git log 
	12.查看差异 - git diff



##python基础知识
	
	1、Python中文编码
		Python中默认的编码格式是ASCII 格式，在没修改编码格式时无法正确打印汉字，所以在读取中文时会报错。
		解决方法为只要在文件开头加入 # -*- coding: UTF-8 -*- 或者 #coding=utf-8 就行了

	2、数据类型
		Python有五个标准的数据类型：
			Numbers（数字）| String（字符串）| List（列表）| Tuple（元组）| Dictionary（字典）

	3、strip()函数和split()函数的详解
		strip()函数 
			函数原型
			声明：s为字符串，rm为要删除的字符序列
			s.strip(rm)       删除s字符串中开头、结尾处，位于 rm删除序列的字符
			s.lstrip(rm)      删除s字符串中开头处，位于 rm删除序列的字符
			s.rstrip(rm)     删除s字符串中结尾处，位于 rm删除序列的字符
			注意：
			（1）当rm为空时，默认删除空白符（包括'\n', '\r', '\t',  ' ')
			（2）这里的rm删除序列是只要边（开头或结尾）上的字符在删除序列内，就删除掉

		split()函数
			（1）按某一个字符分割，如‘.'
				>>> str = ('www.google.com') 
				>>> print str
				www.google.com 
				>>> str_split = str.split('.') 
				>>> print str_split 
				['www', 'google', 'com'] 

			（2）按某一个字符分割，且分割n次。如按‘.'分割1次
				>>> str_split = str.split('.',1) 
				>>> print str_split 
				['www', 'google.com'] 

			（3）split()函数后面还可以加正则表达式，例如：
			（4）split分隔后是一个列表，[0]表示取其第一个元素；
				>>> str_split = str.split('.')[0] 
				>>> print str_split 
				www 


##数据分析那些事儿

	1、何为数据分析
		数据分析是指采用适当的统计分析方法对收集来的大量数据进行分析，将它们汇总理解并消化，以最大化地开发数据的功能，发挥数据的作用
		数据分析的目的是把隐藏在一大批看似杂乱无章的数据背后的信息集中和提炼出来，总结出所研究对象的内在规律
		在实际工作中，数据分析能够帮助管理者进行判断和决策，以便采取适当策略和行动

	2、数据分析三大作用
		现状分析 | 原因分析 | 预测分析

	3、数据分析六部曲
		明确分析目的和思路 数据收集 数据处理 数据分析 数据展现 报告撰写


##机器学习算法

	1、决策树

	2、随机森林算法

	3、逻辑回归

	4、支持向量机SVM

	5、朴素贝叶斯

	6、K最近邻算法

	7、K-means

	8、Adaboost算法

	9、神经网络

	10、马尔科夫


##数据分析常用python库的使用

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

	4、requests

		import requests
		url = http://baidu.com
		headers = {'user-agent': 'my-app/0.0.1'}
		html = requests(url, headers=headers)
		html.text
		html.encoding
		html.status_code

	5、re

	6、BeautifulSoup





