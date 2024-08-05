

# 简单介绍：

- 控制台窗口，别名“黑窗口”、“命令行窗口”、“DOS窗口”、“CUI窗口”，这类窗口内部只能显示字符，无法进行更高级的显示(绘制线条等)；
- 控制台这种说法，在Linux中更习惯以“终端”来形容；
- 控制台应用程序，就是启动时以黑窗口运行的一个普通程序，没有GUI界面；
- 所有进程，都能开控制台，无论它是不是GUI(图形用户界面)程序，只是GUI程序在程序生成期间通过了代码或者配置将控制台默认关闭了而已；
- 通常GUI程序并不需要控制台，除非是为了特别的需求，例如快速输出日志信息和调试信息，在GUI程序代码项目的Debug期间可以考虑启动控制台以减轻Debug压力；
- 通过特殊参数设置，可以将控制台关闭，以实现程序的后台运行，但实际上并不会这么做，因为这会导致程序没有任何运行上的反馈，除非是为了做恶意程序(让程序偷偷运行在机器中)；

<br>

# 更多细节：
- 所有进程，能且仅能使用至多一个控制台窗口；
- 一个控制台窗口可以被多个进程绑定，或者说支持多个进程的输入输出定向到同一个控制台窗口上，但很明显这样做非常棘手，通常不会考虑这种做法；
- ``AllocConsole``可以创建一个新的控制台，而``AttachConsole``是附加到已有控制台上，``FreeConsole``用于关闭控制台(准确的说是断开与控制台的关联)；
- 应用程序开启/附加新的控制台后，如果想用诸如``printf``之类的CRT函数打印内容就必须调用CRT函数中的``freopen``重置标准输入输出；
- 如果一个控制台与多个进程关联，则仅在所有相关进程与该控制台都断开关联(要么进程关闭，要么进程主动调用``FreeConsole``)该控制台窗口才会关闭；
- 标准输入输出(STDIN/STDOUT)通常重定向于控制台上；
- 控制台窗口有``chcp``这个命令，用于设置当前的控制台代码页；
- 很明显，代码页的设置将会直接导致输入输出是否会出现异常情况，例如字符显示出现乱码，输入字符回车后程序得到错误数据甚至程序崩溃；



# 其他：
#### 伪控制台:
所谓伪控制台，就是将传统的控制台输入输出重定向到一个GUI窗口，以实现更加友好的界面显示。
因为传统黑窗口控制台的各种显示问题大家都是有眼可见的了。
重定向的方法通常是那个GUI窗口进行子进程的创建，并设置子进程的标准输入输出进行。




# 参考：

- ``chcp``：[https://learn.microsoft.com/zh-cn/windows-server/administration/windows-commands/chcp](https://learn.microsoft.com/zh-cn/windows-server/administration/windows-commands/chcp)
- 创建控制台：[https://learn.microsoft.com/zh-cn/windows/console/creation-of-a-console](https://learn.microsoft.com/zh-cn/windows/console/creation-of-a-console)
- 伪控制台：[https://learn.microsoft.com/zh-cn/windows/console/pseudoconsoles](https://learn.microsoft.com/zh-cn/windows/console/pseudoconsoles)
- 创建伪控制台会话：[https://learn.microsoft.com/zh-cn/windows/console/creating-a-pseudoconsole-session](https://learn.microsoft.com/zh-cn/windows/console/creating-a-pseudoconsole-session)
- 控制台函数：[https://learn.microsoft.com/zh-cn/windows/console/console-functions](https://learn.microsoft.com/zh-cn/windows/console/console-functions)



