from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *


class Test(QPushButton):
	def resizeEvent(self,event):
		print("resizeEvent:",event.size())
		self.resize(QSize(150,150))
	def resize(self,*size):
		print("resize:",size)
		super().resize(*size)
	def setGeometry(self,*rect):
		print("setGeometry:",rect)
		super().setGeometry(*rect)

if True:
	app = QApplication([])

	win=QWidget()
	t=Test("ABC")
	vbox=QVBoxLayout(win)
	vbox.addWidget(t)
	win.show()
	win.resize(300,300)

	app.exec_()
