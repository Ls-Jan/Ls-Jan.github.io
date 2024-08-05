
#include<stdio.h>
#include<locale>
int main() {
    setlocale(LC_ALL, ".utf-8");//文件使用UTF-8编码，因此CRT区域语言也要跟着设置，否则会出现乱码
    printf_s("%s\n", "一二三");


    char buf[32] = "";
    sprintf_s(buf, "%s", "𬌗");//对于生僻字来说控制台是无法显示的，因此以十六进制输出这个生僻字的utf-8编码
    for (auto i = 0; buf[i]; ++i) {
        printf_s("%02X ", (unsigned char)buf[i]);
    }
    printf_s("\n");

    return 0;
}






