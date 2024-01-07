
仅限于整活，当扩展眼界。
平常开发不建议使用<font size=1>(直接跟个if语句不好吗</font>

<br>

***

### 使用三目运算符调用函数

##### 三目运算符的前后值要保持一致，因此前面的函数返回什么类型的，后面的数也得一样

```cpp
int Test(){//非空类型的函数
	printf("Test被执行\n");
}

#include <stdio.h>
int main(){
	bool flag=true;
	flag?Test():int();//三目运算符的前后值类型要一致。(这里的int()可以随便一个整数代替
	return 0;
}
```

##### 如果前面的函数是void，那么可以对应用个“空变量void()”
```cpp
#include <stdio.h>
void Test(){//void类型的函数
	printf("Test被执行\n");
}

int main(){
	bool flag=true;
	flag?Test():void();//空变量
	
    void (*func)()=flag?&Test:nullptr;//函数指针。这行语句可以偷懒写成这样：auto func=flag?&Test:nullptr;
    func?func():void();//特别的，对于函数指针来说，要提前判空才调用去调用
	return 0;
}
```


##### 特别的，可以使用逗号表达式串联调用多个函数

```cpp
#include <stdio.h>
void Test1(){//空类型的函数
	printf("Test1被执行\n");
}
int Test2(){//非空类型的函数
	printf("Test2被执行\n");
	return 0;
}

int main(){
	bool flag=true;
	flag?(Test1(),Test2(),NULL):NULL;
	//逗号表达式仅最后的值有效，前面的单纯是执行而已。
	//可以把一堆的赋值或是函数(其实赋值也可以看做是函数的一种)放进一行：
	//(a=10),(b=5.6),(Sum(a,b)),(c='x');
    //但对后期的维护会造成不小的麻烦，不建议
	return 0;
}
```



