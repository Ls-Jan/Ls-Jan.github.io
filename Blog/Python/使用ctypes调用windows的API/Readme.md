

以下示例略微复杂，其中使用到的关键API有：
- ``user32.MonitorFromRect``：根据所给矩形``RECT``返回监视器句柄``HMONITOR``；
- ``user32.GetMonitorInfo``：根据所给监视器句柄``HMONITOR``返回监视器相关信息``MONITORINFO``；
- ``QWidget.nativeEvent``：重写这个事件函数以进行更加底层/原生的消息拦截；
- ``ctypes.Structure``：创建ctypes类型时必须继承的类，其中属性``_fields_``是一个格式为``('attr',TYPE)``的列表，元组对应着属性名+属性类型；
- ``ctypes.pointer``：获取C结构体对象的指针，以便传递给winAPI；
- ``ctypes.POINTER``：搭配``ctypes.cast``使用，将一个指针强转至指定类型，以便数据的后续解析；


详细用法不再进行具体说明，因为代码示例足够作为示范了。



<br>



# 参考：
- Python type()函数：[https://www.runoob.com/python/python-func-type.html](https://www.runoob.com/python/python-func-type.html)
- Python ctypes数据类型—结构体：[https://blog.csdn.net/qq_33287871/article/details/100127524](https://blog.csdn.net/qq_33287871/article/details/100127524)
- ctypes.cast：[https://docs.python.org/zh-cn/3/library/ctypes.html#type-conversions](https://docs.python.org/zh-cn/3/library/ctypes.html#type-conversions)
- 如何从sip.voidptr (QImage.constBits())到ctype、void或char指针？：[https://cloud.tencent.com/developer/ask/sof/114745777](https://cloud.tencent.com/developer/ask/sof/114745777)
- Python 与 C 之强制类型转换：[https://my.oschina.net/u/3695598/blog/3133426](https://my.oschina.net/u/3695598/blog/3133426)



