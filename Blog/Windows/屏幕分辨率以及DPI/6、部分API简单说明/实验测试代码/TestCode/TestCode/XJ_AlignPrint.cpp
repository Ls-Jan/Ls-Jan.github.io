
#include<stdio.h>
#include <string.h>  
#include <stdarg.h>

/// �ú�������Ϊprintf_s�ĸİ棬�����������������ڿ��ƶ��������
/// ����ֵΪʵ��������ִ����ȣ�
///- widthΪ��������Ŀ�ȣ�
///- align������ȡֵ����0�Ĵ�С��ϵ��Ϊ����������ֱ��Ӧ�����ң�
///- fmt�Լ�����Ĳ�����������printf_sһ�£�
int XJ_AlignPrint(int width, int align, const char* fmt, ...) {
	const int bufSize = 256;
	char text[bufSize];
	va_list args;
	va_start(args, fmt);
	vsprintf_s(text, fmt, args);
	va_end(args);

	int w = strnlen_s(text, bufSize);
	int margin[2] = { 0,0 };
	if (w < width) {
		w = width - w;
		if (align < 0) {
			margin[1] = w;
		}
		else if (align == 0) {
			margin[0] = w >> 1;
			margin[1] = w - margin[0];
		}
		else {
			margin[0] = w;
		}
	}

	char spaceL[bufSize];
	char spaceR[bufSize];
	memset(spaceL, 0, bufSize);
	memset(spaceR, 0, bufSize);
	memset(spaceL, ' ', margin[0]);
	memset(spaceR, ' ', margin[1]);
	printf_s("%s%s%s", spaceL, text, spaceR);
	return w > width ? w : width;

}
