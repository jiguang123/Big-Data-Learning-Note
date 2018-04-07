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
