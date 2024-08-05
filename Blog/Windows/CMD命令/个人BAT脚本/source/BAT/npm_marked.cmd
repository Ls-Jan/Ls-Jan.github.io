@echo off
rem 安装与Markdown渲染相关的npm包


@echo off
rem 使用 MarkedJS 渲染 Markdown：https://juejin.cn/post/7273685848604885007
rem lodash-es用于输入防抖
set list=marked   @types/marked   marked-highlight   highlight.js   lodash-es
for %%a in (%list%) do ( 
	echo npm install %%a
	cmd /q /c "npm install %1" %%a
)


