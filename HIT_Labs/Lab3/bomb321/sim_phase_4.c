//模拟phase_4的处理过程
/*存在问题：func4函数递归调用未在正确时机结束（似乎多递归了若干次）
导致input1输出有错误值，且在主函数中无法输出*/
#include <stdio.h>

int eax, ebx, edx, edi, esi;

void func4(void)
{
    int tmp;
    eax = edx - esi;
    ebx = (eax >> 31) & 0x1 + eax;
    ebx >>= 1;
    ebx += esi;
    if (ebx > edi)
    {
        edx = ebx - 1;
        tmp = ebx; //模仿push %ebx，但似乎不太一样
        func4();
        ebx = tmp; //模仿pop %ebx，但似乎不太一样
        ebx += eax;
    }
    else if (ebx < edi)
    {
        esi = ebx + 1;
        tmp = ebx; //模仿push %ebx，但似乎不太一样
        func4();
        ebx = tmp; //模仿pop %ebx，但似乎不太一样
        ebx += eax;
    }
    eax = ebx;
    if (eax == 35)
        printf("input1 = %d\n", edi);
    return;
}

int main(void)
{
    int input1;
    int res;
    for (input1 = 0; input1 <= 14; ++input1)
    {
        edx = 14;
        esi = 0;
        edi = input1;
        //寄存器eax、ebx当前值未被利用，此处不进行赋值
        func4();
    }
    return 0;
}