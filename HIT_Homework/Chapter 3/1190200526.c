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
则 x * y = (2 ^ 128) * (x_h * y_h) + (2 ^ 64) * (x_h * y_l) + (2 ^ 64) * (x_l * y_h) + (x_l * y_l)。
而 128位乘积可以写成p = (2^64) * p_h + p_l
故 p_h = (2 ^ 64) * (x_h * y_h) + (x_h * y_l) + (x_l * y_h)，而(2 ^ 64) * (x_h * y_h)溢出。
最终得
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
long cread_alt(long *xp)
{

}

//3.63题：
