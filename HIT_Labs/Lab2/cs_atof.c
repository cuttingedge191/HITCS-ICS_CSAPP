#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

float cs_atof(char* str)
{
    float res = 0;
    float digit = 0.1;
    float tmp;
    int isPos = (*str != '-');
    int ptr = !isPos;
    while (*(str + ptr) >= '0' && *(str + ptr) <= '9')
    {
        res = (*(str + ptr) - '0') + 10 * res;
        ++ptr;
    }
    ++ptr;
    while (*(str + ptr) >= '0' && *(str + ptr) <= '9')
    {
        tmp = (*(str + ptr) - '0') * digit;
        digit /= 10;
        res += tmp;
        ++ptr;
    }
    return isPos ? res : -res;
}

int main(void)
{
    char str[MAX];
    char *test;
    float res;
    int bias = 0;
    printf("输入字符串：\n");
    test = fgets(str, MAX - 1, stdin);
    if (!test)
    {
        printf("读取字符串错误！\n");
        exit(0);
    }
    while (*(str + bias) == ' ')
        ++bias;  //去除前导空格
    res = cs_atof(str + bias);
    printf("转换后的浮点数为：%f\n", res);
    return 0;
}