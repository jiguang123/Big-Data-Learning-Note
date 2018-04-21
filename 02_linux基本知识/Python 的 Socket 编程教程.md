# Python 的 Socket 编程教程
这是用来快速学习 Python Socket 套接字编程的指南和教程。Python 的 Socket 编程跟 C 语言很像。

Python 官方关于 Socket 的函数请看 http://docs.python.org/library/socket.html

基本上，Socket 是任何一种计算机网络通讯中最基础的内容。例如当你在浏览器地址栏中输入 www.oschina.net 时，你会打开一个套接字，然后连接到 www.oschina.net 并读取响应的页面然后然后显示出来。而其他一些聊天客户端如 gtalk 和 skype 也是类似。任何网络通讯都是通过 Socket 来完成的。

---

## 写在开头

本教程假设你已经有一些基本的 Python 编程的知识。

让我们开始 Socket 编程吧。

## 创建 Socket

首先要做的就是创建一个 Socket，socket 的 socket 函数可以实现，代码如下：


```
#Socket client example in python

import socket	#for sockets

#create an AF_INET, STREAM socket (TCP)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

print 'Socket Created'
```

函数 socket.socket 创建了一个 Socket，并返回 Socket 的描述符可用于其他 Socket 相关的函数。

上述代码使用了下面两个属性来创建 Socket：

- 地址簇 : AF_INET (IPv4)
- 类型: SOCK_STREAM (使用 TCP 传输控制协议)


---

### 错误处理

如果 socket 函数失败了，python 将抛出一个名为 socket.error 的异常，这个异常必须予以处理：

```
#handling errors in python socket programs

import socket	#for sockets
import sys	#for exit

try:
	#create an AF_INET, STREAM socket (TCP)
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error, msg:
	print 'Failed to create socket. Error code: ' + str(msg[0]) + ' , Error message : ' + msg[1]
	sys.exit();

print 'Socket Created'
```
好了，假设你已经成功创建了 Socket，下一步该做什么呢？接下来我们将使用这个 Socket 来连接到服务器。

### 注意

与 SOCK_STREAM 相对应的其他类型是 SOCK_DGRAM 用于 UDP 通讯协议，UDP 通讯是非连接 Socket，在这篇文章中我们只讨论 SOCK_STREAM ，或者叫 TCP 。

## 连接到服务器

连接到服务器需要服务器地址和端口号，这里使用的是 www.oschina.net 和 80 端口。

### 首先获取远程主机的 IP 地址

连接到远程主机之前，我们需要知道它的 IP 地址，在 Python 中，获取 IP 地址是很简单的：

```
import socket	#for sockets
import sys	#for exit

try:
	#create an AF_INET, STREAM socket (TCP)
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error, msg:
	print 'Failed to create socket. Error code: ' + str(msg[0]) + ' , Error message : ' + msg[1]
	sys.exit();

print 'Socket Created'

host = 'www.oschina.net'

try:
	remote_ip = socket.gethostbyname( host )

except socket.gaierror:
	#could not resolve
	print 'Hostname could not be resolved. Exiting'
	sys.exit()
	
print 'Ip address of ' + host + ' is ' + remote_ip
```

我们已经有 IP 地址了，接下来需要指定要连接的端口。

代码：

```
import socket	#for sockets
import sys	#for exit

try:
	#create an AF_INET, STREAM socket (TCP)
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error, msg:
	print 'Failed to create socket. Error code: ' + str(msg[0]) + ' , Error message : ' + msg[1]
	sys.exit();

print 'Socket Created'

host = 'www.oschina.net'
port = 80

try:
	remote_ip = socket.gethostbyname( host )

except socket.gaierror:
	#could not resolve
	print 'Hostname could not be resolved. Exiting'
	sys.exit()
	
print 'Ip address of ' + host + ' is ' + remote_ip

#Connect to remote server
s.connect((remote_ip , port))

print 'Socket Connected to ' + host + ' on ip ' + remote_ip
```

现在运行程序

