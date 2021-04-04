#include <stdio.h>
#define DataType int //便于修改数据类型

/*递归算法增加了内存的不必要开销，可能造成栈溢出，
同时可能产生过多冗余运算，浪费时间，
不适合进行较大n的运算，此处也未进行溢出检测*/

DataType fib_dg(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fib_dg(n - 1) + fib_dg(n - 2);
}

int main(void)
{
    int n;
    DataType res = 0 - 1;
    printf("请输入n:");
    scanf("%d", &n);
    res = fib_dg(n);
    printf("n = %d时", n);
    if (res > 0)
    {
        printf(" unsigned ");
        if (sizeof(DataType) == 4)
            printf("int类型结果为:%u\n", res);
        else if (sizeof(DataType) == 8)
            printf("long类型结果为:%lu\n", res);
    }
    else if (res < 0)
    {
        if (sizeof(DataType) == 4)
            printf("int类型结果为:%d\n", res);
        else if (sizeof(DataType) == 8)
            printf("long类型结果为:%ld\n", res);
    }
    return 0;
}