#include <stdio.h>
#include <stdlib.h>

typedef unsigned char *byte_pointer;

struct stu1
{
    char stunum[11];
    int age;
};

union stu2
{
    float f;
    int age;
};

char ch = 'A';
short num_s = 1190;
int num_i = 1190200;
long num_l = 1190200526;
float id_f = 2309032.1;
double id_d = 2309.0321;
char name[10] = "沈城有";
int test[3] = {1, 2, 3};
char* ptr = &ch;
enum gender {male, female} gen;

void show_bytes(byte_pointer start, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++)
	printf("%p\t0x%.2x\n", &start[i], start[i]); 
    printf("\n");
}

int main(void)
{
    struct stu1 s_s = {"1190200526", 19};
    union stu2 s_u;
    s_u.f = 123.456;
    gen = male;

    printf("Type\tName\tValue\t\nAddress\t\tShowbyte\n");
    printf("______________________________________\n");

    printf("char\tch\t%c\n", ch);
    show_bytes((void*)&ch, sizeof(char));

    printf("short\tnum_s\t%hd\n", num_s);
    show_bytes((void*)&num_s, sizeof(short));

    printf("int\tnum_i\t%d\n", num_i);
    show_bytes((void*)&num_i, sizeof(int));

    printf("long\tnum_l\t%ld\n", num_l);
    show_bytes((void*)&num_l, sizeof(long));

    printf("float\tid_f\t%f\n", id_f);
    show_bytes((void*)&id_f, sizeof(float));

    printf("double\tid_d\t%lf\n", id_d);
    show_bytes((void*)&id_d, sizeof(double));

    printf("String\tname\t%s\n", name);
    show_bytes((void*)&name, sizeof(name));

    printf("char*\tptr\t%p\n", ptr);
    show_bytes((void*)&ptr, sizeof(ptr));

    printf("struct stu1\ts_s\tstunum = \"%s\", age = %d\n", s_s.stunum, s_s.age);
    show_bytes((void*)&s_s, sizeof(s_s));

    printf("union stu2\ts_u\tf = %f, age = %d\n", s_u.f, s_u.age);
    show_bytes((void*)&s_u, sizeof(s_u));

    printf("int[]\ttest\ttest[0] = %d, test[1] = %d, test[2] = %d\n", test[0], test[1], test[2]);
    show_bytes((void*)&test, sizeof(test));

    printf("enum gender\tgen\t%d\n", gen);
    show_bytes((void*)&gen, sizeof(gen));

    printf("______________________________________\n");
    printf("Function\tAddress\n");
    printf("main\t%p\n", &main);
    printf("printf\t%p\n", &printf);

    return 0;
}