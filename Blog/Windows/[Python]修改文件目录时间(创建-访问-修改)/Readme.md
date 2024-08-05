

# 代码：

```python
from win32file import CreateFile, SetFileTime, GetFileTime, CloseHandle,CreateDirectory
from win32file import GENERIC_READ, GENERIC_WRITE, OPEN_EXISTING,FILE_FLAG_BACKUP_SEMANTICS
from pywintypes import Time  # 可以忽视这个 Time 报错（运行程序还是没问题的）
import os

def AlterFileFolderTime(path,createTime,accessTime,modifyTime):#修改文件/目录时间。传入的为时间戳
	fh=None#文件句柄
    try:
        if(os.path.isfile(path)):
            fh = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, None, OPEN_EXISTING,0 , 0)
        elif (os.path.isdir(path)):
            fh = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, None, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS , 0)
        else:
            return False
        SetFileTime(fh,*[Time(t) if t else None for t in [createTime,accessTime,modifyTime]])
        CloseHandle(fh)
        return True
    except Exception as e:
        CloseHandle(fh)#防止句柄泄漏造成操作系统出现隐性bug(例如文件部分属性无法成功设置之类的
        raise e


if __name__ == '__main__':
    # import time
    # cTime=time.mktime(time.struct_time((2000,1,1,0,0,0,0,0,0)))#创建
    # mTime=time.mktime(time.struct_time((2010,1,1,0,0,0,0,0,0)))#修改
    # aTime=time.mktime(time.struct_time((2020,1,1,0,0,0,0,0,0)))#访问

    import datetime
    cTime=datetime.datetime(2020,1,1,0,0,0).timestamp()#创建
    mTime=datetime.datetime(2021,1,1,0,0,0).timestamp()#修改
    aTime=datetime.datetime(2022,1,1,0,0,0).timestamp()#访问

    path='./Folder'
    path='./Folder/File.txt'
    try:
        r = AlterFileFolderTime(path, cTime, aTime , mTime)
        rst='成功' if r else '失败：路径不存在'
    except Exception as e:
        rst='异常：'+str(e)
    print(f'路径[{path}]的时间修改【{rst}】')
```


<br>

# 说明：
&emsp; 改文件的容易，改目录的让我一顿好找。
&emsp; 首先我找到一份不错的代码[【(博客园)python 修改文件创建、修改、访问时间】](https://www.cnblogs.com/suwanbin/p/12037497.html)，但这份代码只能修改文件的，目录仍然是没法处理。
&emsp; 然后几经搜索，在一个CSDN帖子[【(CSDN)请教各位，如果修改目录的创建时间、修改时间？？】](https://bbs.csdn.net/topics/60511964)中我看到了一位老哥神仙指路：**<font color=#FF0000>CreateFile+SetFileTime，记住，CreateFile也可以打开目录。</font>**
&emsp; 随即我跑去看官方文档[【(MSDN)CreateFile-Directory】](https://learn.microsoft.com/zh-cn/windows/win32/api/fileapi/nf-fileapi-createfilea#Directories)，也证实了那位老哥说的话，而且在``CreateFile``中仅需传入额外的标志位``FILE_FLAG_BACKUP_SEMANTICS``即可打开目录。在经过测试也的确能够使用``CreateFile``打开目录并用``SetFileTime``对其设置时间。

&emsp;时间戳可以通过``datetime.datetime(y,m,d,H,M,S).timestamp()``或者``time.mktime(time.struct_time((y,m,d,H,M,S,0,0,0)))``生成。关于``time``和``datetime``模块的详细用法可以参考本人写的一篇博文：[【Python-time模块和datetime模块的部分函数说明】](https://blog.csdn.net/weixin_44733774/article/details/133475034)(没错，咱自个儿就是引流之主


<br>
<br>


***
# 参考资料：

- python 修改文件创建、修改、访问时间：[(博客园)https://www.cnblogs.com/suwanbin/p/12037497.html](https://www.cnblogs.com/suwanbin/p/12037497.html)
- 关于修改目录时间的问题：[(CSDN)https://bbs.csdn.net/topics/60511964](https://bbs.csdn.net/topics/60511964)
- ``CreateFile``-打开目录需传入标志位``FILE_FLAG_BACKUP_SEMANTICS``[(MSDN)https://learn.microsoft.com/zh-cn/windows/win32/api/fileapi/nf-fileapi-createfilea#Directories](https://learn.microsoft.com/zh-cn/windows/win32/api/fileapi/nf-fileapi-createfilea#Directories)
- ``SetFileTime``：[(MSDN)https://learn.microsoft.com/zh-cn/windows/win32/api/fileapi/nf-fileapi-setfiletime](https://learn.microsoft.com/zh-cn/windows/win32/api/fileapi/nf-fileapi-setfiletime)
- ``pywintypes.Time``：[(pywin32)http://www.markjour.com/docs/pywin32-docs/pywintypes__Time_meth.html](http://www.markjour.com/docs/pywin32-docs/pywintypes__Time_meth.html)

