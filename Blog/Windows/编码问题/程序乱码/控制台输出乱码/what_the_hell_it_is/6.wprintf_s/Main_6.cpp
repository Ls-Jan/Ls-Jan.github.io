

//̽��wprintf_s

#include<stdio.h>
#include<locale>
#include<windows.h>

int main() {
	char code[] = {
		0x6E,0x30,//UTF-16LE����
		0,0,//��ֹ��
	};
	wprintf_s(L">>>%s\n", (wchar_t*)(code));
	setlocale(LC_CTYPE,".932");
	wprintf_s(L">>>%s\n",(wchar_t*)(code));
	setlocale(LC_CTYPE, ".936");
	wprintf_s(L">>>%s\n", (wchar_t*)(code));
	setlocale(LC_CTYPE,".949");
	wprintf_s(L">>>%s\n",(wchar_t*)(code));
	setlocale(LC_CTYPE,".950");
	wprintf_s(L">>>%s\n",(wchar_t*)(code));
	setlocale(LC_CTYPE,".65001");
	wprintf_s(L">>>%s\n",(wchar_t*)(code));
	return 0;
}





