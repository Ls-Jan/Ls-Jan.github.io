

//ʹ�ñ���ֶν������
//��ʵ��printf_s�����ǵ�����WriteFile���winAPI

#include<stdio.h>
#include<locale>
#include<windows.h>

int main() {
	char code[] = {
		0xE5,0xA3,0xB9,//UTF-8��Ҽ
		0xE8,0xB4,0xB0,//UTF-8����
		0xE5,0x8F,0x81,//UTF-8����
		0,0,//��ֹ��
	};
	SetConsoleOutputCP(65001);
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), code, sizeof(code), NULL, NULL);

	return 0;
}





