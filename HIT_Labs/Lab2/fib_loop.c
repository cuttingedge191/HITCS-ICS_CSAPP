#include <stdio.h>
#define DataType long //便于修改数据类型

/*fib_loop函数中加入了溢出检测，
使用较大的n调用此函数可以测试溢出的n*/

DataType fib_loop(int n)
{
    DataType res = 1;
    DataType res_1 = 1;
    DataType res_2 = 0;
    DataType test = 0 - 1;
    int tmp = n;
    if (n == 0)
        res = 0;
    while (n >= 2)
    {
        res = res_1 + res_2;
        if (res < res_1 || res < res_2)
        {
            printf("%d字节",(int)sizeof(DataType));
            if (test < 0)
                printf("有符号数");
            else
                printf("无符号数");
            printf("溢出于n = %d\n", tmp - n + 2);
            printf("运算中止，下一行输出结果为溢出结果\n");
            return res;
        }
        res_2 = res_1;
        res_1 = res;
        --n;
    }
    return res;
}

int main(void)
{
    int n;
    DataType res;
    DataType test = 0 - 1;
    printf("请输入n:");
    scanf(" %d", &n);
    res = fib_loop(n);
    printf("n = %d时", n);
    if (test > 0)
    {
        printf(" unsigned ");
        if (sizeof(DataType) == 4)
            printf("int类型结果为:%u\n", res);
        else if (sizeof(DataType) == 8)
            printf("long类型结果为:%lu\n", res);
    }
    else if (test < 0)
    {
        if (sizeof(DataType) == 4)
            printf("int类型结果为:%d\n", res);
        else if (sizeof(DataType) == 8)
            printf("long类型结果为:%ld\n", res);
    }
    return 0;
}