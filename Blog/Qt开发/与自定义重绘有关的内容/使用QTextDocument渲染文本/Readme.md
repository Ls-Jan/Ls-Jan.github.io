
使用``QTextDocument``可以对一些文本内容进行预渲染，同时获取渲染结果以及渲染内容的大小。

具体用法则是，前面忘了，中间忘了，后面忘了，等哪天再用上的时候补充。

<br>
<br>

简单附上一些关键函数：
- ``QTextDocument.setHtml``：设置富文本；
- ``QTextDocument.setPlainText``：设置纯文本；
- ``QTextDocument.drawContents``：绘制渲染结果；
- ``QTextDocument.size``：获取渲染大小；
- ``QTextDocument.paintText``：获取纯文本，可借此进行关键词搜索；

<br>

- ``QTextCursor(QTextDocument)``：创建文本光标，用于精细操作；
- ``QTextCursor.setPosition``：设置光标位置；
- ``QTextCursor.movePosition``：移动光标位置，可在移动的过程中选中文本；
- ``QTextCursor.insertText``：在光标位置插入文本(可将选中的文本覆盖掉)；

<br>

- ``QTextEdit.setTextCursor``：QTextEdit设置文本光标(包括文本选中状态);




