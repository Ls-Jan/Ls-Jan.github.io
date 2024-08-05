



以下内容：
- 不保证全面；
- 涉及到计算机组成原理的部分内容；
- 是C/C++以及Windows开发中必绕不开的问题；
- 不打算详细介绍字符集，请网上自找资料；



<br>
<br>

# 简述：
- 代码页就是字符集，只不过代码页可以用一个数字代号表示一个字符集，例如936(GBK)、54936(GB18030)、65001(UTF-8)等；
- 代码页这种概念最初是来源于控制台，现在更习惯使用“字符集”这种说法；
- 在windows中，你所有能选中的字符(包括控制台窗口中的字符)，它们的编码全都是UTF-16LE，天王老子来了都是这个编码；

- windows的控制台界面已经锁死了，难以继续发展，它当初的设计已然完全无法满足如今需求，但积重难返，想要显示更多种类的字符就得修改不少的地方，而且估计v软也没什么动力去修理这个上古遗迹；
- win系统语言决定了ANSI对应哪个字符集，例如简中对应的是GB2312(936)，只不过虽然说的是GB2312但实际上它支持的是GBK，这就非常搞笑了，笑笑就好了哈哈哈哈哈(无语)。至于国标字符集GB18030，对应的代码页是54936，只不过并不是默认字符集；
- 关于上面的问题，win没更新默认字符集是因为，win底层采用了UTF-16这个字符集，使用Unicode编码可以顺利地让一台电脑显示各种语言字符，也就没什么必要使用本地语言(导致简中ANSI一直停留在936)，这同时也就是MSDN里常看到的“国际化”的含义；
- 操作系统的字符集统一，好处就是所有窗口内的文本字符都是采用同一套编码，因此在跨窗口进行文本的复制粘贴时通常不会出现乱码问题(以UTF-16编码进行传输)，如果出问题则多半是目标窗口导致的(例如A系函数和W系函数混用)；
- 不使用UTF-8是因为当时没有，并且因为v软用力过猛导致无力回天，新兴系统和语言都优先采用UTF-8这个编码，例如Linux、Python等；
- win的很多API都有A(ANSI)版本和W(Wide)版本，留下A系函数是为了所谓的旧软件兼容，只不过这个设计明显是失败的，不肯切干净还留下了大量的模棱两可，然后又使用了T宏的结果却是导致了更多麻烦，这也导致了不少软件出现了编码上的问题；
- 列举部分的T宏，例如``TEXT``、``_TCHAR``、``_tcsclen``、``TCHAR``等，额，反正不建议，混着用迟早暴毙，尽量摸清自己的项目到底是以A系还是以W系为核心，并且那些winAPI都准确的写明是A函数还是W函数，例如``CreateFileW``而不是简单的写成``CreateFile``；
- win提供了一个utf-8的代码页设置，有望能整活A系函数(然后W系函数又被整死)；
- win里头的utf-16可是靠着W系函数苟活着的呢；
- 当初推出W系函数因为V软当时认为宽字节所能表达的6w余字符绰绰有余，也就是在当时UTF-16是个定长字符集，所有字符都是2字节表示，定长字符集的优势不必赘述，反正就是字符的处理会非常省事。但后来发现，UTF-16并不够用，于是它变成了变长字符集，很好，优势立马丧失，拿到的2字节不一定就是一个字符，还得进行所谓的“代理对判断”；


<br>

# 补充：

- 别用A系函数，别用A系函数，别用A系函数，我看不到这个函数所带来的好处，例如``CreateFileA``尝试打开路径含有系统ANSI字符集以外的字符时(例如生僻字或是其他国家的字符)必然出错，而且A系函数并不吃``setlocale``的效果，winAPI也并没有提供这种设置系统ANSI字符集的玩意儿，至少我是没搜到，最多也就搜到这种``GetSystemDefaultLangID``获取系统语言的winAPI；
- 而且为啥一定要用A系函数，哪怕真一定要用，为什么不选择W系函数+``WideCharToMultiByte/MultiByteToWideChar``这种做法呢；




