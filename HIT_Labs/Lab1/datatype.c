#include <stdio.h>
#include <stdlib.h>

typedef unsigned char *byte_pointer;

char ch = 'A';
short num_s = 1190;
int num_i = 1190200;
long num_l = 1190200526;
float id_f = 2309032.1;
double id_d = 2309.0321;
char name[10] = "沈城有";

void show_bytes(byte_pointer start, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++)
	printf("%p\t0x%.2x\n", &start[i], start[i]); 
    printf("\n");
}

int main(void)
{
    printf("Type\tName\tValue\t\nAddress\t\tShowbyte\n");
    printf("______________________________________\n");

    printf("char\tch\t%c\t\n", ch);
    show_bytes(&ch, sizeof(char));

    printf("short\tnum_s\t%hd\t\n", num_s);
    show_bytes(&num_s, sizeof(short));

    printf("int\tnum_i\t%d\t\n", num_i);
    show_bytes(&num_i, sizeof(int));

    printf("long\tnum_l\t%ld\t\n", num_l);
    show_bytes(&num_l, sizeof(long));

    printf("float\tid_f\t%f\t\n", id_f);
    show_bytes(&id_f, sizeof(float));

    printf("double\tid_d\t%lf\t\n", id_d);
    show_bytes(&id_d, sizeof(double));

    printf("String\tname\t%s\t\n", name);
    show_bytes(&name, sizeof(name));

    return 0;
}