
&emsp;&emsp;如题，在for中进行一些细化操作时发现SET变量一直不成功(尤其在读取文件时)
&emsp;&emsp;简单搜了下看到有个帖子([BAT求助与讨论-SET变量失效](http://www.bathome.net/thread-55988-1-1.html))是讨论这个问题的，然后有个老哥给出的解答，其中使用了使用``CALL``，这让我想起几天前看到的一个博客([批处理获取当前目录名称(非完整路径)](https://blog.csdn.net/wag2765/article/details/84695042))也是用了``CALL``，只能说``CALL``+``goto``这俩命令是真的伟大(不少疑难杂症要通过这个方式绕开)，同时也深深感叹Win的命令行工具写的跟坨苟石一样。

&emsp;&emsp;然后在处理“for命令读取文本时跳过空行的问题”时又看到了一个帖子([BAT求助与讨论-for命令不遗漏空行](http://www.bathome.net/thread-9174-1-1.html))(<font size=1>又是同个域名-<font color=#448888>批处理之家</font></font>)给出了答案，其中用的是``setlocal enabledelayedexpansion``和``endlocal``，至于这俩命令的作用我也不是很关心，我这里就主要以``CALL``+``goto``的搭配编写脚本。

<br>

***
# CMD/BAT脚本代码：


## 无效代码：

```bash
@echo off
rem 这个脚本无法成功SET变量，导致无法进一步操作
for /f "delims=" %%i in (%0) do (
	SET val=%%i
	echo.%val%
)
```

## 有效代码-【``CALL``+``goto``】：
```bash
@echo off
chcp 65001
for /f "delims=" %%i in (%0) do (
	call :DoSth "%%i"
)
goto :eof

:DoSth
rem 将头尾的引号去除以获取行数据
SET row=%1
SET row=%row:~1,-1%
echo %row%

```


## 有效代码-【``setlocal enabledelayedexpansion``+``endlocal``】：
```bash
@echo off
chcp 65001

for /f "delims=" %%i in ('findstr /n .* %0') do (
   set str=%%i
   setlocal enabledelayedexpansion
   set str=!str:*:=!
   echo,!str!
   endlocal
)
```

<br>

***

# 实际运用场景：

例如，要逐行读取文本文件(往往是各种参数配置或者是其他)并进行一些细化操作。

当然，实际上可以自己写一些C/C++代码编译成``exe程序``供实际生产环境使用，不少时候是这么做的，自己花个把小时造的小轮子远比在BAT原生命令里苦苦寻找可行性操作要来得实际，例如我以前写的一个可通过命令行进行键鼠控制的小轮子[(github)CPP_Mouse_Keyboard](https://github.com/Ls-Jan/CPP_Mouse_Keyboard)，这在原生命令行里是想都不敢想的操作(因为根本就没这样的命令)
CMD命令是真的太令人感到悲哀，它的功能如此受限以至于不时怀疑这玩意儿到底还能干些啥


***

# 参考：
- BAT求助与讨论-SET变量失效：[http://www.bathome.net/thread-55988-1-1.html](http://www.bathome.net/thread-55988-1-1.html)
- BAT求助与讨论-for命令不遗漏空行：[http://www.bathome.net/thread-9174-1-1.html](http://www.bathome.net/thread-9174-1-1.html)


