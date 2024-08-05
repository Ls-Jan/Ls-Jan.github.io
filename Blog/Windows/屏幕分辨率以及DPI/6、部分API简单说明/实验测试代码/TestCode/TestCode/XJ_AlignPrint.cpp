
#include<stdio.h>
#include <string.h>  
#include <stdarg.h>

/// 该函数可视为printf_s的改版，增加了两个参数用于控制对齐输出。
/// 返回值为实际输出的字串长度；
///- width为数据输出的宽度；
///- align有三种取值，与0的大小关系分为三种情况，分别对应左中右；
///- fmt以及后面的不定长参数与printf_s一致；
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
