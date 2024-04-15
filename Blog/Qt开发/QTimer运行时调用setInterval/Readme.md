字面意思，就是在QTimer正在跑的时候，调用``setInterval``的效果。

```py
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

if True:
	app=QApplication([])
	t1=QTimer()
	t1.timeout.connect(lambda:print("!!!"))
	t1.setInterval(5000)
	t1.start()
	t2=QTimer()
	t2.timeout.connect(lambda:print("SET") or t1.setInterval(500))
	t2.setInterval(500)
	t2.setSingleShot(True)
	t2.start()
	app.exec()
```

上面代码运行结果表明``setInterval``是即时生效的，换句话说就是``setInterval``等价于“停止计时器”→“设置interval”→“启动计时器”，因此调用``setInterval``时不必手动停下启动计时器。



