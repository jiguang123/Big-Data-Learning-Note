## python操作MongoDB
---
- windows环境下安装MongoDB

	pip install pymongo

- 然后确保MongoDB已经安装且可以正常运行，去官网下载相应版本：https://www.mongodb.com/

	mkdir -p /home/tools
	cd/home/tools
	get https://fastdl.mongodb.org/linux/mongodb-linux-x86_64-3.4.2.tgz

- 解压文件并修改目录名

	tar -zxvf mongodb-linux-x86_64-3.4.2.tgz
	mv mongodb-linux-x86_64-3.4.2 mongodb3.4.2
	ln -s mongodb_3.4.2 mongodb

- MongoDB 的可执行文件位于 bin 目录下，所以可以将其添加到 PATH 路径中

	export PATH=/home/tools/mongodb/bin:$PATH

- MongoDB的数据存储在data目录的db目录下，但是这个目录在安装过程不会自动创建，所以你需要手动创建data目录，并在data目录中创建db目录。

	mkdir -p /data/db

- 在mongo安装目录中的bin目录执行mongod命令来启动mongdb服务

	./mongod --dbpath /data/db

如果想进入MongoDB后台管理

	./mongo

- 使用用户 admin 使用密码 123456 连接到本地的 MongoDB 服务上

	mongodb://admin:123456@localhost/

- 创建数据库（如果数据库不存在，则创建数据库，否则切换到指定数据库）

	> use test
	switched to db test
	> db
	test
	> show dbs    #查看所有数据库
	admin  0.000GB
	local  0.000GB



---
#### python连接mongodb

	#!/usr/bin/env python
	# -*- coding:utf-8 -*-

	from pymongo import MongoClient

	conn = MongoClient('192.168.0.113', 27017)
	db = conn.mydb  #连接mydb数据库，没有则自动创建
	my_set = db.test_set　　#使用test_set集合，没有则自动创建

	#插入数据（insert插入一个列表多条数据不用遍历，效率高， save需要遍历列表，一个个插入）
	my_set.insert({"name":"zhangsan","age":18})
	#或
	my_set.save({"name":"zhangsan","age":18})

	#添加多条数据到集合中
	users=[{"name":"zhangsan","age":18},{"name":"lisi","age":20}]  
	my_set.insert(users) 
	#或
	my_set.save(users) 

	#查询全部
	for i in my_set.find():
	    print(i)
	#查询name=zhangsan的
	for i in my_set.find({"name":"zhangsan"}):
	    print(i)
	print(my_set.find_one({"name":"zhangsan"}))


---
#### 参考资料
[python操作mongodb详细操作] (https://www.cnblogs.com/melonjiang/p/6536876.html)
[极客学院mongodb数据库文档] (http://wiki.jikexueyuan.com/project/start-learning-python/232.html)
[pymongo官方文档翻译] (http://www.cnblogs.com/zhouxuchen/p/5544227.html)
[Python连接MongoDB操作] (https://www.yiibai.com/mongodb/mongodb_python.html)
[python之MySQLdb库的使用 (http://wiki.jikexueyuan.com/project/python-actual-combat/tutorial-13.html)
