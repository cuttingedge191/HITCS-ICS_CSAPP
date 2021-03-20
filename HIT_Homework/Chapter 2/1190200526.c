/*
* 计算机系统 第二章作业
* 学号：1190200526
* 姓名：沈城有
* 题目：2.59, 2.63, 2.67, 2.71, 2.75, 2.79, 2.83, [2.86, 2.90, 2.94]???
*/

#include <stdio.h>
#include <stdlib.h>

//2.59题：
int Q_2_59(int x, int y)
{
    int exp = (x & 0x000000FF) | (y & 0xFFFFFF00);
    return exp;
}

//2.63题：
unsigned srl(unsigned x, int k)
{
    /* Perform shift arithmetically */
    unsigned xsra = (int) x >> k;
    unsigned adj = ~(-1 << (8 * sizeof(int) - k));
    return xsra & adj;
}

int sra(int x, int k)
{
    /* Perform shift logically */
    int xsrl = (unsigned) x >> k;
    int sign = x & (1 << (8 * sizeof(int) - 1));
    int adj = -1 << (8 * sizeof(int) - k);
    if (sign)
        xsrl = xsrl | adj;
    return xsrl;
}

/*2.67题：
A.使用了未定义的行为：32位机器上没有定义“<<32”这一操作。
*/
//B.至少32位
int int_size_is_32_b(void)
{
    int set_msb = 1 << 31;
    int beyond_msb = 2 << 31;
    return set_msb && (!beyond_msb);
}
//C.至少16位
int int_size_is_32_c(void)
{
    int tmp = 1 << 15;
    int set_msb;
    int beyond_msb;
    tmp = tmp << 15;
    set_msb = tmp << 1;
    beyond_msb = tmp << 2;
    return set_msb && (!beyond_msb);
}

/*2.71题：
A.函数实现了抽取指定字节，但没有进行符号扩展。
*/
//B.函数正确实现
typedef unsigned packed_t;
int xbyte(packed_t word, int bytenum)
{
    int mov = (3 - bytenum) << 3;
    int byte = word << mov;
    return byte >> 24;
}

//2.75题：
int signed_high_prod(int x, int y)
{
    /*返回有符号数相乘结果的高w位，
    题目描述此函数为要调用的库函数，
    故此处不具体实现，仅用于避免报错*/
    return 0xFF;
}

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
    int w = (sizeof(int)) << 3;
    return signed_high_prod(x, y) + (x >> (w - 1)) * y + (y >> (w - 1)) * x;
}

//2.79题：
int mul3div4(int x)
{
    int mul3 = (x << 1) + x;
    int div4 = mul3 >> 2;
    return div4;
}

/*2.83题：
A.
B.
*/




