

//事实上字串"壹贰叁"有着其等效替代
//调用setlocale设置程序字符集

#include<stdio.h>
#include<locale>

int main() {
	char code[] = {
		0xE5,0xA3,0xB9,//UTF-8：壹
		0xE8,0xB4,0xB0,//UTF-8：贰
		0xE5,0x8F,0x81,//UTF-8：叁
		0,0,//终止符
	};
	setlocale(LC_ALL, ".65001");
	printf_s(code);
	return 0;
}





