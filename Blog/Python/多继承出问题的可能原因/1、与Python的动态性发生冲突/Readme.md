

虽然想做一个PPAP梗图，但没技术力就算了，用文字形容就是：
(左手)Python动态性；
(右手)Python多继承；
(两手合起来)额~哦~，“类对象无此属性”、“错误调用”；

<br>

***

这里提供两份代码以及对应的运行结果，一份是Python的，一份是C++的。

在下面的代码中能明显看出来，Python中的基类调用的公有函数是属于派生类的，私有函数才是调用自个儿的，因此如果想要基类顺利调用自己的公有函数，就必须通过“类名.函数名(self,参数)”的方式进行调用。

<br>

### Python

```python
class A:
	def __init__(self,isPublic=False):
		if(isPublic):
			self.Print("aaa")
			# A.Print(self,"aaa")#要通过这种方式才能正确调用到
		else:
			self.__Print("aaa")
	def __Print(self,val):
		print(f">>>[PRIVATE]A-{val}")
	def Print(self,val):
		print(f">>>[PUBLIC]A-{val}")

class B(A):
	def __init__(self,isPublic=False):
		super().__init__(isPublic)
		if(isPublic):
			self.Print("bbb")
		else:
			self.__Print("bbb")
	def __Print(self,val):
		print(f">>>[PRIVATE]B-{val}")
	def Print(self,val):
		print(f">>>[PUBLIC]B-{val}")

if __name__=='__main__':
	print("it's Python")
	for flag in [False,True]:
		print(f'\nisPublic={flag}')
		B(isPublic=flag)
```

![运行结果-Python](./Demo/运行结果-Python.png)

<br>


### C++

```cpp
#include<stdio.h>

class A {
public:
	A(bool isPublic = true) {
		if (isPublic)
			this->Print("aaa");
		else 
			this->__Print("aaa");
	}
public:
	virtual void Print(const char* ch) {
		printf_s(">>>[PUBLIC]A-%s\n", ch);
	}
private:
	virtual void __Print(const char* ch) {
		printf_s(">>>[PRIVATE]A-%s\n", ch);
	}
};

class B :public A {
public:
	B(bool isPublic=true) :A(isPublic) {
		if (isPublic)
			this->Print("bbb");
		else
			this->__Print("bbb");
	}
public:
	virtual void Print(const char* ch) {
		printf_s(">>>[PUBLIC]B-%s\n", ch);
	}
private:
	virtual void __Print(const char* ch) {
		printf_s(">>>[PRIVATE]B-%s\n", ch);
	}
};

int main() {
	bool flags[] = { false,true };
	bool flag = false;
	printf_s("It's C++\n");
	for (auto i = 0; i < 2; ++i) {
		flag = flags[i];
		printf_s("\nisPublic=%s\n", flag ? "True" : "False");
		B b(flag);
	}
	return 0;
}
```

![运行结果-C++](./Demo/运行结果-C++.png)

<br>

