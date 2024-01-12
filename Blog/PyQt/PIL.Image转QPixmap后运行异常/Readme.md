# 问题场景：

<br>

&emsp;&emsp;PIL.Image图片，直接调用``PIL.Image.toqpixmap()``转成QPixmap后，不会立即报错，
&emsp;&emsp;但后续使用该QPixmap时(包括但不仅限于使用``QLabel.setPximap()``、``QPixmap.save()``)将立即出现异常

![运行异常弹窗](./pict/1.png)

&emsp;&emsp;不知道是我关键词不对，还是只有我一个人碰到这样的问题，亦或是bing搜索引擎拉胯，我愣是没搜到相关回答，就有点搞笑。

<br>

***
# 解决方法：

&emsp;&emsp;在进行几次随意的尝试后，倒是找到了个不像是根本原因的原因，那就是转换异常的PIL.Image图片往往是RGB格式的，应该是转图片的那个函数有问题，但我也懒得再深究原因。早上试过``py -m pip install --upgrade PIL ``更新了PIL模块，不顶用，而且新PIL还有警告说明2023年7月1日起不兼容PyQt5，离谱。
&emsp;&emsp;一个最直接的解决办法就是，调用 [PIL.Image.convert()](https://pillow.readthedocs.io/en/stable/reference/Image.html#PIL.Image.Image.convert)将RGB图片转为RGBA图片，然后代码就能正常运行

<br>

***

# 示例代码：

```python
import sys
from PyQt5.QtWidgets import QWidget,QLabel,QApplication
from PIL import Image
#from PIL import ImageQt

if __name__ == '__main__':
	im=Image.open('图片.jpg')
	print(im.mode)#如果该图是RGB那么转换为QPixmap会报错
	#im=im.convert("RGBA")#转为RGBA模式


	app = QApplication(sys.argv)
	lb=QLabel()
	lb.resize(600,375)
	lb.show()
	lb.setPixmap(im.toqpixmap())
	sys.exit(app.exec())

```


<br>

***
### 小小声：
1. 模块API问题估计得反馈到官方那边才会修
2. 在PIL官网愣是没找到``PIL.Image.toqpixmap()``，又是个更新不同步问题。只不过如果的确没有该函数的话可以使用``PIL.ImageQt.toqpixmap()``作为替代

