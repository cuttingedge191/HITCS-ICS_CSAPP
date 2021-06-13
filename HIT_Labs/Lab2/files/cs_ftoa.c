#include <stdio.h>
#include <stdlib.h>

#define MAX 50

char* cs_ftoa(float x)
{
    char *res = (char*)calloc(MAX, sizeof(char));
    char buf[MAX];
    int count = 0;
    int tmp;
    int ptr = 0;
    int keep = 0;
    __int128_t z;
    double f;
    if (x < 0)
    {
        x = -x;
        *res = '-';
        ++ptr;
    }
    z = (__int128_t)x;
    f = (double)x - (double)z;
    if (x = 0)
    {
        *res = '0';
        ++ptr;
    }
    while (z)
    {
        tmp = z % 10;
        z /= 10;
        buf[count++] = '0' + tmp;
    }
    while (count)
    {
        *(res + ptr) = buf[count - 1];
        --count;
        ++ptr;
    }
    *(res + ptr) = '.';
    ++ptr;
    if (f == 0)
    {
        for (int i = 1; i <= 6; ++i)
        {
            *(res + ptr) = '0';
            ++ptr;
        }
    }
    while (ptr < MAX - 1)
    {
        f *= 10;
        tmp = (int)f;
        f -= (double)tmp;
        *(res + ptr) = '0' + tmp;
        ++ptr;
        ++keep;
        if (keep == 6)
        	break;
    }
    *(res + ptr) = '\0';
    return res;
}

int main(void)
{
    char* res;
    int* test;
    float input;
    test = (int*)&input;
    printf("输入一个浮点数:\n");
    scanf(" %f", &input);
    if (((*test) & 0x7f800000) == 0x7f800000)
    {
        if ((*test) & 0x7fffff)
        {
            printf("转换后的字符串为：NaN\n");
            return 0;
        }
        printf("转换后的字符串为：");
        if ((*test) & 0x80000000)
            printf("NEG_");
        else
            printf("POS_");
        printf("INFINITY\n");
        return 0;
    }
    res = cs_ftoa(input);
    printf("转换后的字符串为：%s\n", res);
    return 0;
}
