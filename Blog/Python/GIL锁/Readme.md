这里就不解释了，因为有人写了个更好的说明文章：[一文详解 Python GIL 设计](https://zhuanlan.zhihu.com/p/363040263)

- 大概意思是，GIL锁会让Python的多线程表现为单线程，或者说就是Python的多线程只是在用一个CPU核心在干活，这对于计算密集型的脚本来说是个灾难，即多线程的表现和单线程大差不差；
- 解决方法通常是，使用多线程，例如使用``multiprocessing``模块中的``Process``类；
- 就像线程有线程锁，进程自然也会有相应的锁以实现消息同步，至于如何消息同步本篇就不去讨论(人话就是懒得去试)；
- Python的多进程表现宛如多线程是让我有点意想不到的，因为受苦Windows编程，每逢提起多进程的首先反应是“使用``OpenProcess``打开一个二进制程序文件”，而不是“使用``XXX``函数/模块将某函数丢进里头执行”，或许linux的``fork``和它有相似之处？也就是代码中不需要明写运行某个外部文件就能开启一个新进程；

```py
import time
from threading import Thread
from multiprocessing import Process
#与GIL锁相关：https://zhuanlan.zhihu.com/p/363040263

def Countdown(n):
	while n>0:
		n -= 1

def Start_SingleThread(count:int,threadCount:int=1):
	start=time.time()
	Countdown(count)
	return time.time()-start

def Start_MultiThread(count:int,threadCount:int=2):
	start=time.time()
	lst=[]
	for i in range(threadCount):
		th=Thread(target=Countdown, args=(count//threadCount,))
		lst.append(th)
	for th in lst:
		th.start()
	for th in lst:
		th.join()
	return time.time()-start

def Start_MultiProcess(count:int,processCount:int=2):
	start=time.time()
	lst=[]
	for i in range(processCount):
		proc=Process(target=Countdown, args=(count//processCount,))
		lst.append(proc)
	for proc in lst:
		proc.start()
	for proc in lst:
		proc.join()
	# for proc in lst:#没错，Process对象有kill操作的(不像Thread只能干等线程主动退出)，只不过没去查也没去试验这个API的利弊
	# 	proc.kill()
	return time.time()-start

if __name__ == "__main__": 
	test={
		'单线程':Start_SingleThread,
		'多线程':Start_MultiThread,
		'多进程':Start_MultiProcess,
  	}
	count=50000000
	for type,func in test.items():
		cost=func(count,5)
		print(f'{type}耗时：{round(cost,3)}s')
```

![运行结果](./Preview-1.png)


***

### 其他参考：
单纯懒得看只不过又怕哪一天要用的时候翻不到，索性记录一下。
- [[python/多进程]确保主进程被外部终止时，子进程正常退出](https://zhuanlan.zhihu.com/p/666769349)
- [一篇文章搞定Python多进程(全)](https://zhuanlan.zhihu.com/p/64702600)




