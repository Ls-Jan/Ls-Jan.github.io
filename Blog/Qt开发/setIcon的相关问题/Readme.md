
- 是可以通过``QStandardItem.setIcon``的方式来实现单元格的加载动画效果，但不太优雅，在设置单元格数据的过程中(包括调用``setIcon``)需要在适当的位置调用``QStandardItemModel.blockSignals``以及``QListView.viewport().update()``，还有就是，调整好行高，调行高的偷懒做法就是使用样式表；
- 对成千上万个单元格设置同个icon又或是不同icon但同数据(即``QIcon(pix)``，其中pix是同一张图)并不会造成内存问题，哪怕每个icon大的跟个图片一样；
- 你无法对icon存着的pixmap进行修改，或者说就是无法获取icon的pixmap实例，或者可以理解为QIcon对象的内部图片数据是只读的；


```py
#通过setIcon的方式是可以实现加载效果；
#只不过通常做法是继承绘制代理QStyledItemDelegate并完成相关的函数实现，然后对对应列表控件调用QListView.setItemDelegate进行代理设置
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PIL import Image

from PyQt5.QtWidgets import QAbstractItemView

def GetQItemViewShowingIndices(view:QAbstractItemView,extend=0):
	'''
		字面意思，就是获取QListView列表中，当前显示行的起始结束索引。
		extend对上下限额外修正，例如当前显示的是(3,12)，指定extend=5的话将返回(0,17)
	'''
	# 参考：https://cloud.tencent.com/developer/ask/sof/779490
	minRow=0
	maxRow=view.model().rowCount()-1
	rect = view.viewport().contentsRect()
	top = view.indexAt(rect.topLeft())
	bottom = view.indexAt(rect.bottomLeft())
	top=top.row() if top.isValid() else minRow
	bottom=bottom.row() if bottom.isValid() else maxRow
	top=max(minRow,top-extend)
	bottom=min(maxRow,bottom+extend)
	return top,bottom

def LoadGIF(path:str):
	'''
		读取GIF并返回QPixmap列表
	'''
	im = Image.open(path)
	im.load()#调用该函数后info中的信息才会有效(这是试出来的)
	lst=[]
	for i in range(im.n_frames):
		im.seek(i)
		lst.append(im.convert("RGBA").toqpixmap())
	return lst

if True:
	app=QApplication([])

	lvModel=QStandardItemModel()
	lv=QListView()
	lv.setModel(lvModel)
	lv.setIconSize(QSize(64,64))
	for i in range(10000):#此时如果将该值设置的更大，就会更卡
		item=QStandardItem(str(i))
		item.setCheckable(True)
		item.setEditable(False)
		item.setCheckState(Qt.CheckState.Checked)
		lvModel.insertRow(i,item)
	lv.show()
	
	lst=[QIcon(pix) for pix in LoadGIF('加载动画-1.gif')]
	index=0
	def SetItemsIcon():
		global index
		index=(index+1)%len(lst)
		icon=lst[index]
		indices=GetQItemViewShowingIndices(lv)
		lvModel.blockSignals(True)#哪怕block了也没用
		for i in range(indices[0],indices[1]+1):
			lvModel.item(i).setIcon(icon)
		lvModel.blockSignals(False)
	timer=QTimer()
	timer.setInterval(50)
	timer.timeout.connect(lambda:SetItemsIcon())#打开任务管理器可以看到CPU占用率很高，正常情况下应该维持在1%以内
	timer.start()

	app.exec()
```

```py
#对大量单元格设置同icon不会造成内存问题，但也无法对icon中的图片进行修改
from PyQt5.QtCore import QTimerEvent
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

if True:
	app=QApplication([])

	lvModel=QStandardItemModel()
	lv=QListView()
	lv.setModel(lvModel)
	pix=QPixmap('Test.png')
	ptr=QPainter(pix)
	ptr.fillRect(0,0,200,200,QColor(255,0,0))
	ptr.end()
	lv.setIconSize(QSize(256,256))
	for i in range(1000):
		item=QStandardItem(str(i))
		item.setCheckable(True)
		item.setEditable(False)
		item.setCheckState(Qt.CheckState.Checked)
		item.setIcon(QIcon(pix))
		lvModel.insertRow(i,item)
		icon=QIcon(pix)
	lv.show()
	ptr=QPainter(pix)#对pix进行的修改不会影响到已经生效的QIcon对象
	ptr.fillRect(0,0,100,100,QColor(0,255,0))
	ptr.end()

	app.exec()
```

