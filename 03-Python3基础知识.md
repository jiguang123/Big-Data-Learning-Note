## python基础知识

---	
1、Python中文编码

	Python中默认的编码格式是ASCII格式，在没修改编码格式时无法正确打印汉字，所以在读取中文时会报错。
	解决方法为只要在文件开头加入# -*- coding: UTF-8 -*-或者#coding=utf-8就行了

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
		1）当rm为空时，默认删除空白符（包括'\n', '\r', '\t',  ' ')
		2）这里的rm删除序列是只要边（开头或结尾）上的字符在删除序列内，就删除掉

	split()函数
		1）按某一个字符分割，如‘.'
			>>> str = ('www.google.com') 
			>>> print str
			www.google.com 
			>>> str_split = str.split('.') 
			>>> print str_split 
			['www', 'google', 'com'] 

		2）按某一个字符分割，且分割n次。如按‘.'分割1次
			>>> str_split = str.split('.',1) 
			>>> print str_split 
			['www', 'google.com'] 

		3）split()函数后面还可以加正则表达式，例如：
		4）split分隔后是一个列表，[0]表示取其第一个元素；
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

---
7、请写一段代码实现Python中list去重

	#方法1
	list1 = [1,1,2,3,3,4]
	set1 = set(list1)
	list1 = list(set1)
	#方法2
	list2 = []
	for i in list1:
	    if i not in list2:
	        list2.append(i)

---
8、创建一个装饰器将下面函数输入的字符串首字母大写

	def greetins(word='hi there'):
	    return word.lower()
	from functools import wraps
	def start_word_upper(func):
	    @wraps(func)
	    def inner(*args,**kwargs):
	        word = func(*args,**kwargs)
	        return word.capitalize()
	    return inner    
	# 装饰器可以在：
	# 1.函数调用之前对函数参数进行操作，直接返回被装饰函数的返回值
	# 2.对返回值进行‘装饰’并返回（本题案例）

---
9、描述yield作用

- 保存当前运行状态（断点），然后暂停执行，即将函数挂起
- 将yeild关键字后面表达式的值作为返回值返回，此时可以理解为起到了return的作用，当使用next()、send()函数让函数从断点处继续执行，即唤醒函数。

---
10、装饰器

- 装饰器本质上是一个Python函数，它可以让其他函数在不需要做任何代码变动的前提下增加额外功能，装饰器的返回值也是一个函数对象。
- 功能：1.引入日志；2.函数执行时间统计；3.执行函数前预备处理；4.执行函数后清理功能；5.权限校验；6.缓存

---
11、你对多线程和多进程的理解

- 进程是系统进行资源分配和调度的一个独立单位，线程是进程的一个实体,是CPU调度和分派的基本单位,它是比进程更小的能独立运行的基本单位.线程自己基本上不拥有系统资源,只拥有一点在运行中必不可少的资源(如程序计数器,一组寄存器和栈),但是它可与同属一个进程的其他的线程共享进程所拥有的全部资源；
- 一个程序至少有一个进程,一个进程至少有一个线程；
- 线程的划分尺度小于进程(资源比进程少)，使得多线程程序的并发性高；
- 进程在执行过程中拥有独立的内存单元，而多个线程共享内存，从而极大地提高了程序的运行效率 ；
- 线线程不能够独立执行，必须依存在进程中；
- 优缺点：线程和进程在使用上各有优缺点：线程执行开销小，但不利于资源的管理和保护；而进程正相反。

---
12、线程中start方法和run方法的区别？

- 若调用start,则先执行主进程，后执行子进程；
- 若调用run，相当于正常的函数调用，将按照程序的顺序执行

---
13、python中如何拷贝一个对象？（赋值，浅拷贝，深拷贝的区别）

- 赋值（=），就是创建了对象的一个新的引用，修改其中任意一个变量都会影响到另一个。
- 浅拷贝：创建一个新的对象，但它包含的是对原始对象中包含项的引用（如果用引用的方式修改其中一个对象，另外一个也会修改改变）{1,完全切片方法；2，工厂函数，如list()；3，copy模块的copy()函数}
- 深拷贝：创建一个新的对象，并且递归的复制它所包含的对象（修改其中一个，另外一个不会改变）{copy模块的deep.deepcopy()函数}

---
14、简述一下你熟悉的NOSQL，它有什么优点和缺点？

redis:

