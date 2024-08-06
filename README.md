# 思博操作系統（$Symbol$ $OS$）

[ 簡化字 ](README_zh_CN.md)

## 介紹

一個簡單的 $IA-32e$ 操作系統，由思博開發團隊提供支持。

## 支持致謝（按照字典序排列）

- $CLydq$（$Symbol D.T.$）
- $CW$（$Feynco$）
- $DiannaoJun$ （$Symbol D.T.$）
- $XYZ$（$XYZ$）

## 使用

### 對於版本中的 vmdk 文件

由於目前系統甚至無法控制，所以我們僅為每個版本提供了 .vmdk 文件。

您可以下載該文件，然後按照下圖創建虛擬機：

[![pkxS12V.png](https://s21.ax1x.com/2024/08/06/pkxS12V.png)](https://imgse.com/i/pkxS12V) 

[![pkxSl80.png](https://s21.ax1x.com/2024/08/06/pkxSl80.png)](https://imgse.com/i/pkxSl80) 

然後您可以啟動虛擬機了。

### 對於源碼

拿到源碼後，請在 Linux 環境下編譯。

~~由於環境差異，以及平台特性，不保證 Windows 下能正常編譯。~~

~~我測試的時候，Windows 環境無法正常編譯。~~

~~但是 WSL 環境下是可以正常編譯的。~~

編譯環境需要您具備：

$NASM$（可通過 `sudo apt install nasm -y` 來安裝）

$GCC$（可通過 `sudo apt install build-essential` 來安裝）

如果您遇到了一點 ~~小~~ Bug，您可以尝试以下命令：

`sudo apt update`

更新您的 $apt$，然後重試。

在控制台切換到源碼根目錄，輸入 `make` 即可編譯得到鏡像。

如果需要虛擬機鏡像，可以輸入 `make VM_IMAGE`。

其它用法請自行百度。