<br>


# 参考：

- Java 为什么使用 UTF-16 而不是更节省内存的 UTF-8？- Victor Yeh的回答 - 知乎[https://www.zhihu.com/question/308677093/answer/2748648048](https://www.zhihu.com/question/308677093/answer/2748648048)
- 知乎提问:Windows为什么用GBK而不是UTF-8？：[https://www.zhihu.com/question/20689098](https://www.zhihu.com/question/20689098)
- 知乎提问:为何微软不把 Windows 的默认字符集设置成 UTF-8 ？：[https://www.zhihu.com/question/24103924/answers/updated](https://www.zhihu.com/question/24103924/answers/updated)
- Windows下UTF-16的坑：[https://blog.codingnow.com/2019/05/windows_utf16.html](https://blog.codingnow.com/2019/05/windows_utf16.html)
- 在 Windows 应用中使用 UTF-8 代码页：[https://learn.microsoft.com/zh-cn/windows/apps/design/globalizing/use-utf8-code-page#-a-vs--w-apis](https://learn.microsoft.com/zh-cn/windows/apps/design/globalizing/use-utf8-code-page#-a-vs--w-apis)
- 代理项和增补字符：[https://learn.microsoft.com/zh-cn/windows/win32/intl/surrogates-and-supplementary-characters](https://learn.microsoft.com/zh-cn/windows/win32/intl/surrogates-and-supplementary-characters)
- 代码页：[https://learn.microsoft.com/zh-cn/windows/win32/intl/code-pages](https://learn.microsoft.com/zh-cn/windows/win32/intl/code-pages)
- ``TEXT``宏：[https://learn.microsoft.com/zh-cn/windows/win32/api/winnt/nf-winnt-text](https://learn.microsoft.com/zh-cn/windows/win32/api/winnt/nf-winnt-text)
- 使用一般文本映射：[https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/using-generic-text-mappings?view=msvc-170](https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/using-generic-text-mappings?view=msvc-170)
- main 函数和命令行参数：[https://learn.microsoft.com/zh-cn/cpp/cpp/main-function-command-line-args?source=recommendations&view=msvc-170](https://learn.microsoft.com/zh-cn/cpp/cpp/main-function-command-line-args?source=recommendations&view=msvc-170)
- 为什么需要字符集：[https://www.cnblogs.com/qqaz/p/15033042.html](https://www.cnblogs.com/qqaz/p/15033042.html)
- windows编程——宽字符集与Unicode 
：[https://www.cnblogs.com/BensonLaur/p/5241964.html](https://www.cnblogs.com/BensonLaur/p/5241964.html)
- 彻底搞懂字符编码：[https://www.cnblogs.com/robertoji/p/4976123.html](https://www.cnblogs.com/robertoji/p/4976123.html)
- TONT 33593 为什么 OEM 代码页经常被称作 ANSI？：[https://www.aoisnow.net/blog/archives/3209](https://www.aoisnow.net/blog/archives/3209)
- TONT 33753 有关日文版和韩文版 Windows 里路径分隔符的故事：[https://www.aoisnow.net/blog/archives/3191](https://www.aoisnow.net/blog/archives/3191)
- C++ 如何获取Windows操作系统的语言：[https://blog.csdn.net/hellokandy/article/details/122633225](https://blog.csdn.net/hellokandy/article/details/122633225)
- Windows 字符串数据类型：[https://learn.microsoft.com/zh-cn/windows/win32/intl/windows-data-types-for-strings](https://learn.microsoft.com/zh-cn/windows/win32/intl/windows-data-types-for-strings)
- Unicode：[https://learn.microsoft.com/zh-cn/windows/win32/intl/unicode](https://learn.microsoft.com/zh-cn/windows/win32/intl/unicode)
- 使用一般文本映射：[https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/using-generic-text-mappings?view=msvc-170](https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/using-generic-text-mappings?view=msvc-170)




