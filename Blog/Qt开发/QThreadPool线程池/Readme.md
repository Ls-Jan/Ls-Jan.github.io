 ``QThreadPool``线程池，只需向里头添加``QRunnable``任务(需继承并重写``QRunnable.run``)，池子将会不断地从中取出任务并运行，无需关心其中的实现细节；

- ``QThreadPool.setMaxThreadCount(int)``：设置最大线程数；
- ``QThreadPool.tryTake(QRunnable)``：尝试移除任务；
- ``QThreadPool.start(QRunnable)``：将任务加进池中；
- ``QThreadPool.clear()``：清空池子(不包括正运行中的任务)；
- ``QThreadPool.waitForDone()``：等待池子完成所有任务；