优点：
- 读写性能优异；
- 支持数据持久化，支持AOF和RDB两种持久化方式；
- 支持主从复制，主机会自动将数据同步到从机，可以进行读写分离；
- 数据结构丰富：除了支持string类型的value外还支持string、hash、set、sortedset、list等数据结构。  

缺点：
- Redis不具备自动容错和恢复功能，主机从机的宕机都会导致前端部分读写请求失败，需要等待机器重启或者手动切换前端的IP才能恢复；
- 主机宕机，宕机前有部分数据未能及时同步到从机，切换IP后还会引入数据不一致的问题，降低了系统的可用性;
- Redis的主从复制采用全量复制，复制过程中主机会fork出一个子进程对内存做一份快照，并将子进程的内存快照保存为文件发送给从机，这一过程需要确保主机有足够多的空余内存。若快照文件较大，对集群的服务能力会产生较大的影响，而且复制过程是在从机新加入集群或者从机和主机网络断开重连时都会进行，也就是网络波动都会造成主机和从机间的一次全量的数据复制，这对实际的系统运营造成了不小的麻烦;
- Redis较难支持在线扩容，在集群容量达到上限时在线扩容会变得很复杂。为避免这一问题，运维人员在系统上线时必须确保有足够的空间，这对资源造成了很大的浪费。


---
15、把字符串“HELLO PYTHON”从大写字母全部转换成小写字母并换行显示，然后输出到计算机c盘的hello.txt文件中保存。

	str = 'HELLO PYTHON'
	with open(r'C:/hello.txt','a') as f:
    	for letter in str:
	        letter = letter.lower()
	        f.write(letter)
	        f.write('\n')

---
16、合并列表a=[1,2,3,4]和b=[5,6,7,8]

	a.extend(b)

---
17、列表a，请写出实现正序排列，倒序排列，逆序排列的内置方法

	# 正序
	a.sort()
	# 倒序
	a.sort(reverse=Ture)
	# 逆序
	a.reverse()


---
18、请阐述__new__和__init__的区别？

- __new__:创建对象时调用，会返回当前对象的一个实例
- __init__:创建完对象后调用，对当前对象的一些实例初始化，无返回值
- 调用顺序：先调用__new__生成一个实例再调用__init__方法对实例进行初始化，比如添加属性。

---
19、用yield写出一个生成器

	def generator():
    	for i in range(5):
        	yield i

---
20、描述对super，pass，yield，lambda关键字修饰的理解

- super：在继承中充当父类的代理对象，在多继承中，super的调用顺序是MRO的顺序。
- pass：空语句，什么也不做，在特别的时候用来保证格式或是语义的完整性。
- yield：
    - 1.保存当前运行状态（断点），然后暂停执行，即将函数挂起
    - 2.将yeild关键字后面表达式的值作为返回值返回，此时可以理解为起到了return的作用，当使用next()、send()函数让函数从断点处继续执行，即唤醒函数。
- lambda：定义匿名函数

---
21、对比一下dict中items与iteritems?

	>>> D = {'a':1,'b':2,'c':3,'d':4}    
	>>> D.items()                       #一次性取出所有    
	[('a', 1), ('c', 3), ('b', 2), ('d', 4)]    
	>>> D.iteritems()                   #迭代对象，每次取出一个。用for循环遍历出来；    
	<dictionary-itemiterator object at 0x00000000026243B8>    
	>>> for i in D.iteritems():    
	...   print i,    
	...    
	('a', 1) ('c', 3) ('b', 2) ('d', 4)    
	>>> for k,v in D.iteritems():    
	...   print k,    
	...    
	a c b d    
	总结:   
	1. 一般iteritems()迭代的办法比items()要快，特别是数据库比较大时。  
	2. 在Python3中一般取消前者函数  

---
22、有用过with statement吗？它的好处是什么？

	>>> with open('text.txt') as myfile:    
	...     while True:    
	...         line = myfile.readline()    
	...         if not line:    
	...              break    
	...         print line,    
	    
	# with语句使用所谓的上下文管理器对代码块进行包装，允许上下文管理器实现一些设置和清理操作。    
	# 例如：文件可以作为上下文管理器使用，它们可以关闭自身作为清理的一部分。    
	# NOTE：在PYTHON2.5中，需要使用from __future__ import with_statement进行with语句的导入    

