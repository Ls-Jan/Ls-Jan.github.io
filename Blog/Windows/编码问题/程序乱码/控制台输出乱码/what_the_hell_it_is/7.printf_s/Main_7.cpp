

//ʹ�ñ���ֶν������
//C�������ԣ���setlocale(LC_CTYPE, "C")���������µ�printf_s��������ִ����ж���ı��ת����
//˵ʵ��������Ҫ����Ч�������Ǹ��Ҹ��ְ��̰����ַ�

#include<stdio.h>
#include<locale>
#include<windows.h>

int main() {
	char tx1[] = "\xE3\x81\xAE";//UTF-8����
	char tx2[] = "\x82\xCC";//���ģ���
	char tx3[] = "\xA4\xCE";//GB2312����

	setlocale(LC_CTYPE, "C");
	SetConsoleOutputCP(65001); // UTF - 8
	printf_s("%s\n", tx1);
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), tx1, sizeof(tx1), NULL, NULL);
	printf_s("\n");

	SetConsoleOutputCP(932);//����
	printf_s("%s\n", "\x82\xCC");
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), tx2, sizeof(tx2), NULL, NULL);
	printf_s("\n");

	SetConsoleOutputCP(936);//GB2312
	printf_s("%s\n", "\xA4\xCE");
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), tx3, sizeof(tx3), NULL, NULL);
	printf_s("\n");

	return 0;
}





