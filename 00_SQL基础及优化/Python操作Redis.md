#### 一、redis

	redis是一个key-value存储系统。和Memcached类似，它支持存储的value类型相对更多，包括string(字符串)、list(链表)、set(集合)、zset(sorted set --有序集合)和hash（哈希类型）。这些数据类型都支持push/pop、add/remove及取交集并集和差集及更丰富的操作，而且这些操作都是原子性的。在此基础上，redis支持各种不同方式的排序。与memcached一样，为了保证效率，数据都是缓存在内存中。区别的是redis会周期性的把更新的数据写入磁盘或者把修改操作写入追加的记录文件，并且在此基础上实现了master-slave(主从)同步。

	Redis 是一个高性能的key-value数据库。 redis的出现，很大程度补偿了memcached这类key/value存储的不足，在部 分场合可以对关系数据库起到很好的补充作用。它提供了Python，Ruby，Erlang，PHP客户端，使用很方便,Redis支持主从同步。数据可以从主服务器向任意数量的从服务器上同步，从服务器可以是关联其他从服务器的主服务器。这使得Redis可执行单层树复制。从盘可以有意无意的对数据进行写操作。由于完全实现了发布/订阅机制，使得从数据库在任何地方同步树时，可订阅一个频道并接收主服务器完整的消息发布记录。

---
#### 二、python操作redis

- 1、连接方式

redis-py提供两个类Redis和StrictRedis用于实现Redis的命令，StrictRedis用于实现大部分官方的命令，并使用官方的语法和命令，Redis是StrictRedis的子类

	#!/usr/bin/env python
	# -*- coding:utf-8 -*-
	import redis

	r = redis.Redis(host='192.168.0.110', port=6379,db=0)
	r.set('name', 'zhangsan')   #添加
	print (r.get('name'))   #获取

- 2、连接池

redis-py使用connection pool来管理对一个redis server的所有连接，避免每次建立、释放连接的开销。默认，每个Redis实例都会维护一个自己的连接池。可以直接建立一个连接池，然后作为参数Redis，这样就可以实现多个Redis实例共享一个连接池。

	#!/usr/bin/env python
	# -*- coding:utf-8 -*-
	import redis

	pool = redis.ConnectionPool(host='192.168.0.110', port=6379)
	r = redis.Redis(connection_pool=pool)
	r.set('name', 'zhangsan')   #添加
	print (r.get('name'))   #获取


- 3、 redis详细操作

[redis详细操作命令] (http://www.cnblogs.com/melonjiang/p/5342505.html)



- 4、管道

redis-py默认在执行每次请求都会创建（连接池申请连接）和断开（归还连接池）一次连接操作，如果想要在一次请求中指定多个命令，则可以使用pipline实现一次请求指定多个命令，并且默认情况下一次pipline 是原子性操作。

	#!/usr/bin/env python
	# -*- coding:utf-8 -*-
	import redis
	pool = redis.ConnectionPool(host='192.168.0.110', port=6379)
	r = redis.Redis(connection_pool=pool)

	pipe = r.pipeline(transaction=True)

	r.set('name', 'zhangsan')
	r.set('name', 'lisi')

	pipe.execute()

