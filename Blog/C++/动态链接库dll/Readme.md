请跳转github仓库查看Readme：https://github.com/Ls-Jan/CPP_DLL

这里不进行赘述


# 补充：

#### 1、dll无命名空间：
脑抽了，想老半天才想通，dll是C语言的，它没有命名空间这种东西，
在C++中编写的带命名空间的dllexport函数在生成后的dll中是没有命名空间的，或者说不同命名空间的同名dllexport函数在dll生成过程中必报错。

说难听点就是使用dll极大可能污染命名空间，
换个说法就是导入dll极有可能造成函数同名问题，
见仁见智了这下。

通常做法是别使用简单函数名，像是``print``这样的，真用了的话只能佛祖保佑。

#### 2、不同命名空间的同名函数链接到同一个函数定义：
大胆猜测，未经实测。
假如项目中调用M::Func和N::Func，并且它们都没有函数定义，然后我此时将一个带有Func函数的链接库引入到项目后：
1. 项目能正常生成；
2. 调用M::Func和N::Func实质上都是调用同一个Func函数；


#### 3、*.def文件中语句LIBRARY后的名称：
实测这名称无明显作用。
- 模块定义语句的规则——LIBRARY：[https://learn.microsoft.com/zh-cn/cpp/build/reference/library?view=msvc-170](https://learn.microsoft.com/zh-cn/cpp/build/reference/library?view=msvc-170)