---
23、Python匹配HTML tag的时候，<.*>和<.*?>有什么区别

	import re  
	s = ‘<html><head><title>Title</title>’  
	print(re.match(‘<.*>’, s).group())  
	  
	会返回一个匹配<html><head><title>Title</title>而不是<html>  
	  
	而  
	  
	import re  
	s = ‘<html><head><title>Title</title>’  
	print(re.match(‘<.*?>’, s).group())  
	  
	则会返回<html>  
	  
	<.*>这种匹配称作贪心匹配 <.*?>称作非贪心匹配  

---
24、Python里面search()和match()的区别

	>>> import re  
	>>> re.match(r'python','Programing Python, should be pythonic')  
	>>> obj1 = re.match(r'python','Programing Python, should be pythonic')  #返回None  
	>>> obj2 = re.search(r'python','Programing Python, should be pythonic') #找到pythonic  
	>>> obj2.group()  
	'python'  
	#re.match只匹配字符串的开始，如果字符串开始不符合正则表达式，则匹配失败，函数返回None；  
	#re.search匹配整个字符串，直到找到一个匹配。  

---
 25、Python程序中文输出问题怎么解决

	在Python3中，对中文进行了全面的支持，但在Python2.x中需要进行相关的设置才能使用中文。否则会出现乱码。  
	Python默认采取的ASCII编码，字母、标点和其他字符只使用一个字节来表示，但对于中文字符来说，一个字节满足不了需求。  
	为了能在计算机中表示所有的中文字符，中文编码采用两个字节表示。如果中文编码和ASCII混合使用的话，就会导致解码错误，从而才生乱码。  
	解决办法:  
	交互式命令中：一般不会出现乱码，无需做处理   
	py脚本文件中：跨字符集必须做设置，否则乱码  
	1. 首先在开头一句添加:  
	# coding = utf-8    
	# 或    
	# coding = UTF-8    
	# 或    
	# -*- coding: utf-8 -*-   
	2. 其次需将文件保存为UTF-8的格式！  
	3. 最后: s.decode('utf-8').encode('gbk')  

---
26、请写出一段Python代码实现删除一个list里面的重复元素

	>>> L1 = [4,1,3,2,3,5,1]  
	>>> L2 = []  
	>>> [L2.append(i) for i in L1 if i not in L2]  
	>>> print L2  
	[4, 1, 3, 2, 5]  

---
27、Python是如何进行类型转换的

	>>> int('1234')                   # 将数字型字符串转为整形  
	1234  
	>>> float(12)                     # 将整形或数字字符转为浮点型  
	12.0  
	>>> str(98)                       # 将其他类型转为字符串型  
	'98'  
	>>> list('abcd')                  # 将其他类型转为列表类型  
	['a', 'b', 'c', 'd']  
	>>> dict.fromkeys(['name','age']) # 将其他类型转为字典类型  
	{'age': None, 'name': None}  
	>>> tuple([1, 2, 3, 4])           # 将其他类型转为元祖类型  
	(1, 2, 3, 4)  

	详细转换总结如下:
	函数                      描述  
	int(x [,base])              将x转换为一个整数  
	long(x [,base] )            将x转换为一个长整数  
	float(x)                    将x转换到一个浮点数  
	complex(real [,imag])       创建一个复数  
	str(x)                      将对象 x 转换为字符串  
	repr(x)                     将对象 x 转换为表达式字符串  
	eval(str)                   用来计算在字符串中的有效Python表达式,并返回一个对象  
	tuple(s)                    将序列 s 转换为一个元组  
	list(s)                     将序列 s 转换为一个列表  
	set(s)                      转换为可变集合  
	dict(d)                     创建一个字典。d 必须是一个序列 (key,value)元组。  
	frozenset(s)                转换为不可变集合  
	chr(x)                      将一个整数转换为一个字符  
	unichr(x)                   将一个整数转换为Unicode字符  
	ord(x)                      将一个字符转换为它的整数值  
	hex(x)                      将一个整数转换为一个十六进制字符串  
	oct(x)                      将一个整数转换为一个八进制字符串 


---
28、如何用Python删除一个文件

	import os  
	os.remove(filename)  

---
29、Python代码得到列表list的交集与差集

	>>> list1 = [1, 3, 4, 6]  
	>>> list2 = [1, 2, 3, 4]  
	>>> [i for i in list1 if i not in list2]  
	[6]  
	>>> [i for i in list1 if i in list2]  
	[1, 3, 4] 

