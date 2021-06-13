#include <stdio.h>
#include <stdlib.h>
#define MAX 1024

int utf8len(char* str)
{
    int len = 0;
    int maxi = 0;
    unsigned char *ptr = (unsigned char*)str;
    while (*(ptr + maxi) != '\0')
        ++maxi;
    for (int i = 0; i < maxi; )
    {
        if ((*(ptr + i) & 0x80) == 0)
        {
            i += 1;
            ++len;
        }
        else if ((*(ptr + i) & 0xE0) == 0xC0)
        {
            i += 2;
            ++len;
        }
        else if ((*(ptr + i) & 0xF0) == 0xE0)
        {
            i += 3;
            ++len;
        }
        else if ((*(ptr + i) & 0xF8) == 0xF0)
        {
            i += 4;
            ++len;
        }
        else
        {
            printf("编码错误！\n");
            return 0;
        }
    }
    return len - 1;  //结尾的回车减去
}

int main(void)
{
    char str[MAX];
    char *test;
    printf("输入字符串：\n");
    test = fgets(str, MAX - 1, stdin);
    if (!test)
    {
        printf("读取字符串错误！\n");
        exit(0);
    }
    printf("字符个数：%d\n", utf8len(str));
    return 0;
}