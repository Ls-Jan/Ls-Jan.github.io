
from PyQt5.QtWidgets import QApplication,QWidget,QPushButton
from PyQt5.QtCore import QPropertyAnimation,QRect,QTimer

if True:
	app = QApplication([])

	wid=QWidget()
	btn=QPushButton("ABC",wid)
	pa=QPropertyAnimation(btn,'geometry'.encode())
	pa.setDuration(1000)
	def Func():
		pa.stop()
		if(btn.text()=='上'):
			rect=QRect(200,200,100,100)
			btn.setText('下')
		else:
			rect=QRect(200,50,50,50)
			btn.setText('上')
		pa.setEndValue(rect)
		pa.start()
	Func()
	btn.clicked.connect(Func)
	btn.show()
	wid.show()
	wid.resize(400,400)
	app.exec_()


