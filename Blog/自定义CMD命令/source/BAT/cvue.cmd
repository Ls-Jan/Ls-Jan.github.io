@echo off
rem 在本文件夹下创建并构建vue项目




@echo off
rem 参数判空：https://cloud.tencent.com/developer/ask/sof/32166
rem 参数路径扩充：https://www.jianshu.com/p/87e360866130
rem 获取目录名：https://blog.csdn.net/wag2765/article/details/84695042


call :GETDIR %cd%
goto :eof
:GETDIR
SHIFT
cd ..
cmd /q /c "npm create vue@latest %1" %~n0
cd %~n0
cmd /q /c "npm install"






