

//使用别的手段进行输出
//C区域语言，即setlocale(LC_CTYPE, "C")，此设置下的printf_s并不会对字串进行额外的编号转换，
//说实话就是需要这种效果而不是给我各种暗吞暗改字符

#include<stdio.h>
#include<locale>
#include<windows.h>

int main() {
	char tx1[] = "\xE3\x81\xAE";//UTF-8：の
	char tx2[] = "\x82\xCC";//日文：の
	char tx3[] = "\xA4\xCE";//GB2312：の

	setlocale(LC_CTYPE, "C");
	SetConsoleOutputCP(65001); // UTF - 8
	printf_s("%s\n", tx1);
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), tx1, sizeof(tx1), NULL, NULL);
	printf_s("\n");

	SetConsoleOutputCP(932);//日文
	printf_s("%s\n", "\x82\xCC");
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), tx2, sizeof(tx2), NULL, NULL);
	printf_s("\n");

	SetConsoleOutputCP(936);//GB2312
	printf_s("%s\n", "\xA4\xCE");
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), tx3, sizeof(tx3), NULL, NULL);
	printf_s("\n");

	return 0;
}





