#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char cstr[100] = "1190200526-沈城有";
char *pstr;
char ID[100] = "351205200104021653";

int main(void)
{
	pstr = "1190200526-沈城有";
	printf("cstr = %s", cstr);
	printf("pstr(address) = %p", pstr);
	printf("pstr(string) = %s", pstr);
	strcpy(cstr, ID);
	strcpy(pstr, ID);
	printf("After copy ID:\n");
	printf("cstr = %s", cstr);
	printf("pstr(address) = %p", pstr);
	printf("pstr(string) = %s", pstr);
	return 0;
}
		
