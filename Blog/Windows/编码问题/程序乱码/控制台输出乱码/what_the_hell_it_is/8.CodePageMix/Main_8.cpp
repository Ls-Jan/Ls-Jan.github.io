

//在调用setlocale后紧接着调用SetConsoleOutputCP对printf_s造成的影响
//也就是代码页混用

#include<stdio.h>
#include<locale>
#include<windows.h>

int main() {
	char code[]= "\xE3\x81\xAE";//UTF-8：の

	int codePage[] = { 932,936,949,950,65001 };
	for (auto i = 0; i < sizeof(codePage) / sizeof(int); ++i) {
		for (auto j = 0; j < sizeof(codePage) / sizeof(int); ++j) {
			char lc[32] = ".";
			_itoa_s(codePage[i], lc + 1, 32 - 1, 10);
			setlocale(LC_CTYPE, lc);
			SetConsoleOutputCP(codePage[j]);
			printf_s("%6d>>><chcp:%6d> %s \n", codePage[i], codePage[j], code);
		}
		printf_s("\n\n");
	}

	return 0;
}





