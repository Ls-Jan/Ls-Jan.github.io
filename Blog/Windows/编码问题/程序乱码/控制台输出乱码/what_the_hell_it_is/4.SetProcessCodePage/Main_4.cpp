

//��ʵ���ִ�"Ҽ����"�������Ч���
//����setlocale���ó����ַ���

#include<stdio.h>
#include<locale>

int main() {
	char code[] = {
		0xE5,0xA3,0xB9,//UTF-8��Ҽ
		0xE8,0xB4,0xB0,//UTF-8����
		0xE5,0x8F,0x81,//UTF-8����
		0,0,//��ֹ��
	};
	setlocale(LC_ALL, ".65001");
	printf_s(code);
	return 0;
}





