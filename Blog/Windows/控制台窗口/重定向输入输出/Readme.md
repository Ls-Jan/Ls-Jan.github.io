




- 不要妄图使用``SetStdHandle``这个winAPI来实现这功能，这API是个摆设，强调，这winAPI仅仅只是个摆设，它唯一会影响到的API是``GetStdHandle``；
- 如果你当前用的是CRT函数，即``printf_s``之类的，那么如果想重定向输入输出，最好的方法是调用同为CRT函数的一个名为``freopen``的函数，没错，CRT函数的上下文不该由winAPI来完成，例如CRT函数中有个是``setlocale``用于设置区域语言的，这个区域语言仅适用于CRT函数；
- ``setlocale``所设置的字符集对winAPI的A系函数那是一丝影响都造成不了的，那些A系函数照常使用系统的ANSI字符集；
- 猜测``std::cout``底层用的东西多半和``printf_s``相关，因为``setlocale``能同样影响到``std::cout``的输出，虽然没有直接的源码证明；
- CRT函数中的标准输入输出，在程序启动的时候就已经固定了的(与其说是固定倒不如说是偷懒把输入输出给特么的缓存起来了)，并且底层估计是没使用``WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),...)``，而这直接导致的就是``SetStdHandle``卵用没有；
- 是找到了一个使用``_open_osfhandle``+``_dup2``的方式实现的代码，但我本机在调用``_dup2``时并没有成功，错误代号``errno``为``EBADF``，由此质疑这种做法是否靠谱；
- 一篇博客中提到，用``_open_osfhandle``尝试关联``HANDLE``和``文件描述符``的做法是相当危险的，不建议混用CRT函数和winAPI，不然造成的bug可是一时半会都修不好；
- 介于上述两点，无法实现将一个已经运行的程序的标准输入输出重定向到管道，或者准确点的说就是无法将``printf_s``之类的CRT函数的标准输入输出重定向到管道(或是别的什么地方)；
- 如果真想使用重定向，那只能新写一个函数RePrint，函数内部调用``vswprintf_s``+``WriteFileW``+``GetStdHandle``，然后其他地方都使用这个RePrint函数而不用``wprintf_s``。说实话这种做法也是有一些棘手，倒不如说为什么一定要搞这样的重定向？太麻烦了，直接抛弃``printf_s``这个老登函数不好吗？
- 当然，使用子进程的方式实现标准输入输出重定向也是一种做法，或者说这应该就是重定向的最优解；

<br>


# 参考：
- 控制台句柄：[https://learn.microsoft.com/zh-cn/windows/console/console-handles](https://learn.microsoft.com/zh-cn/windows/console/console-handles)
- SetStdHandle对cout/printf没有影响：[https://www.coder.work/article/558106](https://www.coder.work/article/558106)
- SetStdHandle无法对进程的标准输入输出重定向：[https://github.com/MicrosoftDocs/Console-Docs/issues/95](https://github.com/MicrosoftDocs/Console-Docs/issues/95)
- VC++的文件描述符和内核文件句柄HANDLE：[https://www.cnblogs.com/fullsail/archive/2012/10/21/2732873.html](https://www.cnblogs.com/fullsail/archive/2012/10/21/2732873.html)
- 在win32中重定向stdout失败：[https://www.coder.work/article/2113476](https://www.coder.work/article/2113476)
- _open_osfhandle：[https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/reference/open-osfhandle?view=msvc-170](https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/reference/open-osfhandle?view=msvc-170)
- _dup，_dup2：[https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/reference/dup-dup2?view=msvc-170](https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/reference/dup-dup2?view=msvc-170)
- errno常量：[https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/errno-constants?view=msvc-170](https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/errno-constants?view=msvc-170)


