/*
* 计算机系统 第三章作业
* 学号：1190200526
* 姓名：沈城有
* 题目：3.59, 3.61, 3.63, 3.65, 3.67, 3.69, 3.71
*/

#include <stdio.h>
#include <stdlib.h>

/*3.59题：
【分析】
x = (2 ^ 64) * x_h + x_l，
y = (2 ^ 64) * y_h + y_l，
其中x_h，y_h其实是两个64位数符号位的扩展。
则 x * y = (2 ^ 128) * (x_h * y_h) + (2 ^ 64) * (x_h * y_l) + (2 ^ 64) * (x_l * y_h) + (x_l * y_l)。
而 128位乘积可以写成p = (2^64) * p_h + p_l，
故 p_h = (2 ^ 64) * (x_h * y_h) + (x_h * y_l) + (x_l * y_h)，而(2 ^ 64) * (x_h * y_h)溢出或为0，不影响最终结果。
最终得：
   p_h = x_h * y_l + x_l * y_h + [x_l * y_l 可能的进位]
   p_l = [x_l * y_l 表示范围内的部分]
---------------------------------------------------------------------------------------------
【代码注释】
typedef __int128 int128_t;

void store_prod(int128_t *dest, int64_t x, int64_t y) {
    *dest = x * (int128_t) y;
}
GCC产出下面的汇编代码来实现计算：
store_prod:             # x保存在寄存器rdx，y保存在寄存器rsi
  movq    %rdx, %rax    # 复制x至寄存器rax，作为cqto的操作数
  cqto                  # 将x符号扩展为八字，高64位存rdx，低64位存rax
  movq    %rsi, %rcx    # 复制y至寄存器rcx
  sarq    $63, %rcx     # 将rcx中数据算术右移63位，作为扩展后y的高64位，低64位在rsi
  imulq   %rax, %rcx    # 相当于进行x_l * y_h，结果保存于rcx
  imulq   %rsi, %rdx    # 相当于进行x_h * y_l，结果保存于rdx
  addq    %rdx, %rcx    # 计算x_h * y_l + x_l * y_h，结果保存于rcx（即p_h的前两部分）
  mulq    %rsi          # 无符号全乘法计算x_l * y_l，结果低64位保存于rax（即p_l），高64位保存于rdx
  addq    %rcx, %rdx    # 得到最终的p_h
  movq    %rax, (%rdi)  # 将p_l存储在目标位置的低8字节
  movq    %rdx, 8(%rdi) # 将p_h存储在目标位置的高8字节
  ret                   # 程序返回
*/

//3.61题：
//此题需声明静态变量并使用O2以上才能得到使用条件传送指令的编译结果
long cread_alt(long *xp)
{
    static long zero = 0;
    if(xp == 0)
        xp = &zero;
    return *xp;
}

//3.63题：
long switch_prob(long x, long n)
{
    long result = x;
    switch(n)
    {
        case 60:
        case 62:
            result = 8 * x;
            break;
        case 63:
            result >>= 3;
            break;
        case 64:
            x = (result << 4) - x;
        case 65:
            x *= x;
        default:
            result = x + 0x4b;
    }
    return result;
}

/*3.65题：
【分析】
.L6:
  movq    (%rdx), %rcx  # tmp1 = A[i][j]
  movq    (%rax), %rsi  # tmp2 = A[j][i]
  movq    %rsi, (%rdx)  # A[i][j] = tmp2
  movq    %rcx, (%rax)  # A[j][i] = tmp1
  addq    $8, %rdx      # sizeof(long)，顺序寻址
  addq    $120, %rax    # 120 = 15 * 8，故 M = 15
  cmpq    %rdi, %rax    # 循环终止检测
  jne     .L6           # if A[j][i] != A[M][M]，继续循环
---------------------------------------------------------
【答案】
A.寄存器rdx
B.寄存器rax
C.15
*/

/*3.67题：
A.eval的栈帧：
    ____________________
    rsp+104
           ......
    rsp+48
    rsp+40
    rsp+32            
    rsp+24            z
    rsp+16            &z
    rsp+8             y
    rsp               x
    --------栈顶--------
B.传递了%rsp+64（保存process生成的strB结构体的栈空间起始位置）
C. 1)以寄存器rsp中地址为基址，分别计算出偏移+24、+16、+8字节（由于调用时向栈中压入了返回地址，故均要+8）的地址存于寄存器；
   2)访问寄存器中地址对应内存位置保存的值。
D.使用存入的参数作为结构参数s的起始位置，分别偏移0、+8、+16字节在对应位置写入值。
E.
    ____________________
    rsp+104
           ......
    rsp+88
    rsp+80            z
    rsp+72            x
    rsp+64            y
    rsp+56
           ......    
    rsp+32             
    rsp+24            z
    rsp+16            &z
    rsp+8             y
    rsp               x
    --------栈顶--------
    rsp+64 ~ rsp+87保存了结构r，访问时用rsp作为基址，分别偏移+72，+64，+80字节寻址访问各元素。
F.结构体传参及返回时一般不传递整个结构体，而是传递保存结构体的起始位置（基址），随后进行基址+偏移量寻址来读写结构体元素。
*/

/*3.69题：
【分析】
    1)第1、2行指令执行test函数中第一条语句，且可以看出变量first、last之间隔了288字节，猜测结构体b_struct存储方式如下：
        int first          4字节 + 对齐4字节
        a_struct a[CNT]    280字节
        int last           4字节 + 对齐4字节
    2)第3 ~ 5行指令计算出地址 bp + 8 + 40 * i，并访问此处的值，应该是ap->idx。
    且可知结构体a_struct的大小应为40字节，同时也证明first后对齐用了4字节；
    3)第6行指令将第1、2行计算出的n符号扩展为8字节，说明a_struct中成员x的数组元素类型应该是long；
    4)第7行指令执行test函数中最后一条语句，伸缩因子为8，说明a_struct中成员idx的类型为long；
    5)结构体a_struct大小为40字节，idx占8字节，剩余32字节被数组x占用，可知x有32 / 8 = 4个元素。
【答案】
A.CNT = 280 / 40 = 7
B.
typedef struct {
    long idx;
    long x[4];
} a_struct;
*/

//3.71题：
#define BUFSIZE 64
void good_echo(void)
{
    char buf[BUFSIZE];
    int i;
    while (1)
    {
        if (!fgets(buf, BUFSIZE, stdin))
            return;  //读到EOF或者发生错误
        
        //输出缓冲区内的字符
        for (i = 0; buf[i] && buf[i] != '\n'; ++i)
            if (putchar(buf[i]) == EOF)
                return;

        //到达一行的末尾
        if (buf[i] == '\n')
        {
            putchar('\n');
            return;
        }
    }
}
