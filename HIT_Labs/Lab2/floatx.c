#include <stdio.h>

typedef union hex2f
{
    unsigned int hex;
    float f;
} H2F;

int main(void)
{
    H2F pos_zero, neg_zero, pos_min, pos_max, pos_rmin, pos_inf, nan;
    pos_zero.hex = 0x0;
    neg_zero.hex = 0x80000000;
    pos_min.hex = 0x00000001;
    pos_max.hex = 0x7f7fffff;
    pos_rmin.hex = 0x00800000;
    pos_inf.hex = 0x7f800000;
    nan.hex = 0x7f800001;
    printf("Var\t\t\tDec\t\t\t\t\t\t\tHex\n");
    printf("+0\t\t\t%f\t\t\t\t\t\t%x\n", pos_zero.f, pos_zero.hex);
    printf("-0\t\t\t%f\t\t\t\t\t\t%x\n", neg_zero.f, neg_zero.hex);
    printf("pos_min\t\t\t%.50f\t%x\n", pos_min.f, pos_min.hex);
    printf("pos_max\t\t\t%f\t\t%x\n", pos_max.f, pos_max.hex);
    printf("pos_regular_min\t\t%.50f\t%x\n", pos_rmin.f, pos_rmin.hex);
    printf("pos_inf\t\t\t%f\t\t\t\t\t\t\t%x\n", pos_inf.f, pos_inf.hex);
    printf("nan\t\t\t%f\t\t\t\t\t\t\t%x\n", nan.f, nan.hex);
}