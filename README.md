# ITE87_GPIO_TEST_LINUX

Linux下ITE87芯片GPIO的简单测试工具



#### 开发环境

Ubuntu：18.04LTS  

Kernel：5.0.6

IDE：Qt5.7.0

Chip：ITE8786E-I



#### 软件截图

![GPIO](./app/img/GPIO.png)

#### 使用方法

因为程序是使用iopl接口直接访问硬件地址，所以需要使用root权限运行

`sudo ./app/GPIO-TEST.sh`运行程序

