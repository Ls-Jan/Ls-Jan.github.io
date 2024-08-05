
说实话这个内容写到一半我就已经不想写下去了，网上那么多资料，随便搜都有十几条结果，看都看不完。
总结也没什么作用，反倒不如直接贴链接。

事实上心中一直有个疑问，既然已经出了个Unicode万国码，国家的字符集是否还有发展修订的必要？或者说国标字符集具体会用在哪些场合？





<br>
<br>
<br>
<br>

# GB2312：
- 使用单双字节进行编码；
- 双字节字符的高低字节取值范围依次是0xA1\~0xFE和0xA0\~0xFF，简单理解就是这俩字节的值均要求大于127；
- 向下兼容ASCII码；
- 这个字符集收录了6763个汉字；
- 发布于1980年，在目前来看是一个非常落后的字符集；

# BIG5：
- 大五码，湾湾使用的繁体字字符集；
- 使用单双字节进行编码；
- 向下兼容ASCII码；
- 与GB2312没有丝毫关系，它们互不兼容，人话就是大陆的软件无法在湾湾那边使用，反之同理；
- 高字节使用0x81\~0xFE，低字节使用0x40\~0x7E和0xA1\~0xFE；
- 收录了13053个字符；
- 发布于1984年，不是国家标准(赶紧收复台湾)，在目前来看也是一个非常古老的字符集；

# GBK：
- 依然是单双字节进行编码；
- 向下兼容GB2312这个旧字符集，或者说GBK就是GB2312的扩展；
- 在GB2312的基础上，低字节的取值不再限制为0xA0\~0xFF，而是0x40\~0xFF，因此容量大大提升；
- 收录了21886个字符，包括湾湾用的BIG5繁体字字符以及其他一些字符；
- 发布于1995年，也是个老得不行的标准；

# GB18030:
- 使用单、双、四字节进行编码；
- 在GBK的基础上，进一步的扩展，使用了GBK第二字节中未使用的0x30\~0x39作为四字节字符的判断依据(也就是第二字节如果取值为0x30\~0x39那么继续读取两个字节作为四字节字符)。从这一步就已经能感受到国家对字符集的完善是多么的稳健了，不会把剩余的编码全部用完，总会留下一部分预防未来可能出现的扩展问题；
- 目前为止(2022版)收录了近9万个字符，并且仍在不断丰富中，国家提供渠道欢迎更多人将信息生活中无法使用的生僻字拍照上传；
- 这个标准自2000年发布，并在2005年和2022年进行了更新；

# Unicode：
请参考以下链接(都是随手搜的)：
- 彻底弄懂 Unicode 编码：[https://liyucang-git.github.io/2019/06/17/彻底弄懂Unicode编码/](https://liyucang-git.github.io/2019/06/17/彻底弄懂Unicode编码/)
- Unicode详解：[https://www.jianshu.com/p/07b578adfbf8](https://www.jianshu.com/p/07b578adfbf8)
- Unicode、UTF-8、UTF-16 终于懂了：[https://zhuanlan.zhihu.com/p/427488961](https://zhuanlan.zhihu.com/p/427488961)
- UTF-16BE、UTF-16LE、UTF-16 三者之间的区别：[https://blog.csdn.net/QQxiaoqiang1573/article/details/84937863](https://blog.csdn.net/QQxiaoqiang1573/article/details/84937863)
- Unicode编码规则：[https://www.toolhelper.cn/Encoding/Unicode](https://www.toolhelper.cn/Encoding/Unicode)
- 字符编码技术专题(一)：快速理解ASCII、Unicode、GBK和UTF-8：[https://segmentfault.com/a/1190000044266299](https://segmentfault.com/a/1190000044266299)


<br>


# 拓展内容：
- 恼人的"龙天"(䶮)--谈谈从GBK转到GB18030的特殊情况：[https://www.darkathena.top/archives/longtian-yan-encoding-gbk-gb18030](https://www.darkathena.top/archives/longtian-yan-encoding-gbk-gb18030)
- 一个名字叫“䶮”的人的苦恼：开不了银行账户，用不了微信、支付宝：[https://mp.weixin.qq.com/s/1q8Ag21UrEDgRwkqKV41pQ](https://mp.weixin.qq.com/s/1q8Ag21UrEDgRwkqKV41pQ)
- 一图读懂｜GB 18030-2022《信息技术 中文编码字符集》:[https://www.samr.gov.cn/xw/tp/art/2023/art_851ce0ae0b3b4926942b0fb200c749cb.html](https://www.samr.gov.cn/xw/tp/art/2023/art_851ce0ae0b3b4926942b0fb200c749cb.html)
- 国标GB18030-2022：[https://openstd.samr.gov.cn/bzgk/gb/newGbInfo?hcno=A1931A578FE14957104988029B0833D3](https://openstd.samr.gov.cn/bzgk/gb/newGbInfo?hcno=A1931A578FE14957104988029B0833D3)

<br>


# 参考：
- 锤子在线工具网——GBK编码表：[https://www.toolhelper.cn/Encoding/GBK](https://www.toolhelper.cn/Encoding/GBK)
- 锤子在线工具网——GB2312编码表：[https://www.toolhelper.cn/Encoding/GB2312](https://www.toolhelper.cn/Encoding/GB2312)
- 锤子在线工具网——GB18030编码表：[https://www.toolhelper.cn/Encoding/GB18030](https://www.toolhelper.cn/Encoding/GB18030)
- 千千秀字——GB18030编码：[https://www.qqxiuzi.cn/zh/hanzi-gb18030-bianma.php](https://www.qqxiuzi.cn/zh/hanzi-gb18030-bianma.php)


