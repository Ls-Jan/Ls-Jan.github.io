- ``QApplication.clipboard().mimeData()``：获取剪切板内容；
- ``QWidget.setAttribute(Qt.WA_Hover)``：启用鼠标悬停事件，启用后``QWidget.eventFilter``可接收``QEvent.HoverMove``类型事件；
- ``QApplication.instance().aboutToQuit``在应用程序退出前做好清理收尾工作，防白弹窗(程序异常/崩溃)；
- ``QApplication.focusWidget/focusWindow``获取当前活跃控件/窗口；

