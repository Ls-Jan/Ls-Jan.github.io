## 废弃原因：
本质上使用``sys.path``和``exec``实现相对路径导入，因此有如下问题：

- 由于是使用``exec``这种动态方式进行模块导入，使用pyinstaller将项目打包成exe时并不会将相关模块打包进去，也就是运行exe程序时将提示模块不存在


<br>
<br>
<br>


***

# RelativeImport：

```python
__version__='1.1.0'
__author__='Ls_Jan'


import os
import sys
import inspect

def RelativeImport(module,*args):#模块导入
	'''
		module为模块所在路径(模块名不需要.py后缀)，支持相对路径：
			导入上一级名为M的模块，那么module='../M'
			导入目录A下的名为M的模块，那么module='A/M'
		args为从module中导入的变量名：
			如果args为空，那么仅导入模块module
			如果args不为空，那么将导入模块module中指定的args

		例子：
			RelativeImport('M')：导入模块M。【等同import M】
			RelativeImport('M','info','func')：导入模块M中的info和func。【等同于from M import info,func】
			RelativeImport('M','*')：导入模块M中所有内容。【等同于from M import *】
			RelativeImport('../M')：导入上级目录中的模块M。
			RelativeImport('A/M','info')：导入A目录下的模块M中名为info的变量。

		特别的，支持“重命名”行为：
			RelativeImport(('M','mmm'))：导入模块M并命名为mmm。【等同import M as mmm】
			RelativeImport('M',('info','i'),('func','f'))：导入模块M中的info和func并分别命名为i和f。【等同from M import info as i,func as f】

		补充：
			虽然名字是RelativeImport(相对导入)，但实际上它也能正常导入其他模块，例如RelativeImport(('numpy','np'))等效于import numpy as np
	'''

	info=inspect.stack()[1]#调用者的上下文信息
	frame=info.frame
	fileName=info.filename
	varG=frame.f_globals

	if(type(module)!=tuple):
		module=(module,None)
	sourcePath=os.path.dirname(fileName)#调用该函数的文件所在的路径(绝对路径)
	relativePath,module_exec=os.path.split(module[0])#模块所在目录(相对路径) + 模块名
	modulePath=os.path.join(sourcePath,relativePath)#模块所在路径(绝对路径)

	sys.path.append(modulePath)#将路径临时加入到系统列表中
	if(args):
		lst=[]
		for item in args:
			if(type(item)==tuple):
				lst.append(f'{item[0]} as {item[1]}')
			else:
				lst.append(f'{item}')
		exec(f'from {module_exec} import {",".join(lst)}',varG)
	else:
		if(module[1]):
			exec(f'import {module_exec} as {module[1]}',varG)
		else:
			exec(f'import {module_exec}',varG)
	sys.path.pop()#移除临时加入的路径

```



<br>


***

# 补充：
- 造了个小轮子原本打算发布到pypi上，但发现注册不了(然后查了下才发现原来pip有漏洞被黑客恶意上传病毒啥的才禁止新用户注册)，遂移步至github。
- 下载轮子，安装轮子，~~成为轮子~~ ：[RelativeImport-1.1-py3-none-any.whl](https://github.com/Ls-Jan/Python_RelativeImport/releases/download/v1.1/RelativeImport-1.1-py3-none-any.whl)，``pip install RelativeImport-1.1-py3-none-any.whl``，建议去github查看详细操作(毕竟如果github都上不去那轮子更不可能下载的了。
- github项目链接：[https://github.com/Ls-Jan/Python_RelativeImport/tree/main](https://github.com/Ls-Jan/Python_RelativeImport/tree/main)

<br>



***

# 参考：
- 【Python】获取调用者信息： [https://blog.csdn.net/weixin_44733774/article/details/134665412](https://blog.csdn.net/weixin_44733774/article/details/134665412)
- python之PypI打包whl文件：[https://www.cnblogs.com/yuhaohao/p/13099552.html](https://www.cnblogs.com/yuhaohao/p/13099552.html)
- pip安装本地包：[https://blog.csdn.net/enter89/article/details/90291667](https://blog.csdn.net/enter89/article/details/90291667)
