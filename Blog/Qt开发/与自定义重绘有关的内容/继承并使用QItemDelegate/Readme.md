这里的样式开发，不比某个叫``QStyle``的玩意儿简单明了？没有那么多杂七杂八意义不明的函数。

在实现单元格重绘时，绕不开的函数是``QModelIndex.data(Qt.ItemDataRole)``，它用于获取该单元格中存着的数据，
其中，可以使用``QStandardItem.setData(QVariant,Qt.ItemDataRole)``来设置用户独有的单元格数据。


<br>

##### 通常情况下需要继承重写的函数有：
- ``sizeHint``：用于管理单元格大小；
- ``paint``：单元格数据绘制；

##### 选择性重写的函数(肯定是不止这么点的，但``QItemDelegate``接触得少就暂时只有这些内容)：
- ``editorEvent``：处理单元格交互事件，包括但不限于点击单元格等；
- ``drawCheck``：绘制复选框；



<br>
<br>

### 更详细的参考内容：
[Qt.ItemDateRole枚举值](https://doc.qt.io/qt-6/qt.html#ItemDataRole-enum)
[QStandardItem.setData](https://doc.qt.io/qt-6/qstandarditem.html#setData)
[QStyledItemDelegate基本使用：单元格数据渲染与编辑](https://blog.csdn.net/gongjianbo1992/article/details/108687172)

