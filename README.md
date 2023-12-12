# 学习51单片机

本人学习51单片机的示例代码，使用的是清翔的QX-MCS 51单片机开发板V3.5。

## 准备

1. 安装sdcc：

```shell
sudo apt install sdcc
```

2. 安装stcgal：

```shell
pip3 install stcgal
```

3. 将学习板连接电脑USB接口，修改权限：

```shell
sudo chmod a+rw /dev/ttyCH341USB0
```

## 使用

在各个示例目录下运行`make`，或者使用`make -C <DEMO_DIR>`。
