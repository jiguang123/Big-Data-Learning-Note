# Linux 基础知识与常用命令
## 一. linux为何物
Linux 就是一个操作系统，就像你多少已经了解的 Windows（xp，7，8）和 Mac OS 。至于操作系统是什么，就不用过多解释了，如果你学习过前面的入门课程，应该会有个基本概念了，这里简单介绍一下操作系统在整个计算机系统中的角色。

![image](https://dn-anything-about-doc.qbox.me/linux_base/1-1.png/logoblackfont)

我们的 Linux 主要是系统调用和内核那两层。当然直观地看，我们使用的操作系统还包含一些在其上运行的应用程序，比如文本编辑器、浏览器、电子邮件等。

## 二. Linux 与 Windows 到底有哪些不同

### 1. 免费与收费

- 最新正版 Windows 10，需要付费购买；
- Linux 免费或少许费用。
### 2. 软件与支持

- Windows 平台：数量和质量的优势，不过大部分为收费软件；由微软官方提供重要支持和服务；
- Linux 平台：大都为开源自由软件，用户可以修改定制和再发布，由于基本免费没有资金支持，部分软件质量和体验欠缺；由全球所有的 Linux 开发者和自由软件社区提供支持。
### 3. 安全性

- Windows 平台：三天两头打补丁安装系统安全更新，还是会中病毒木马；
- Linux 平台：要说 Linux 没有安全问题，那当然是不可能的，这一点仁者见仁智者见智，相对来说肯定比 Windows 平台要更加安全，使用 Linux 你也不用装某杀毒、某毒霸。
### 4. 使用习惯

- Windows：普通用户基本都是纯图形界面下操作使用，依靠鼠标和键盘完成一切操作，用户上手容易，入门简单；
- Linux：兼具图形界面操作（需要使用带有桌面环境的发行版）和完全的命令行操作，可以只用键盘完成一切操作，新手入门较困难，需要一些学习和指导（这正是我们要做的事情），一旦熟练之后效率极高。
### 5. 可定制性

- Windows：这些年之前算是全封闭的，系统可定制性很差；
- Linux：你想怎么做就怎么做，Windows 能做到得它都能，Windows 做不到的，它也能。
### 6. 应用范畴

或许你之前不知道 Linux ，要知道，你之前在 Windows 使用百度、谷歌，上淘宝，聊 QQ 时，支撑这些软件和服务的，是后台成千上万的 Linux 服务器主机，它们时时刻刻都在忙碌地进行着数据处理和运算，可以说世界上大部分软件和服务都是运行在 Linux 之上的。

### 7. Windows 没有的

- 稳定的系统
- 安全性和漏洞的快速修补
- 多用户
- 用户和用户组的规划
- 相对较少的系统资源占用
- 可定制裁剪，移植到嵌入式平台（如安卓设备）
- 可选择的多种图形用户界面（如 GNOME，KDE）

### 8. Linux 没有的

- 特定的支持厂商
- 足够的游戏娱乐支持度
- 足够的专业软件支持度


## 三、linux终端
### 3.1 终端的概念

通常我们在使用 Linux 时，并不是直接与系统打交道，而是通过一个叫做 Shell 的中间程序来完成的，在图形界面下为了实现让我们在一个窗口中完成用户输入和显示输出，Linux 系统还提供了一个叫做终端模拟器的程序（Terminal），下面是几个比较常见的终端模拟器： gnome-terminal，kconsole，xterm，rxvt，kvt，nxterm 和 eterm 。目前我们的实验中的终端程序是 xfce 桌面环境自带的 xfce-terminal 。不过要注意的是这里所说的终端（Terminal）和控制台（Console）是有区别的。

![image](https://dn-anything-about-doc.qbox.me/linux_base/2-2.png/logoblackfont)

### 3.2 Shell

通常在图形界面中对实际体验带来差异的不是上述的不同发行版的各种终端模拟器，而是这个 Shell（壳）。有壳就有核，这里的核就是指 UNIX/Linux 内核，Shell 是指“提供给使用者使用界面”的软件（命令解析器），类似于 DOS 下的 command（命令行）和后来的 cmd.exe 。普通意义上的 Shell 就是可以接受用户输入命令的程序。它之所以被称作 Shell 是因为它隐藏了操作系统底层的细节。同样的 UNIX/Linux 下的图形用户界面 GNOME 和 KDE，有时也被叫做“虚拟 shell”或“图形 shell”。

UNIX/Linux 操作系统下的 Shell 既是用户交互的界面，也是控制系统的脚本语言。当然这一点也有别于 Windows 下的命令行，虽然该命令行也提供了很简单的控制语句。在 Windows 操作系统下，有些用户从来都不会直接使用 Shell，然而在 UNIX 系列操作系统下，Shell 仍然是控制系统启动、X11 启动和很多其它实用工具的脚本解释程序。

在 UNIX/Linux 中比较流行的常见的 Shell 有 bash、zsh、ksh、csh 等等，Ubuntu 终端默认使用的是 bash，默认的桌面环境是 GNOME 或者 Unity（基于 GNOME），但我们的环境中使用的分别是 zsh 和 xfce。

### 3.3 命令行操作体验
在linux中，最最重要的就是命令，常用命令如下：

```
#创建一个名为文件，touch是一个命令
touch file 

#进入一个目录，cd是一个命令
cd /etc/

#查看当前所在目录
pwd

#进入上一级目录
cd ..

#进入你的 home 目录：
cd ~ 

# 绝对路径
$ cd /usr/local/bin
# 相对路径
$ cd ../../usr/local/bin

#创建名为 test 的空白文件
touch test

#创建名为“ mydir ”的空目录：
mkdir mydir

#使用 -p 参数，同时创建父目录（如果不存在该父目录），如下我们同时创建一个多级目录（这在安装软件、配置安装路径时非常有用）：
mkdir -p father/son/grandson

#将之前创建的“ test ”文件复制到“ /home/shiyanlou/father/son/grandson ”目录中：
$ cp test father/son/grandson

#使用 rm（remove files or directories）命令删除一个文件：
rm test

#使用 mv（move or rename files）命令移动文件（剪切）。将文件“ file1 ”移动到 Documents目录：mv 源目录文件 目的目录：
$ mkdir Documents
$ mv file1 Documents

#将文件“ file1 ”重命名为“ myfile ”：mv 旧的文件名 新的文件名：
$ mv file1 myfile

#创建一个 python 脚本文件：
$ gedit hello_shell.py

#将 shiyanlou.zip 解压到当前目录：
$ unzip shiyanlou.zip

#使用 df 命令查看磁盘的容量
$ df

#比如我们想安装一个软件，名字叫做w3m(w3m是一个命令行的简易网页浏览器)，那么输入如下命令：
$ sudo apt-get install w3m

# 更新软件源
$ sudo apt-get update

# 升级没有依赖问题的软件包
$ sudo apt-get upgrade

# 升级并解决依赖关系
$ sudo apt-get dist-upgrade

#卸载软件
sudo apt-get remove w3m



```
#### 其他一些常用快捷键
- Tab键   来进行命令补全
- Ctrl+c  来强行终止当前程序（你可以放心它并不会使终端退出）。
- Ctrl+d	键盘输入结束或退出终端
- Ctrl+s	暂停当前程序，暂停后按下任意键恢复运行
- Ctrl+z	将当前程序放到后台运行，恢复到前台为命令fg
- Ctrl+a	将光标移至输入行头，相当于Home键
- Ctrl+e	将光标移至输入行末，相当于End键
- Ctrl+k	删除从光标所在位置到行末
- Alt+Backspace	向前删除一个单词
- Shift+PgUp	将终端显示向上滚动
- Shift+PgDn	将终端显示向下滚动

#### Shell 常用通配符：
通配符是一种特殊语句，主要有星号（*）和问号（?），用来对字符串进行模糊匹配（比如文件名、参数名）。当查找文件夹时，可以使用它来代替一个或多个真正字符；当不知道真正字符或者懒得输入完整名字时，常常使用通配符代替一个或多个真正字符。
- ?	        匹配任意一个字符
- [list]	    匹配 list 中的任意单一字符
- [!list]	    匹配 除list 中的任意单一字符以外的字符
- [c1-c2]	    匹配 c1-c2 中的任意单一字符 如：[0-9] [a-z]
- {string1,string2,...}	匹配 string1 或 string2 (或更多)其一字符串
- {c1..c2}	匹配 c1-c2 中全部字符 如{1..10}


#### 解压缩常用命令：

- zip：
>  - 打包 ：zip something.zip something （目录请加 -r 参数）
>  - 解包：unzip something
>  - 指定路径：-d 参数
- tar：
> - 打包：tar -zcvf something.tar something
> - 解包：tar -zxvf something.tar
> - 指定路径：-C 参数



#### apt-get包含的常用工具
apt-get 是用于处理 apt包的公用程序集，我们可以用它来在线安装、卸载和升级软件包等

- install	其后加上软件包名，用于安装一个软件包
- update	从软件源镜像服务器上下载/更新用于更新本地软件源的软件包列表
- upgrade	升级本地可更新的全部软件包，但存在依赖问题时将不会升级，通常会在更新之前执行一次update
- dist-upgrade	解决依赖关系并升级(存在一定危险性)
- remove	移除已安装的软件包，包括与被移除软件包有依赖关系的软件包，但不包含软件包的配置文件
- autoremove	移除之前被其他软件包依赖，但现在不再被使用的软件包
- purge	与remove相同，但会完全移除软件包，包含其配置文件
- clean	移除下载到本地的已经安装的软件包，默认保存在/var/cache/apt/archives/
- autoclean	移除已安装的软件的旧版本软件包


## 四 Linux进程之初步了解
简而言之,一个程序至少有一个进程,一个进程至少有一个线程。线程的划分尺度小于进程，使得多线程程序的并发性高。另外，进程在执行过程中拥有独立的内存单元，而多个线程共享内存，从而极大地提高了程序的运行效率。就如下图所示：

![image](https://dn-simplecloud.qbox.me/1135081469062947147-wm)


