


原本实现md的html渲染，要去处理资源文件的相对路径问题，于是向v-html中额外插入``<base src="./XXX/">``指定根路径，结果在八竿子打不着的地方出现了fetch异常，几经查找也无法确定错误根源，只能认为是v-html的漏洞(或者说是innerHtml)造成的

通过``<iframe srcdoc>``可以解决v-html嵌入而造成的``<base scr>``标签破坏根路径的问题，但一想到兼容性问题(IE浏览器：有人叫我？)就还是不太想弄，宁可把md中涉及到相对路径的资源全改成绝对路径也懒得再趟这浑水。

很多文章甚至是在Vue、ElementPlus官网中都提及使用内嵌html的危险性(说明漏洞很多)



