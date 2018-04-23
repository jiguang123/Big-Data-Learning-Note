# 数据分析师的知识体系

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

## linux基础知识
	
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


## Git基本命令

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



## python基础知识
	
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


## 数据分析那些事儿

	1、何为数据分析
		数据分析是指采用适当的统计分析方法对收集来的大量数据进行分析，将它们汇总理解并消化，以最大化地开发数据的功能，发挥数据的作用
		数据分析的目的是把隐藏在一大批看似杂乱无章的数据背后的信息集中和提炼出来，总结出所研究对象的内在规律
		在实际工作中，数据分析能够帮助管理者进行判断和决策，以便采取适当策略和行动

	2、数据分析三大作用
		现状分析 | 原因分析 | 预测分析

	3、数据分析六部曲
		明确分析目的和思路 数据收集 数据处理 数据分析 数据展现 报告撰写


## 机器学习算法

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


## 数据分析常用python库的使用

	1、Numpy

	2、Pandas
	
	3、Matplotlib

	4、requests

	5、re

	6、BeautifulSoup

	7、tushare





