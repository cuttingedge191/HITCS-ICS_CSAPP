/*
* 计算机系统 第七章作业
* 学号：1190200526
* 姓名：沈城有
* 题目：7.7, 7.9, 7.11, 7.13
*/

#include <stdio.h>
#include <stdlib.h>

//7.7题：
/* bar5.c */
static double x;

void f()
{
    x = -0.0;
}

/*7.9题：
答：在foo6.c中，main是函数，属于强符号；而在bar6.c中，main为未初始化全局变量，是弱符号。
链接器选择了foo6.c中的强符号，并将其指向main函数的起始地址，
故在作为char类型printf输出时会默认输出开头的一个字节。
*/