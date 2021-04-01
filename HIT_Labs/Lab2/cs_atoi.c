#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int cs_atoi(char* str)
{
    int res = 0;
    int isPos = (str[0] != '-');
    int i = !isPos;
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        ++i;
    }
    return isPos ? res : -res;
}

int main(void)
{
    char str[MAX];
    char *test;
    int res;
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
    res = cs_atoi(str + bias);
    printf("转换后的整数为：%d\n", res);
    return 0;
}