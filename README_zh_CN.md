# 思博操作系统（Symbol OS）

[繁體中文](README.md)

## 介绍

一个简单的 $IA-32e$ 操作系统，由思博开发团队提供支持。

## 支持致谢（按照字典序排列）

- CLydq（Symbol D.T.）
- CW (Feynco)
- DiannaoJun (Symbol D.T.)
- XYZ (XYZ)

## 使用

### 对于版本中的 vmdk 文件

由于目前系统甚至无法控制，所以我们仅为每个版本提供了 .vmdk 文件。

您可以下载该文件，然后按照下图创建虚拟机：

[![pkxS12V.png](https://s21.ax1x.com/2024/08/06/pkxS12V.png)](https://imgse.com/i/pkxS12V)

[![pkxSl80.png](https://s21.ax1x.com/2024/08/06/pkxSl80.png)](https://imgse.com/i/pkxSl80)

然后您可以启动虚拟机了。

### 对于源码

拿到源码后，请在 Linux 环境下编译。

~~由于工具环境差异，以及平台特性，不保证Windows下编译结果。~~

~~Windows 环境我自己测试的时候由于开发是在 Linux 下进行的，编译无法正常运行。~~

~~但是基于 WSL 是可以编译的。~~

编译环境需要您具备：

$NASM$（` sudo apt install nasm -y `）

$GCC$

在控制台切换到源码根目录，输入 `make` 即可编译得到镜像。

如果需要虚拟机镜像，可以输入 `make VM_IMAGE`。

其它用法请自行百度。
