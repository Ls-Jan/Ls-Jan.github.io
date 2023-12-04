@echo off
rem 启动本地服务器，实际调用命令为：npx http-server -o

@echo off

rem 参数判空：https://cloud.tencent.com/developer/ask/sof/32166
rem 参数路径扩充：https://www.jianshu.com/p/87e360866130
rem 获取目录名：https://blog.csdn.net/wag2765/article/details/84695042

if "%~1"=="" (
	call :GETDIR %cd%
	goto :eof
	:GETDIR
	SHIFT
	cd ..
	cmd /q /c "npx http-server -o %1" %~n0

	cd %~n0
	goto :eof
) else (
	cmd /q /c "npx http-server -o"
)