---
30、介绍一下Python下range()函数的用法

	>>> range(10)  
	[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]  
	>>> range(1, 10)  
	[1, 2, 3, 4, 5, 6, 7, 8, 9]  
	>>> range(0, 9, 2)  
	[0, 2, 4, 6, 8]  
	>>> range(99,0,-10)  
	[99, 89, 79, 69, 59, 49, 39, 29, 19, 9]  
	相区别的是xrange(),每次只取出一个迭代对象，如果是数据量比较大时，效率较高  
	在Python3中，没有xrange()函数，其功能放在了range()函数上  

---
31、如何用Python来进行查询和替换一个文本字符串

	>>> words = 'Python is a very funny language!'  
	>>> words.find('Python')             # 返回的为0或正数时，为其索引号  
	0  
	>>> words.find('is')  
	7  
	>>> words.find('dafa')               # 返回-1表示查找失败  
	-1  
	>>> words.replace('Python', 'Perl')  # replace()替换  
	'Perl is a very funny language!'  

---
32、默写尽可能多的str对象的方法

	
	#方法                                   #描述    
	-------------------------------------------------------------------------------------------------    
	S.capitalize()                          #返回首字母大写的字符串的副本    
	S.center(width[,fillchar])              #返回一个长度为max(len(S),width),S居中，两侧fillchar填充    
	S.count(sub[,start[,end]])              #计算子字符串sub的出现次数，可将搜索范围限制为S[start:end]    
	S.decode([encoding[,error]])            #返回使用给定编码方式的字符串的解码版本，由error指定错误处理方式    
	S.endswith(suffix[start[,end]])         #检查S是否以suffix结尾，可给定[start:end]来选择匹配的范围    
	S.expandtabs([tabsize])                 #返回字符串的副本，其中tab字符会使用空格进行扩展，可选择tabsize    
	S.find(sun[,start[,end]])               #返回子字符串sub的第一个索引，不存在则为-1,可选择搜索范围    
	S.index(sub[,start[,end]])              #返回子字符串sub的第一个索引，不存在则引发ValueError异常.    
	S.isalnum()                             #检查字符串是否由字母或数字字符组成    
	S.isalpha()                             #检查字符串是否由字母字符组成    
	S.isdigit()                             #检查字符串是否由数字字符组成    
	S.islower()                             #检查字符串是否由小写字母组成    
	S.isspace()                             #检查字符串是否由空格组成    
	S.istitle()                             #检查字符串时候首字母大写    
	S.isupper()                             #检查字符串是否由大写字母组成    
	S.join(sequence)                        #返回其中sequence的字符串元素由S连接的字符串    
	S.ljust(width[,fillchar])               #返回S副本左对齐的字符串,长度max(len(S),W),右侧fillchar填充    
	S.lower()                               #返回所有字符串都为小写的副本    
	S.lstrip([char])                        #向左移除所有char，默认移除(空格,tab,\n)    
	S.partition(seq)                        #在字符串中搜索seq并返回    
	S.replace(old,new[,max])                #将new替换olad,最多可替换max次    
	S.rfind(sub[,start[,end]])              #返回sub所在的最后一个索引，不存在则为-1,可定搜索范围S[start:end]    
	S.rindex(sub[,start[,end]])             #返回sub所在的最后一个索引，不存在则会引发ValueError异常。    
	S.rjust(width[,fillchar])               #返回S副本右对齐的字符串,长度max(len(S),W),左侧fillchar填充    
	S.rpartition(seq)                       #同Partition,但从右侧开始查找    
	S.rstip([char])                         #向右移除所有char，默认移除(空格,tab,\n)    
	S.rsplit(sep[,maxsplit])                #同split,但是使用maxsplit时是从右往左进行计数    
	S.split(sep[,maxsplit])                 #使用sep做为分割符,可使用maxsplit指定最大切分数    
	S.zfill(width)                          #在S的左侧以0填充width个字符    
	S.upper()                               #返回S的副本，所有字符大写    
	S.splitlines([keepends])                #返回S中所有行的列表，可选择是否包括换行符    
	S.startswith(prefix[,start[,end]])      #检查S是否以prefix开始，可用[start,end]来定义范围    
	S.strip([chars])                        #移除所有字符串中含chars的字符，默认移除(空格，tab,\n)    
	S.swapcase()                            #返回S的副本，所有大小写交换    
	S.title()                               #返回S的副本，所有单词以大写字母开头    
	S.translate(table[,deletechars])        #返回S的副本，所有字符都使用table进行的转换，可选择删除出现在deletechars中的所有字符    

