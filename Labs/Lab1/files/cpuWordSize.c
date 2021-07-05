#include <stdio.h>

int cpuWordSize(void)
{
    return (int)(8 * sizeof(void*));
}

int main(void)
{
    int wordsize;
    wordsize = cpuWordSize();
    printf("CPU字长（位数）为%d位\n", wordsize);
    return 0;
}