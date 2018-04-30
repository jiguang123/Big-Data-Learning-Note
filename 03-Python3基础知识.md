## python基础知识

---	
1、Python中文编码

		Python中默认的编码格式是ASCII 格式，在没修改编码格式时无法正确打印汉字，所以在读取中文时会报错。
		解决方法为只要在文件开头加入 # -*- coding: UTF-8 -*- 或者 #coding=utf-8 就行了

---
2、数据类型

		Python有五个标准的数据类型：
			Numbers（数字）| String（字符串）| List（列表）| Tuple（元组）| Dictionary（字典）

---
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

---
4、python中is和==的区别

	- Python中对象包含的三个基本要素，分别是：id(身份标识) 、type(数据类型)和value(值)。
	- ‘==’比较的是value值
	- ‘is’比较的是id

---
5、简述read、readline、readlines的区别

	- read读取整个文件
	- readline读取下一行数据
	- readlines读取整个文件到一个迭代器以供我们遍历（读取 到一个list中，以供使用，比较方便）

---
6、一个函数接收文件夹的名称作为参数，返回该文件中所有文件的全路径,请补全缺失的代码。

	def print_directry_contents(spath):
	    import os
	    files_list = os.listdir(spath)
	    for file in files_list:
	        print(os.path.realpath(file))