
- 在列表数据量很大的情况下，频繁周期更新其中的部分单元格数据时，不屏蔽信号将会出现极其严重的卡顿问题；
- 要屏蔽信号需要调用``QStandardItemModel.blockSignals``的，调用``QListView.blockSignals``不会生效；
- 更新控件需要调用``QListView.viewport().update()``，调用``QListView.update()``不会生效；

```py
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

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

if True:
	app=QApplication([])

	lvModel=QStandardItemModel()
	lv=QListView()
	lv.setModel(lvModel)
	lv.setIconSize(QSize(64,64))
	# lv.setIconSize(QSize(256,256))		
	for i in range(10000):
		item=QStandardItem(str(i))
		item.setCheckable(True)
		item.setEditable(False)
		item.setCheckState(Qt.CheckState.Checked)
		lvModel.insertRow(i,item)
	lv.show()
	
	num=0
	def SetItemsIcon_WithoutBlock():
		global num
		num+=1
		indices=GetQItemViewShowingIndices(lv)
		for i in range(indices[0],indices[1]+1):
			lvModel.item(i).setText(str(i+num))
	def SetItemsIcon_WithBlock():
		global num
		num+=1
		lvModel.blockSignals(True)#屏蔽这个信号才行
		indices=GetQItemViewShowingIndices(lv)
		for i in range(indices[0],indices[1]+1):
			lvModel.item(i).setText(str(i+num))
		lvModel.blockSignals(False)
		# lv.update()#该函数不生效
		lv.viewport().update()

	timer=QTimer()
	timer.setInterval(50)
	# timer.timeout.connect(lambda:SetItemsIcon_WithoutBlock())#打开任务管理器可以看到CPU占用率很高，正常情况下应该维持在1%以内
	timer.timeout.connect(lambda:SetItemsIcon_WithBlock())#使用屏蔽信号的方式可以优化CPU占用
	timer.start()

	app.exec()
```

