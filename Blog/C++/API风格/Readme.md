


其实无论哪种语言，都得决定好API的设计风格，只不过由于C/C++的语言特性，它们更加注重这方面的设计。
API设计的好坏直接体现一个程序员是否具备足够的设计理念。


<br>

# API简单介绍：

众所周知，API，有三个基础要素：
- 函数名称；
- 函数返回值；
- 函数参数；

##### 注意：
函数体不在其中。
API实际上应该理解为**函数声明**，用其他术语来形容则是**函数签名**。
我们应该清楚的认识到，声明与定义的区别。
函数体作为函数的定义不应该同时出现在函数的声明中，如果出现了“声明和定义同时写在一个地方”的时候那就该自问一句是否明白这样做会带来什么样的问题。


事实上在实际应用中你不总能拿得到函数定义，只能拿到链接库lib/dll或者编译过程文件obj或是其他形式的文件，因此函数定义不应该作为API的基本要素。
而且再有一点，函数体内部哪怕闹得再大，写得再烂，里头写着各种杂七杂八的怪东西，也无关外部的调用。

更单纯点的说就是，函数体是可变的，而API是不可变的。
API若是发生改变，对项目的冲击将是巨大的，可以试想一下假如一个自定义函数``Print``的参数/返回值发生变化，其余所有用到这个``Print``函数的代码都得进行或大或小的改动(轻则三两处，重则十余个，再重点则波及数个/数十个源文件)，这不是一句简单的**文本替换Ctrl+F**就能完事的。


***

# API的设计风格：
通常来说，一个系列的API应该同时保持同样的风格，它们的函数名、参数列表以及返回值应该最大程度的保持一致。

以winAPI进行举例，对文件进行操作会有如下API：
##### 打开/创建文件：
```cpp
HANDLE CreateFile(
  [in]           LPCSTR                lpFileName,
  [in]           DWORD                 dwDesiredAccess,
  [in]           DWORD                 dwShareMode,
  [in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  [in]           DWORD                 dwCreationDisposition,
  [in]           DWORD                 dwFlagsAndAttributes,
  [in, optional] HANDLE                hTemplateFile
);
```
##### 读取文件：
```cpp
BOOL ReadFile(
  [in]                HANDLE       hFile,
  [out]               LPVOID       lpBuffer,
  [in]                DWORD        nNumberOfBytesToRead,
  [out, optional]     LPDWORD      lpNumberOfBytesRead,
  [in, out, optional] LPOVERLAPPED lpOverlapped
);
```

##### 写入文件：
```cpp
BOOL WriteFile(
  [in]                HANDLE       hFile,
  [in]                LPCVOID      lpBuffer,
  [in]                DWORD        nNumberOfBytesToWrite,
  [out, optional]     LPDWORD      lpNumberOfBytesWritten,
  [in, out, optional] LPOVERLAPPED lpOverlapped
);
```

<br>

实际上如果要做的更彻底点的话，那就应该使用``PHANDLE``，将所有的API统一成这种形式：``BOOL xxxFile(PHANDLE, ...)``。

API统一的难度从低到高依次是：
- 名称，使用共同前缀或后缀，例如采用``xxxFile``、``FileXXX``的形式；
- 返回值，例如统一返回``BOOL``；
- 参数，某一个/几个参数的类型、位置、含义固定，例如首参数固定使用``PHANDLE``，意为对目标句柄进行特定操作；



