

//�ڵ���setlocale������ŵ���SetConsoleOutputCP��printf_s��ɵ�Ӱ��
//Ҳ���Ǵ���ҳ����

#include<stdio.h>
#include<locale>
#include<windows.h>

int main() {
	char code[]= "\xE3\x81\xAE";//UTF-8����

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