```
$ python client.py
Socket Created
Ip address of www.oschina.net is 61.145.122.155
Socket Connected to www.oschina.net on ip 61.145.122.155
```

这段程序创建了一个 Socket 并进行连接，试试使用其他一些不存在的端口（如81）会是怎样？这个逻辑相当于构建了一个端口扫描器。

已经连接上了，接下来就是往服务器上发送数据。

### 免费提示

使用 SOCK_STREAM/TCP 套接字才有“连接”的概念。连接意味着可靠的数据流通讯机制，可以同时有多个数据流。可以想象成一个数据互不干扰的管道。另外一个重要的提示是：数据包的发送和接收是有顺序的。

其他一些 Socket 如 UDP、ICMP 和 ARP 没有“连接”的概念，它们是无连接通讯，意味着你可从任何人或者给任何人发送和接收数据包。


---
## 发送数据

sendall 函数用于简单的发送数据，我们来向 oschina 发送一些数据：

```
import socket	#for sockets
import sys	#for exit

try:
	#create an AF_INET, STREAM socket (TCP)
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error, msg:
	print 'Failed to create socket. Error code: ' + str(msg[0]) + ' , Error message : ' + msg[1]
	sys.exit();

print 'Socket Created'

host = 'www.oschina.net'
port = 80

try:
	remote_ip = socket.gethostbyname( host )

except socket.gaierror:
	#could not resolve
	print 'Hostname could not be resolved. Exiting'
	sys.exit()
	
print 'Ip address of ' + host + ' is ' + remote_ip

#Connect to remote server
s.connect((remote_ip , port))

print 'Socket Connected to ' + host + ' on ip ' + remote_ip

#Send some data to remote server
message = "GET / HTTP/1.1\r\n\r\n"

try :
	#Set the whole string
	s.sendall(message)
except socket.error:
	#Send failed
	print 'Send failed'
	sys.exit()

print 'Message send successfully'
```

上述例子中，首先连接到目标服务器，然后发送字符串数据 "GET / HTTP/1.1\r\n\r\n" ，这是一个 HTTP 协议的命令，用来获取网站首页的内容。

接下来需要读取服务器返回的数据。

## 接收数据

recv 函数用于从 socket 接收数据：

```
#Socket client example in python

import socket	#for sockets
import sys	#for exit

#create an INET, STREAMing socket
try:
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error:
	print 'Failed to create socket'
	sys.exit()
	
print 'Socket Created'

host = 'oschina.net';
port = 80;

try:
	remote_ip = socket.gethostbyname( host )

except socket.gaierror:
	#could not resolve
	print 'Hostname could not be resolved. Exiting'
	sys.exit()

#Connect to remote server
s.connect((remote_ip , port))

print 'Socket Connected to ' + host + ' on ip ' + remote_ip

#Send some data to remote server
message = "GET / HTTP/1.1\r\nHost: oschina.net\r\n\r\n"

try :
	#Set the whole string
	s.sendall(message)
except socket.error:
	#Send failed
	print 'Send failed'
	sys.exit()

print 'Message send successfully'

#Now receive data
reply = s.recv(4096)

print reply
```
下面是上述程序执行的结果：

```
$ python client.py
Socket Created
Ip address of oschina.net is 61.145.122.
Socket Connected to oschina.net on ip 61.145.122.155
Message send successfully
HTTP/1.1 301 Moved Permanently
Server: nginx
Date: Wed, 24 Oct 2012 13:26:46 GMT
Content-Type: text/html
Content-Length: 178
Connection: keep-alive
Keep-Alive: timeout=20
Location: http://www.oschina.net/
```

oschina.net 回应了我们所请求的 URL 的内容，很简单。数据接收完了，可以关闭 Socket 了。

## 关闭 socket

close 函数用于关闭 Socket：

```
s.close()
```

这就是了。

## 让我们回顾一下

上述的示例中我们学到了如何：

1. 创建 Socket
2. 连接到远程服务器
3. 发送数据
4. 接收回应

