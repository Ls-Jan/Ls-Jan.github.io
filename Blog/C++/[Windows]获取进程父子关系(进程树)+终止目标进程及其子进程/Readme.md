
使用``快照``获取进程的父子关系。

1. ``PROCESSENTRY32``中有个数据成员为``th32ParentProcessID``，借此获取进程间的父子关系。
2. ``创建快照和查看过程``，有着1+2个关键函数(这仨函数搭配使用的，建议直接查看[示例](https://learn.microsoft.com/zh-cn/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes))：``CreateToolhelp32Snapshot``，``Process32First``，``Process32Next``
3. 使用``TerminateProcess``关闭进程，但由于该函数需要进程句柄所以还得使用函数``OpenProcess``。

顺便一说的就是，``TerminateProcess``官方文档明说是强制终止进程，说的直白点就是该函数的清理工作做的很不到位，其中一点就是仅杀死父进程后子进程很可能会成为后台进程驻留在系统内(得开任务管理器手动清理)，所以使用该函数终止进程时需要连同子进程一并杀死以防止残留。

还有就是，使用快照遍历所有进程，看似很耗时间，实际上并没有，我一开始也以为要“遍历”会不会很慢，然后发现香的不行，所以不必担心造成卡顿。


<br>

***
# 代码

```cpp
#include<map>
#include<vector>
#include<Windows.h>
#include <tlhelp32.h>

namespace ProcessRelation {
    std::map<DWORD, std::vector<DWORD>>GetProcessRelation();//获取进程父子关系。键值对含义为：pid:[P-pid,C-pid,C-pid,...]，(其中，P-Parent，C-Child)
    void ProcessRelation::TerminateProcessTree(DWORD pid);//终结以pid为根节点的进程树
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------

std::map<DWORD, std::vector<DWORD>> ProcessRelation::GetProcessRelation() {//获取进程父子关系。键值对含义为：pid:[P-pid,C-pid,C-pid,...]，(其中，P-Parent，C-Child)
    std::map<DWORD, std::vector<DWORD>>tree;

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);
        for (Process32First(hSnap, &pe32); Process32Next(hSnap, &pe32);) {
            DWORD curr = pe32.th32ProcessID;
            DWORD parent = pe32.th32ParentProcessID;
            std::vector<DWORD>& Vcurr = tree[curr];
            std::vector<DWORD>& Vparent = tree[parent];

            if (Vcurr.empty())
                Vcurr.push_back(0);
            if (Vparent.empty())
                Vparent.push_back(0);
            Vcurr[0] = parent;
            Vparent.push_back(curr);
        }
        CloseHandle(hSnap);
    }
    return tree;
}



void ProcessRelation::TerminateProcessTree(DWORD pid) {//终结以pid为根节点的进程树
    std::map<DWORD, std::vector<DWORD>> ret = ProcessRelation::GetProcessRelation();
    std::vector<DWORD>lst;
    std::vector<DWORD>stk = { pid };
    while (stk.empty() == false) {
        DWORD pid = stk.back();
        stk.pop_back();
        for (auto p = ret[pid].begin() + 1; p != ret[pid].end(); ++p) {
            lst.push_back(*p);
            stk.push_back(*p);
        }
    }
    //for (auto p = lst.begin(); p != lst.end(); ++p) {
    //    std::cout << *p << std::endl;
    //}
    for (auto p = lst.begin(); p != lst.end(); ++p) {
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, *p);
        if (hProc != INVALID_HANDLE_VALUE) {
            TerminateProcess(hProc, -1);
            WaitForSingleObject(hProc,INFINITE);
            CloseHandle(hProc);
        }
    }
}
```


# 参考：

- PROCESSENTRY32结构：[https://learn.microsoft.com/zh-cn/windows/win32/api/tlhelp32/ns-tlhelp32-processentry32](https://learn.microsoft.com/zh-cn/windows/win32/api/tlhelp32/ns-tlhelp32-processentry32)

- 创建快照和查看过程：[https://learn.microsoft.com/zh-cn/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes](https://learn.microsoft.com/zh-cn/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes)

- TerminateProcess 函数：[https://learn.microsoft.com/zh-cn/windows/win32/api/processthreadsapi/nf-processthreadsapi-terminateprocess](https://learn.microsoft.com/zh-cn/windows/win32/api/processthreadsapi/nf-processthreadsapi-terminateprocess)

- OpenProcess 函数(英文未机翻)：[https://learn.microsoft.com/zh-cn/windows/win32/api/processthreadsapi/nf-processthreadsapi-openprocess](https://learn.microsoft.com/zh-cn/windows/win32/api/processthreadsapi/nf-processthreadsapi-openprocess)

