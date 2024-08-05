

//使用别的手段进行输出
//事实上printf_s最终是调用了WriteFile这个winAPI

#include<stdio.h>
#include<locale>
#include<windows.h>

int main() {
	char code[] = {
		0xE5,0xA3,0xB9,//UTF-8：壹
		0xE8,0xB4,0xB0,//UTF-8：贰
		0xE5,0x8F,0x81,//UTF-8：叁
		0,0,//终止符
	};
	SetConsoleOutputCP(65001);
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), code, sizeof(code), NULL, NULL);

	return 0;
}