当你用浏览器打开 www.oschina.net 时，其过程也是一样。包含两种类型，分别是客户端和服务器，客户端连接到服务器并读取数据，服务器使用 Socket 接收进入的连接并提供数据。因此在这里 www.oschina.net 是服务器端，而你的浏览器是客户端。

接下来我们开始在服务器端做点编码。


---
## 服务器端编程

服务器端编程主要包括下面几步：

1. 打开 socket
2. 绑定到一个地址和端口
3. 侦听进来的连接
4. 接受连接
5. 读写数据

我们已经学习过如何打开 Socket 了，下面是绑定到指定的地址和端口上。

## 绑定 Socket

bind 函数用于将 Socket 绑定到一个特定的地址和端口，它需要一个类似 connect 函数所需的 sockaddr_in 结构体。

示例代码：


```
import socket
import sys

HOST = ''	# Symbolic name meaning all available interfaces
PORT = 8888	# Arbitrary non-privileged port

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'

try:
	s.bind((HOST, PORT))
except socket.error , msg:
	print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
	sys.exit()
	
print 'Socket bind complete'
```

绑定完成后，就需要让 Socket 开始侦听连接。很显然，你不能将两个不同的 Socket 绑定到同一个端口之上。

## 连接侦听

绑定 Socket 之后就可以开始侦听连接，我们需要将 Socket 变成侦听模式。socket 的 listen 函数用于实现侦听模式：


```
s.listen(10)
print 'Socket now listening'
```

isten 函数所需的参数成为 backlog，用来控制程序忙时可保持等待状态的连接数。这里我们传递的是 10，意味着如果已经有 10 个连接在等待处理，那么第 11 个连接将会被拒绝。当检查了 socket_accept 后这个会更加清晰。


---
## 接受连接

示例代码：

```
import socket
import sys

HOST = ''	# Symbolic name meaning all available interfaces
PORT = 8888	# Arbitrary non-privileged port

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'

try:
	s.bind((HOST, PORT))
except socket.error , msg:
	print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
	sys.exit()
	
print 'Socket bind complete'

s.listen(10)
print 'Socket now listening'

#wait to accept a connection - blocking call
conn, addr = s.accept()

#display client information
print 'Connected with ' + addr[0] + ':' + str(addr[1])
```

### 输出

运行该程序将会显示：

```
$ python server.py
Socket created
Socket bind complete
Socket now listening
```
现在这个程序开始等待连接进入，端口是 8888，请不要关闭这个程序，我们来通过 telnet 程序来进行测试。

打开命令行窗口并输入：


```
$ telnet localhost 8888

It will immediately show
$ telnet localhost 8888
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
Connection closed by foreign host.
```

而服务器端窗口显示的是：

```
$ python server.py
Socket created
Socket bind complete
Socket now listening
Connected with 127.0.0.1:59954
```

我们可看到客户端已经成功连接到服务器。

上面例子我们接收到连接并立即关闭，这样的程序没什么实际的价值，连接建立后一般会有大量的事情需要处理，因此让我们来给客户端做出点回应吧。

sendall 函数可通过 Socket 给客户端发送数据：


```
import socket
import sys

HOST = ''	# Symbolic name meaning all available interfaces
PORT = 8888	# Arbitrary non-privileged port

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'

try:
	s.bind((HOST, PORT))
except socket.error , msg:
	print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
	sys.exit()
	
print 'Socket bind complete'

s.listen(10)
print 'Socket now listening'

#wait to accept a connection - blocking call
conn, addr = s.accept()

print 'Connected with ' + addr[0] + ':' + str(addr[1])

#now keep talking with the client
data = conn.recv(1024)
conn.sendall(data)

conn.close()
s.close()
```

继续运行上述代码，然后打开另外一个命令行窗口输入下面命令：


```
$ telnet localhost 8888
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
happy
happy
Connection closed by foreign host.
```

可看到客户端接收到来自服务器端的回应内容。

上面的例子还是一样，服务器端回应后就立即退出了。而一些真正的服务器像 www.oschina.net 是一直在运行的，时刻接受连接请求。

