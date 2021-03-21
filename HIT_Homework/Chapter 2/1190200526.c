/*
* 计算机系统 第二章作业
* 学号：1190200526
* 姓名：沈城有
* 题目：2.59, 2.63, 2.67, 2.71, 2.75, 2.79, 2.83, 2.87, 2.91, 2.95
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
A.使用了C语言未定义的行为：32位机器上没有定义“<<32”这一操作。
*/
//B.至少32位
int int_size_is_32_b(void)
{
    int set_msb = 1 << 31;
    int beyond_msb = 1 << 16;
    beyond_msb <<= 16;
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
    int div4 = (mul3 + 3) >> 2;
    return div4;
}

/*2.83题：
A.令x为无穷串的值，可得x*(2^k) = Y+x，故x = Y/(2^k-1)
B.(a)101 = 5/7  （b）0110 = 2/5  （c）010011 = 19/63
*/

/*2.87题：
描述                       Hex        M         E      V               D
-0                        8000    0            -14    -0              -0.0
最小的>2的值               7001    1025/1024    1      1025*2^(-9)     2.001953
512                       6000    1            9      512             512.0
最大的非规格化数           03FF    1023/1024    -14    1023*2^(-24)    0.000061   
-inf                      FC00    --           --     -inf            -inf
十六进制表示为3BB0的数?    3BB0    123/64       -1     123*2^(-7)      0.960938
*/

/*2.91题：
0x40490FDB -> 0 10000000 10010010000111111011011 
A.11.0010010000111111011011，即3.1415927410125732；
B.11.001001001...(y = 001)；
C.两种表示从二进制小数点后第9位开始不同。
*/

//2.95题：
/* Access bit-level representation floating-point number */
typedef unsigned float_bits;
/* Compute 0.5*f.  If f is NaN, then return f. */
float_bits float_half(float_bits f)
{
    unsigned sign = f & 0x80000000;
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    //NaN
    if (exp == 0xFF && frac != 0)
        return f;
    //0
    if (exp == 0 && frac == 0)
        return 0;
    //infinity
    if (exp == 0xFF && frac == 0)
        return f;
    //规格->非规格
    if (exp == 0x01) {
        --exp;
        if (frac == 0)
            frac = 0x40000000;
        else {
            frac += 0x800000;
            frac /= 2;
        }
    }
    //非规格->非规格
    else if (exp == 0)
        frac = frac >> 1;
    //规格->规格
    else if (exp)
        --exp;
    return sign + (exp << 23) + frac;
}

//测试用主函数
int main(void)
{
    int x, y, result;
    float f;
    printf("----------Ch2 Homework Test----------\n");

    printf("2.59:\n");
    printf("Input x, y:");
    scanf("%d %d", &x, &y);
    result = Q_2_59(x, y);
    printf("result:%X\n", result);

    printf("2.63:\n");
    printf("Input x, k:");
    scanf("%d %d", &x, &y);
    result = srl((unsigned)x, y);
    printf("srl result:%X\n", result);
    result = sra(x, y);
    printf("sra result:%X\n", result);

    printf("2.67:\n");
    printf("2.67 b result:%d\n", int_size_is_32_b());
    printf("2.67 c result:%d\n", int_size_is_32_c());

    printf("2.71:\n");
    printf("Input x, bytenum:");
    scanf("%u %d", &x, &y);
    result = xbyte((packed_t)x, y);
    printf("result:%X\n", result);

    printf("2.75:\n");

    printf("2.79:\n");
    printf("Input x:");
    scanf("%d", &x);
    result = mul3div4(x);
    printf("result:%d\n", result);

    printf("2.95:\n");
    printf("Input f:");
    scanf("%f", &f);
    f = float_half((float_bits)f);
    printf("result:%f", f);

    return 0;
}
