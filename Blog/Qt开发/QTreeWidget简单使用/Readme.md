
怎么说呢，Qt的树就是一个典型的“隐式根节点”，下面将简称为“隐根”。
因此与其说它是“树”控件，不如说是“森林”更为合适，后面会将直接追加到``QTreeWidget``的节点直接称为“根节点”。

使用森林直接导致了一个问题，那就是各种操作都要多做一步的判断以及好几步的冗余操作，例如：
- 在给``QTreeWidget``追加新节点时有两种方法，一个是使用``QTreeWidget.addTopLevelItem``将节点追加到隐根下，一个是使用``QTreeWidgetItem.addChild``将节点追加到指定节点下，如果我能拿到那个隐根节点的话那我岂不是就没必要调用``QTreeWidget``的函数了？
- 在树遍历的过程中由于无法获取到隐根，在遍历操作执行到根节点时会出现好几个问题，首先是``QTreeWidgetItem.parent()``返回的是空值，其次是获取根节点的兄弟节点时需要调用``QTreeWidget.itemBelow/itemAbove``，如果，如果我说，我能获取到隐根的话，那我岂不是可以直接调用``QTreeWidgetItem.child(int)``获取根节点的兄弟节点？


<br>

反正个人觉得Qt的树模型的设计是真糟糕，它的树不是树，是森林，``QTreeWidget``该改名为“QForestWidget”，关于节点的操作都会或多或少的与树控件出现了耦合(而且明明是可以摆脱这种不必要的耦合的)，或许Qt是有什么高见才采用的这个模型？


<br>
<br>


***

- ``QTreeWidget.setColumnCount``：设置列数；
- ``QTreeWidget.setHeaderLabels``：设置表头；
- ``QTreeWidget.addTopLevelItem(QTreeWidgetItem)``：追加根节点；
- ``QTreeWidget.insertTopLevelItem(int,QTreeWidgetItem)``：插入根节点；
- ``QTreeWidget.topLevelItemCount``：获取根节点数量；
- ``QTreeWidget.setItemWidget(QTreeWidgetItem,int,QWidget)``：设置指定节点的第i列的单元格为控件(可以传空以移除这个单元格控件)
- ``QTreeWidget.itemAbove``：获取根节点的上一个兄弟节点
- ``QTreeWidget.itemBelow``：获取根节点的下一个兄弟节点

<br>

- ``QTreeWidgetItem.addChild``：追加子节点
- ``QTreeWidgetItem.insertChild``：插入子节点
- ``QTreeWidgetItem.child(int)``：根据位置获取子节点
- ``QTreeWidgetItem.childCount``：获取子节点个数
- ``QTreeWidgetItem.indexOfChild(QTreeWidgetItem)``：获取子节点的位置



# 简单的示例：

```py
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *

if True:
	app=QApplication([])
	tree=QTreeWidget()

	tree.setHeaderLabels(["R1","R2","R3","R4","R5"])
	itemA=QTreeWidgetItem(['AAA','aaa'])
	itemB=QTreeWidgetItem(['BBB','bbb'])
	itemC=QTreeWidgetItem(['CCC','ccc'])
	itemA.addChild(itemB)#在节点A中添加子节点B
	tree.addTopLevelItem(itemA)#添加根节点A
	tree.addTopLevelItem(itemC)#添加根节点C
	tree.setItemWidget(itemA,1,QPushButton("BTN"))
	tree.show()

	exit(app.exec())
```

![preview-1](./Preview-1.png)







<br>
<br>

# 参考：
- [QTreeWidget详细使用方法：往单元格插入控件、处理点击事件](https://blog.csdn.net/weixin_43961107/article/details/108872928)

