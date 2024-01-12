说实话还是不太擅长这些异步，弄的头昏昏的。

JavaScript中与异步操作有关的主要有
- ``async``
- ``await``
- ``Promise``

<br>

***

首先先说明一点，浏览器中的js运行是单线程的，也就是没有所谓的``sleep``、``join``之类的玩意儿，或者说如果你硬要“实现”这种功能的话接下来面对的将是页面的无响应假死状态(无法关闭、无法刷新)。例如使用``while``进入死循环判断，主线程将会陷进其中，同时其他的异步操作完全得不到执行权。

因此在js中需要拎清楚的一点就是，js的线程不可受阻，每条语句都是非常丝滑的执行(因为js引擎师傅很忙)。

<br>

有人提到``await``？``await``只能用在``async``异步函数中，受阻的是异步函数，关调用这个异步函数的外部有什么关系，或者说调用这个异步函数时也不会乖乖等待这个异步函数执行完毕，而且，``async``函数返回的是一个``Promise``对象。

再进一步，如若想要阻塞一个``Promise``对象，那么其上下文也处于异步函数之中，因为``await``只能用于``async``异步函数内部。

除了使用``await``获取``Promise``的结果外，还能使用``Promise.then``塞个回调函数，而这本质也是异步。

***

额外的，由于js是单线程，其底层总会是逐份代码段执行，忙得很，就例如正在执行A代码段时，突然``setTimeout``设置的定时结束需要执行B代码段，此时它并不会暂停A代码段扭头执行B代码段，而是先把A代码段彻底跑完才行。到处跑只会让本就忙碌的js引擎师傅再添一把汗。

```html
<script>
	function funcA() {
		document.write(" ")
		for (let i = 0; i < 1000; ++i)
			document.write("A");
	}
	function funcB() {
		document.write(" ")
		for (let i = 0; i < 10; ++i)
			document.write("B");
	}
	setTimeout(funcA, 0);
	setTimeout(funcB, 1);
</script>
```
上面代码在浏览器中的运行结果总是*AAAAAAA....BBBB*，而不是*AAAAAA...BBBB...AAAAA*


# 其他参考：

- 菜鸟教程-Promise：[https://www.runoob.com/js/js-promise.html](https://www.runoob.com/js/js-promise.html)

- MDN-Promise：[https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Promise](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Promise)

- MDN-使用Promise：[https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Guide/Using_promises](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Guide/Using_promises)

- MDN-async函数：[https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Statements/async_function](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Statements/async_function)

- JavaScript - 异步操作和异步传染性：[https://blog.hushes.cn/AsyncInfectivity/](https://blog.hushes.cn/AsyncInfectivity/)

- 理解 JavaScript 的 async/await：[https://segmentfault.com/a/1190000007535316](https://segmentfault.com/a/1190000007535316)
(顺便挂出一只抄袭狗：[https://zhuanlan.zhihu.com/p/172378607](https://zhuanlan.zhihu.com/p/172378607)



