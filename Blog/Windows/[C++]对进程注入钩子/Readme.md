
//TODO:内容待进一步的补充


诶？真的要这么做吗？
很麻烦的诶。
出问题我可不管的哦。
虽然有点关心做DLL注入的目的，但还是算了。


<br>

# 注入钩子的注意事项
安装钩子的目的基本是消息拦截

- dll必须和目标程序的位数(x86/x64)匹配，否则无法调用；
- 注入程序必须与目标程序的位数(x86/x64)匹配；
- 代码页的不一致或成为一种阻碍；
- 注入钩子一定要用W系函数，避免特殊字符路径；







# 参考：
- SetWindowsHookEx()第四个参数如何理解？：[https://bbs.csdn.net/topics/230056375](https://bbs.csdn.net/topics/230056375)
- c# - SetWindowsHookEx 失败并出现错误 126： [https://www.coder.work/article/953173](https://www.coder.work/article/953173)
- 使用SetWindowsHookEx监控窗口消息(1)：[https://yhsnlkm.github.io/2019/12/25/攻防保护/使用SetWindowsHookEx监控窗口消息-1/](https://yhsnlkm.github.io/2019/12/25/攻防保护/使用SetWindowsHookEx监控窗口消息-1/)
- c++ - SetWindowsHookEx 没有调用我的回调？：[https://www.coder.work/article/3228159](https://www.coder.work/article/3228159)
- ``LoadLibrary``：[https://learn.microsoft.com/zh-cn/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibraryw](https://learn.microsoft.com/zh-cn/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibraryw)
- ``FindResource``：[https://learn.microsoft.com/zh-cn/windows/win32/api/winbase/nf-winbase-findresourcea](https://learn.microsoft.com/zh-cn/windows/win32/api/winbase/nf-winbase-findresourcea)
- ``GetModuleHandle``：[https://learn.microsoft.com/zh-cn/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandlew](https://learn.microsoft.com/zh-cn/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandlew)
- 命名文件、路径和命名空间：[https://learn.microsoft.com/zh-cn/windows/win32/fileio/naming-a-file](https://learn.microsoft.com/zh-cn/windows/win32/fileio/naming-a-file)
- ``GetCurrentDirectory``：[https://learn.microsoft.com/zh-cn/windows/win32/api/winbase/nf-winbase-getcurrentdirectory](https://learn.microsoft.com/zh-cn/windows/win32/api/winbase/nf-winbase-getcurrentdirectory)
- ``getFullPathName``：[https://learn.microsoft.com/zh-cn/windows/win32/api/fileapi/nf-fileapi-getfullpathnamew](https://learn.microsoft.com/zh-cn/windows/win32/api/fileapi/nf-fileapi-getfullpathnamew)
- ``SetDllDirectoryA``：[https://learn.microsoft.com/zh-cn/windows/win32/api/winbase/nf-winbase-setdlldirectorya](https://learn.microsoft.com/zh-cn/windows/win32/api/winbase/nf-winbase-setdlldirectorya)
- Load-Time动态链接：[https://learn.microsoft.com/zh-cn/windows/win32/dlls/load-time-dynamic-linking](https://learn.microsoft.com/zh-cn/windows/win32/dlls/load-time-dynamic-linking)
- 遍历模块列表：[https://learn.microsoft.com/zh-cn/windows/win32/toolhelp/traversing-the-module-list](https://learn.microsoft.com/zh-cn/windows/win32/toolhelp/traversing-the-module-list)
- 拍摄快照，查看进程：[https://learn.microsoft.com/zh-cn/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes](https://learn.microsoft.com/zh-cn/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes)
- 动态链接库最佳做法：[https://learn.microsoft.com/zh-cn/windows/win32/dlls/dynamic-link-library-best-practices](https://learn.microsoft.com/zh-cn/windows/win32/dlls/dynamic-link-library-best-practices)



