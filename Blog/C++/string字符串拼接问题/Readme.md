
``string``字符串有软拼和硬拼，软拼后接<font color=#FF0000>字符串</font>，硬拼后接<font color=#FF0000>字符</font>，两者效果大不相同。

<br>


***

string并不将``'\0'``作为末尾字符，它作为一个容器并不需要这样的边界量，(而字符数组需要


```cpp
#include<string>
#include<iostream>
using namespace std;

int main() {
	string strA("ABC");
	strA += '\0';
	strA += "123";
	cout << strA<<endl;//输出结果是【ABC 123】，这和印象里的“遇到\0就停止输出”的不一样。
	//因为“遇到\0就停止”是给字符数组用的，'\0'是字符数组的结束符
	cout<<strA.data()<<endl;//这里只会输出【ABC】
	return 0;
}
```

<br>

***

软拼并不会将子字串的``'\0'``加入其中，而硬拼则是无视字符值直接加入，也就是软拼的字串中绝对不会出现``'\0'``字符。

```cpp
#include<string>
#include<iostream>
using namespace std;

int main() {
	string strA;
	strA += "ABC\0ABC";
	strA += "123";
	cout << strA;//输出结果是【ABC123】。软拼接下只会拼接\0之前的字符
	return 0;
}
```



<br>

***

在不进行判断就将字符``'\0'``硬拼到字符串后面时将会导致许多问题，最常见的便是字符串判等失效(如果使用``strcmp``判断字符数组那将判断成功)，这在字典集合等容器中会造成不小的麻烦




```cpp
#include<string>
#include<iostream>
using namespace std;

int main() {
	string strA;
	string strB;
	strA += '\0';
	strB += "\0";
	if (strA == strB)//硬拼的strA中有个'\0'字符而软拼的strB没有，因此失败
		cout << "相等" << endl;//实际上这句是绝对不会命中的
		//可以在debug里头查看strA和strB的内容
	return 0;
}
```


```cpp
#include<string>
#include<iostream>
using namespace std;

int main() {
	string strA;
	strA += '\0';
	strA += "123";
	if (strcmp(strA.data(), "")==0)//strA.data()是string转字符数组char*
		cout << "相等" << endl;
	return 0;
}
```


<br>

***

``to_string``该函数是给数值转字符串用的，不是字符转字符串

```cpp
#include<string>
#include<iostream>
using namespace std;

int main() {
	string strA(to_string('A'));
	cout << strA << endl;//输出结果是【65】，对应'A'的ASCII值
	return 0;
}
```


<br>

***

字符连接到字符串时的正确做法
```cpp
#include<string>
#include<iostream>
using namespace std;

int main() {
	char ch = '\0';
	string strA;

	strA += string(string("\0")+ch);//由于编译器的优化，该语句会等效于strA+=ch
	cout << strA.length() << endl;//从而导致'\0'被预期之外加入其中，导致strA长度为1
	
	strA.clear();
	if(ch)strA += ch;//最好的做法就是先判断ch字符值是否为0然后再加入到字符串
	cout << strA.length() << endl;//长度为0
	return 0;
}

```

