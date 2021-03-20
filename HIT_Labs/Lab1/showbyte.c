#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char buf[16];
    int last = 16;
    FILE* fp;
    if (argc != 2) {
        printf("Usage:%s <filedir>\n", argv[0]);
        exit(1);
    }
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Fail to open the file!\n");
        exit(1);
    }
    while (!feof(fp)) {
        for (int i = 0; i < 16; ++i) {
            buf[i] = fgetc(fp);
            if (feof(fp)) {
                last = i;
                break;
            }
            if (buf[i] != '\n')
                printf("%c\t", buf[i]);
            else
                printf("\\n\t");
        }
        printf("\n");
        for (int i = 0; i < last; ++i)
            printf("%.2x\t", buf[i]);
        printf("\n");
    }
    fclose(fp);
    return 0;
}
