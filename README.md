# 思博作業系統（Symbol OS）

[簡化字](README_zh_CN.md)

## 介紹

一個簡單的 $IA-32e$ 作業系統，由思博開發團隊提供支援。

## 支援致謝（按照字典序排列）

- $CLydq$（$Symbol D.T.$）
- $CW$ ($Feynco$)
- $DiannaoJun$ ($Symbol D.T.$)
- $XYZ$ ($XYZ$)

## 使用

### 對於版本中的 vmdk 檔案

由於目前系統甚至無法控制，所以我們僅為每個版本提供了 .vmdk 檔案。

您可以下載該檔案，然後按照下圖創建虛擬機器：

[![pkxS12V.png](https://s21.ax1x.com/2024/08/06/pkxS12V.png)](https://imgse.com/i/pkxS12V) 

[![pkxSl80.png](https://s21.ax1x.com/2024/08/06/pkxSl80.png)](https://imgse.com/i/pkxSl80) 

然後您可以啟動虛擬機器了。

### 對於源碼

拿到源碼後，請在 Linux 環境下編譯。

~~由於工具環境差異，以及平台特性，不保證在Windows系統下編譯結果~~

~~Windows 環境我自己測試的時候由於開發是在 Linux 下進行的，編譯無法正常運行。~~

~~但是基於使用WSL是可以編譯的。~~

編譯環境需要您具備：

$NASM$（` sudo apt install nasm -y `）

$GCC$

在控制台切換到源碼根目錄，鍵入 `make` 即可編譯得到鏡像。

如果需要虛擬機器鏡像，可以鍵入 `make VM_IMAGE`。

其它用法請自行谷歌。