也就是说服务器端应该一直处于运行状态，否则就不能成为“服务”，因此我们要让服务器端一直运行，最简单的方法就是把 accept 方法放在一个循环内。


---
## 一直在运行的服务器

对上述代码稍作改动：


```
import socket
import sys

HOST = ''	# Symbolic name meaning all available interfaces
PORT = 8888	# Arbitrary non-privileged port

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'

try:
	s.bind((HOST, PORT))
except socket.error , msg:
	print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
	sys.exit()
	
print 'Socket bind complete'

s.listen(10)
print 'Socket now listening'

#now keep talking with the client
while 1:
    #wait to accept a connection - blocking call
	conn, addr = s.accept()
	print 'Connected with ' + addr[0] + ':' + str(addr[1])
	
	data = conn.recv(1024)
	reply = 'OK...' + data
	if not data: 
		break
	
	conn.sendall(reply)

conn.close()
s.close()
```
很简单只是加多一个 while 1 语句而已。

继续运行服务器，然后打开另外三个命令行窗口。每个窗口都使用 telnet 命令连接到服务器：


```
$ telnet localhost 5000
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
happy
OK .. happy
Connection closed by foreign host.
```

服务器所在的终端窗口显示的是：

```
$ python server.py
Socket created
Socket bind complete
Socket now listening
Connected with 127.0.0.1:60225
Connected with 127.0.0.1:60237
Connected with 127.0.0.1:60239
```

你看服务器再也不退出了，好吧，用 Ctrl+C 关闭服务器，所有的 telnet 终端将会显示 "Connection closed by foreign host."

已经很不错了，但是这样的通讯效率太低了，服务器程序使用循环来接受连接并发送回应，这相当于是一次最多处理一个客户端的请求，而我们要求服务器可同时处理多个请求。


---
## 处理多个连接

为了处理多个连接，我们需要一个独立的处理代码在主服务器接收到连接时运行。一种方法是使用线程，服务器接收到连接然后创建一个线程来处理连接收发数据，然后主服务器程序返回去接收新的连接。

下面是我们使用线程来处理连接请求：


```
import socket
import sys
from thread import *

HOST = ''	# Symbolic name meaning all available interfaces
PORT = 8888	# Arbitrary non-privileged port

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'

#Bind socket to local host and port
try:
	s.bind((HOST, PORT))
except socket.error , msg:
	print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
	sys.exit()
	
print 'Socket bind complete'

#Start listening on socket
s.listen(10)
print 'Socket now listening'

#Function for handling connections. This will be used to create threads
def clientthread(conn):
	#Sending message to connected client
	conn.send('Welcome to the server. Type something and hit enter\n') #send only takes string
	
	#infinite loop so that function do not terminate and thread do not end.
	while True:
		
		#Receiving from client
		data = conn.recv(1024)
		reply = 'OK...' + data
		if not data: 
			break
	
		conn.sendall(reply)
	
	#came out of loop
	conn.close()

#now keep talking with the client
while 1:
    #wait to accept a connection - blocking call
	conn, addr = s.accept()
	print 'Connected with ' + addr[0] + ':' + str(addr[1])
	
	#start new thread takes 1st argument as a function name to be run, second is the tuple of arguments to the function.
	start_new_thread(clientthread ,(conn,))

s.close()
```
运行上述服务端程序，然后像之前一样打开三个终端窗口并执行 telent 命令：

```
$ telnet localhost 8888
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
Welcome to the server. Type something and hit enter
hi
OK...hi
asd
OK...asd
cv
OK...cv
```
服务器端所在终端窗口输出信息如下：

```
$ python server.py
Socket created
Socket bind complete
Socket now listening
Connected with 127.0.0.1:60730
Connected with 127.0.0.1:60731
```


线程接管了连接并返回相应数据给客户端。

这便是我们所要介绍的服务器端编程。

## 结论
到这里为止，你已经学习了 Python 的 Socket 基本编程，你可自己动手编写一些例子来强化这些知识。

你可能会遇见一些问题：Bind failed. Error Code : 98 Message Address already in use，碰见这种问题只需要简单更改服务器端口即可。

