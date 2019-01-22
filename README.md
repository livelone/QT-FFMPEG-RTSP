#                                  2018年7月8日更---程序使用说明
（1）首先将代码下载到本地，并解压；
（2）下载附件中的FFmpeg压缩包，解压后文件夹以FFmpeg命名，并和源码放入同一文件夹下；
（3）利用Qt creator Debug/release后，将FFmpeg文件夹下“dll”文件夹中的所有文件复制到含有.exe文件的文件夹（名称为Debug或release）下；
（4）再次点击Debug或release即可正常运行。

# FFmpeg-QT实现摄像头rtsp实时显示
1. 程序运行平台：（1）win10 64bit         （2）Qt Creator 4.3.1
2. 程序需要的库：（1）Qt 5.9.1(MSVC 2015,32bit) （2）FFmpeg 2.5.2
3. 程序流程图：
	程序流程图如图1所示，图中所示的主函数部分主要完成界面的构建、播放线程的建立以及参考坐标系的建立。图1展示了整个程序的运行流程。

![图1 程序流程图](https://git.oschina.net/uploads/images/2017/0905/143250_0efc807a_1477507.jpeg "视频播放流程图.jpg")
 
4. 程序界面
5. 主要功能：
	该界面主要实现四个功能：
（1）.读取摄像头视频流（rtsp），并实时显示到主界面上（注：存在0.7s左右的延时）；
（2）.将rtsp视频流经过FFmpeg解码后的YUV数据转化成RGB32数据，提取其中的R（红色）通道，并在界面中的小窗显示（如图2中的左上角部分）；
（3）.将水下机器人的横滚角反映在界面上（如图2中，中间部分的虚线“十字”为水平和竖直参考位置；实线“十字”为横滚运动后机器人相对参考位置的角度变化，图示为模拟横滚角为10度的情形）。
（4）.若程序掉电，再次上电后能够自动地建立连接。


