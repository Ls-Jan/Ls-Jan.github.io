@echo off
rem 打开资源管理器窗口，如果未指定路径那么将打开当前路径对应窗口
rem 用法：exp [filePath/folderPath]



@echo off
rem 参数判空：https://cloud.tencent.com/developer/ask/sof/32166
rem 文件/目录判断：http://www.bathome.net/thread-1047-1-1.html
rem 参数路径扩充：https://www.jianshu.com/p/87e360866130

if "%~1"=="" (
	explorer %cd%
) else (
	if exist %1/ (
		explorer %1
	) else (
		explorer %~dp1
	)
)




