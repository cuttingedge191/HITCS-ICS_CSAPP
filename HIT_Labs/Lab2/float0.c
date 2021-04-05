#include <stdio.h>

int main(void)
{
    float x;
    printf("Input x:");
    scanf(" %f", &x);
    printf("%f / 0 = %f\n", x, x / 0);
    printf("%f / 1e-45 = %f\n", x, x / 1e-45);
    return 0;
}