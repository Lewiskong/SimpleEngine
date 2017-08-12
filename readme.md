# C++/OpenGL 梦幻西游

个人学习练手项目

### Mac编译指南

1. 安装好git和cmake,然后敲命令
		
		git clone --recursive https://github.com/oceancx/SimpleEngine

2. 编译之前将Environment.h中WORK_DIR宏设置为SimpleEngine的路径，例如：
		
		#define WORK_DIR "/Users/oceancx/SimpleEngine"

3. 下载资源压缩包：[百度云盘](https://pan.baidu.com/s/1o7Gn0t8)，直接在SimpleEngine/下解压即可,你会看到Data/文件夹被创建

4. 然后：

		cd SimpleEngine/
		mkdir build
		cd build
		cmake ..
		make -j8
		./SimpleEngine


### Windows编译

用CMake生成VisualStudio项目文件，打开VS编译即可，同样需要设置Environment.h的WORK_DIR

### TODO

在线聊天~ （progress：0.01%）


### 截图

<img src="https://github.com/oceancx/SimpleEngine/blob/develop/ScreenShots/screenshot1.png" width="50%" height="50%">

<img src="https://github.com/oceancx/SimpleEngine/blob/develop/ScreenShots/screenshot2.png" width="50%" height="50%">



# C++/OpenGL Project Intro

 Fantasy Westward Journey, individual learning and training project.

### Mac build


1. install cmake and git,then:
		
		git clone --recursive https://github.com/oceancx/SimpleEngine

2. before build,in file "Environment.h",set WORK_DIR as SimpleEngine's path，for instance：

		#define WORK_DIR "/Users/oceancx/SimpleEngine"

3. download resource zip file ：[baidu pan](https://pan.baidu.com/s/1o7Gn0t8) , and extract to SimpleEngine/ , you will see a new dir Data/ was created.

4. then,happy to build:

		cd SimpleEngine/
		mkdir build
		cd build
		cmake ..
		make -j8
		./SimpleEngine

### Windows Build

Use CMake to generate Visual Studio Project file, Open it by VS and build.

### ScreenShots

<img src="https://github.com/oceancx/SimpleEngine/blob/develop/ScreenShots/screenshot1.png" width="50%" height="50%">

<img src="https://github.com/oceancx/SimpleEngine/blob/develop/ScreenShots/screenshot2.png" width="50%" height="50%">
