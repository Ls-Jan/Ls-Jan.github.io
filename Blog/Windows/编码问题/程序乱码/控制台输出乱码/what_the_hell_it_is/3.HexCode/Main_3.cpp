

//��ʵ���ִ�"Ҽ����"�������Ч���


#include<stdio.h>

int main() {
	char code[] = {
		0xE5,0xA3,0xB9,//UTF-8��Ҽ
		0xE8,0xB4,0xB0,//UTF-8����
		0xE5,0x8F,0x81,//UTF-8����
		0,0,//��ֹ��
	};
	printf_s("%s\n", code);
	printf_s("%s\n", "\xE5\xA3\xB9\xE8\xB4\xB0\xE5\x8F\x81");
	return 0;
}





