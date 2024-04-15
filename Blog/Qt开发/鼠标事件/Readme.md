1. 鼠标事件只能向上传递而无法同级传递，换句话说就是事件可以向父级传递但无法传递给兄弟控件，无论控件是否发生重叠；
2. 通常情况下鼠标左键会被对应控件拦截处理，不会向父级传递；
3. 鼠标的悬浮、中键点击、右键点击在不重写对应的鼠标事件函数时默认是不会被拦截的，事件会向父级传递；

下面的样例代码效果很简单，可以看出鼠标在左键点击TEST按钮时作为父级的WIN无法接收到左键点击信息，但可以接收到鼠标的移动、鼠标中键点击和右击时的事件。

```py
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *

lst=list(filter(lambda key:key[0].isupper(),dir(QEvent)))
link={getattr(QEvent,i):i for i in lst}

class WIN(QPushButton):
	def __init__(self,*args):
		super().__init__(*args)
		self.__HM=0
		self.__MM=0
	def event(self,event):
		name=link[event.type()]
		flag=False
		if(name=='HoverMove'):
			self.__HM+=1
			flag=True
		elif(name=='MouseMove'):
			self.__MM+=1
			flag=True
		if(flag):
			print(f'\rHoverMove*{self.__HM} MouseMove*{self.__MM}',end='')
		else:
			if(self.__HM!=0 or self.__MM!=0):
				print()
			self.__HM=0
			self.__MM=0
			print(name)
		return super().event(event)

if True:
	app = QApplication([])

	win=WIN("WIN")
	win.show()
	win.resize(600,400)

	btn=QPushButton("TEST",win)
	btn.setGeometry(200,200,100,100)
	btn.show()

	app.exec_()
```


利用父级控件可以接收到子控件的鼠标移动等相关操作，可以写出一个容器控件专门处理有关鼠标的操作，例如鼠标悬浮显示提示文本(toolTip)、鼠标进入到子控件的哪块区域之类的


