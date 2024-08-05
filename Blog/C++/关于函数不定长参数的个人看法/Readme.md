

好难用，相当的难用，难用到爆，而且问题多多，算是一个埋雷小能手。
若非必要，使用``std::vector<void*>``等手段进行传参会更加安全便利。


<br>

# 简述：
在对``printf_s``进行简单封装的时候，发现了各种问题，这也让我不得不重新看待这个函数中存在的API设计问题，然后发现其核心问题是不定长参数造成的。

<br>

不定长参数，的确有用，但说实话并不那么好用。

说它有用，是因为通过它可以往函数中放入任意个参数；
说它难用，是因为：
- 硬性需要一个首参数以获取不定参数列表以及不定参数的实际个数；
- 极易出现数组越界，以``printf_s``作为举例，这函数哪怕警告也能跑，会不会白窗口就另一回事了；
- 拿到的这些不定参数都必须进行转换(使用``va_arg``)才能继续使用；
- 无法接力传递给下一个不定长参数函数；

最后一点直接注定了``printf_s``无法进一步封装(或者说封装起来会非常令人郁闷)，
或者说对于那些不定长参数函数来说，想将其封装那简直就是痴人说梦。

<br>

在不定长参数函数中通过``va_start``拿到的``va_list``数据记录着不定长参数栈的起始地址，其中的参数数据就必须得手动调用``va_arg``指定参数类型一个个地拿出来，姑且不谈类型不同的情况，由于C/C++并不像py、js那样有**列表解包**的概念，哪怕可以用``vector``之类的容器将其装载，也无法将其传递给下一个不定长参数函数。

C运行时库(CRT)给出的解决办法是，使用以``va_list``为参数的函数，这类函数我习惯称之为v系函数，例如``vprintf_s``、``vsprintf_s``等。

也就是如果创建一个不定长参数函数的话，建议再顺手搓一个以``va_list``为参数的v函数，万一这个v函数哪天又用得上了呢？
对此我只能说，好抽象，将麻烦推给了函数实现，虽然函数调用是省事了(真的?)，但函数实现那可谓是不少麻烦。
虽然说是这么说，事实上不定长参数函数的那些参数通常都是同一类型的，函数实现写起来倒不那么麻烦，
例如写了一个整数求和函数``sum(count,...)``，然后就能以这种方式进行调用：``sum(3,111,333,555)``，
只不过这里的缺陷也十分的明显，那就是假如我传入的是双精浮点数而不是整数时，这个sum函数必然会得到错误结果，但它是通过语法检查的，也就是在编译乃至运行之前都无法确认这个sum函数是不是安全的。

简单点的说就是**不定长参数函数极易埋雷，调用时稍有不留意就会导致错误结果的发生，而且这个雷通常无法在编译/运行前就能排查出来**，这完全靠程序员自觉了，说实话，真信得过？真觉得调用你API的都不会犯错？更何况传错参数时IDE连个屁都不放，导致这错误更加的隐蔽。


<br>

# 示例代码：
该示例定义了一个**RePrint**的不定长参数函数，参数格式与``printf_s``一致，
但是**RePrint**支持重定向行为，使用``SetStdHandle``可以将输出重定向至管道或是其他地方。

<br>

主函数演示了匿名管道的使用以及**RePrint**的重定向效果，
将写进管道的数据读取出来并以十六进制的方式显示其中的数据。

将示例代码以utf-8进行保存并进行编译(需附加编译参数``/utf-8``)，
实际运行结果就是输出了字符“贰”的UTF-8编码``E8 B4 B0``。

![运行结果](./Pict_运行结果.png)

```cpp
#include<stdarg.h>
#include<Windows.h>
#include<stdio.h>
#include<locale>

//具有重定向效果的打印函数，作为printf_s的高级平替。
//调用SetStdHandle即可重定向输出。
void RePrint(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);//va_start的第二参数必须是紧跟在省略号前面的参数，它是用来抓参数栈的地址的

	const int sz = BUFSIZ;
	char buf[sz] = "";
	vsprintf_s(buf, fmt, args);
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buf, max(sz, 1 + strnlen_s(buf, sz)), NULL, NULL);

	va_end(args);//还是尽量调用这个函数吧，作为一种规范
}

//创建匿名管道
BOOL Pipe_Create(PHANDLE phWr, PHANDLE phRd) {
	if (phWr == nullptr || phRd == nullptr)
		return FALSE;
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	return CreatePipe(phRd, phWr, &saAttr, 0);
}

int wmain(int argc, wchar_t* argv[]) {
	HANDLE hWr;
	HANDLE hRd;
	const char tx="贰";
	char buf[BUFSIZ] = "";

	setlocale(LC_CTYPE, ".65001");
	Pipe_Create(&hWr, &hRd);
	SetStdHandle(STD_OUTPUT_HANDLE, hWr);
	RePrint("%s", tx);
	ReadFile(hRd, buf, BUFSIZ, NULL, NULL);
	CloseHandle(hWr);
	CloseHandle(hRd);

	printf_s(">>> ");//输出十六进制
	for (auto i = 0; buf[i]; ++i)
		printf_s("%02X ", (unsigned char)buf[i]);
	printf_s("\n");

	return 0;
}

```

<br>


# 扩展阅读(看不懂，不想看)：
- [c语言中函数参数入栈的顺序是什么？为什么](https://www.cnblogs.com/zhaopengcheng/p/6522523.html)
- [可变参数实现原理-参数栈](https://www.cnblogs.com/kuikuitage/p/14018113.html)
- [函数调用的参数压栈（详解）](https://blog.51cto.com/musnow/5118286)
- [运行时获取函数调用栈](https://www.jianshu.com/p/4aadb4fd00c7)


<br>
<br>



# 参考：
- C 可变参数：[https://www.runoob.com/cprogramming/c-variable-arguments.html](https://www.runoob.com/cprogramming/c-variable-arguments.html)
- C 库函数 - printf：[https://www.runoob.com/cprogramming/c-function-printf.html](https://www.runoob.com/cprogramming/c-function-printf.html)
- C 库宏 - va_start：[https://www.runoob.com/cprogramming/c-macro-va_start.html](https://www.runoob.com/cprogramming/c-macro-va_start.html)
- C 库函数 - vsprintf：[https://www.runoob.com/cprogramming/c-function-vsprintf.html](https://www.runoob.com/cprogramming/c-function-vsprintf.html)
- C 库宏 - va_start：[https://www.runoob.com/cprogramming/c-macro-va_start.html](https://www.runoob.com/cprogramming/c-macro-va_start.html)
- C 标准库 - stdarg.h：[https://www.runoob.com/cprogramming/c-standard-library-stdarg-h.html](https://www.runoob.com/cprogramming/c-standard-library-stdarg-h.html)
- 包含变量自变量列表的函数 (C++)：[https://learn.microsoft.com/zh-cn/cpp/cpp/functions-with-variable-argument-lists-cpp?view=msvc-170](https://learn.microsoft.com/zh-cn/cpp/cpp/functions-with-variable-argument-lists-cpp?view=msvc-170)
- vprintf：[https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/vprintf-functions?view=msvc-170](https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/vprintf-functions?view=msvc-170)
- 理解可变参数va_list、va_start、va_arg、va_end原理及使用方法 ：[https://www.cnblogs.com/pengdonglin137/p/3345911.html](https://www.cnblogs.com/pengdonglin137/p/3345911.html)

