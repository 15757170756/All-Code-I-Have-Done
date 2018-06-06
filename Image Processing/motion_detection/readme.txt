测试方法：
解压
tar -zxvf motion_detection.tar.gz(不让上传.tar.gz格式.....o(╯□╰)o)

进入motion_detecion目录
cd motion_detecion

新建一个build文件夹
mkdir build

cd build
cmake ..
make
运行testUtil（注意改变main.c中的各个参数，测试视频可以放进data文件夹）
最后在build文件夹中有 outputFile.txt，里面记录了结果