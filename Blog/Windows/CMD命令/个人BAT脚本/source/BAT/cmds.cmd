@echo off
rem 罗列本脚本所在路径下所有脚本文件(*.cmd)并输出脚本文件中的头部注释内容

@echo off
rem 解决for语句中set变量失效的问题：https://blog.csdn.net/weixin_44733774/article/details/134774369
rem 逐行获取文件内容：https://www.cnblogs.com/gered/p/10682741.html#autoid-2-0-0
rem 字符串截取+替换：https://zhuanlan.zhihu.com/p/421422830
rem for命令不遗漏空行：http://www.bathome.net/thread-9174-1-1.html
rem SET变量判空：https://blog.csdn.net/weixin_44733774/article/details/134774852
rem 获取目录下文件：https://blog.csdn.net/xieyunc/article/details/80471107


rem flag等效于循环语句的break。flag为0时后面的文本不作处理
rem 至多接受1次@echo
SET flag=2
SET path_old=%cd%
cd /d %~dp0
for /f "delims=" %%i in ('dir /b') do ( 
	if "%%~xi"==".cmd" (
		echo.----------------------------------------------------------------------
		echo.%%i
		for /f "delims=" %%i in ('findstr /n .* %%i') do (call :ReadRow "%%i")
	)
	if "%%~xi"==".bat" (
		echo.----------------------------------------------------------------------
		echo.%%i
		for /f "delims=" %%i in ('findstr /n .* %%i') do (call :ReadRow "%%i")
	)
	SET flag=2
)
cd /d %path_old%
goto :eof

:ReadRow
if %flag%==0 (goto :eof)
SET row=%1
SET row=%row:~1,-1%
SET row=%row:*:=%
call :EmptyTest %row%
goto :eof

:EmptyTest
if "%1"=="" ( 
	rem echo. 
	goto :eof
) 

rem 只能说，挺无奈的，到哪都得塞上双引号然后再取下来，那些开发者就不能多给SET命令多一个控制参数吗？真的折磨
if "%row:~,2%"=="::" (
	SET row="%row:~2%"
	goto :PrintRow
)
if "%row:~,4%"=="rem " (
	SET row="%row:~4%"
	goto :PrintRow
)
if "%row:~,5%"=="@echo" (
	SET /A flag=flag-1
	goto :eof
)
SET /A flag=0
goto :eof

:PrintRow
echo %row:~1,-1%

