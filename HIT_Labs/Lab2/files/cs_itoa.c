#include <stdio.h>
#include <stdlib.h>

#define MAX 12

char* cs_itoa(int x)
{
    char *res = (char*)calloc(MAX, sizeof(char));
    char buf[MAX];
    int ptr = 0;
    int tmp;
    int count = 0;
    if (x == 0)
    {
        *res = '0';
        ++ptr;
    }
    else if (x < 0)
    {
        x = -x;
        *res = '-';
        ++ptr;
    }
    while (x)
    {
        tmp = x % 10;
        x /= 10;
        buf[count++] = '0' + tmp;
    }
    while (count)
    {
        *(res + ptr) = buf[count - 1];
        --count;
        ++ptr;
    }
    *(res + ptr) = '\0';
    return res;
}

int main(void)
{
    char* res;
    char min[12] = "-2147483648";
    int input;
    printf("输入一个整数:\n");
    scanf(" %d", &input);
    if (input == -2147483648)
    {
        printf("转换后的字符串为：%s\n", min);
        return 0;
    }
    res = cs_itoa(input);
    printf("转换后的字符串为：%s\n", res);
}