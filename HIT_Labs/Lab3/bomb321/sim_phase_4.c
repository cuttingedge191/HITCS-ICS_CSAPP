//模拟phase_4的处理过程
#include <stdio.h>

int func4(int edx, int edi, int esi)
{
    int eax, ebx;
    eax = edx - esi;
    ebx = eax;
    ebx >>= 1;
    ebx += esi;
    if (ebx > edi)
    {
        edx = ebx - 1;
        ebx += func4(edx, edi, esi);
    }
    else if (ebx < edi)
    {
        esi = ebx + 1;
        ebx += func4(edx, edi, esi);
    }
    eax = ebx;
    return eax;
}

int main(void)
{
    int input1;
    int res;
    for (input1 = 0; input1 <= 14; ++input1)
    {
        res = func4(14, input1, 0);
        if (res == 35)
            printf("Password:[%d %d]\n", input1, 35);
        else
            printf("Wrong:[%d %d]\n", input1, 35);
    }
    return 0;
}