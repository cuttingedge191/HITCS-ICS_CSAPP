#include <stdio.h>
#include <stdlib.h>
#define MAX 20

float cs_atof(char* str)
{
    
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
    while (*str == ' ')
        ++bias;  //去除前导空格
    res = cs_atof(str + bias);
    printf("转换后的浮点数为：%f\n", res);
    return 0;
}