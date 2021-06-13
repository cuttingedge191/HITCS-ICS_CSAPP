#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int x = -1190200526;

int main(int argc, char**argv)
{
    float y = 351205200104021653;
    static char z[25] = "1190200526-沈城有";
    printf("x = %d\n", x);
    printf("y = %f\n", y);
    printf("z = %s\n", z);
    if (argc != 3)
    {
        printf("传参数量错误（应为2个,y,z）!\n");
        exit(0);
    }
    y = (float)atof(argv[1]);
    strcpy(z, argv[2]);
    printf("main函数传参至y,z后：\n"); //x为常量，不参与传参，也不再输出
    printf("y = %f\n", y);
    printf("z = %s\n", z);
    return 0;
}
