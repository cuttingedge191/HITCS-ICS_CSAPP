#include <stdio.h>

#define True 1
#define False 0

int isLittleEndian(void)
{
    int test = 0x1;
    char* ptr = &test;
    if (*ptr)
        return True;
    return False;
}

int main(void)
{
    int result;
    result = isLittleEndian();
    if (result)
        printf("Little Endian\n");
    else
        printf("Big Endian\n");
    return 0;
}