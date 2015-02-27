#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../leak_check.h"

int main()
{

	char *str1;
	char *str2, *str3, *str4, *str5;
	
	init_leakcheck();

	str1 = malloc(100);
	str2 = realloc(str1, 200);
	
	str3 = malloc(300);
	str4 = realloc(NULL, 400);

	display_leakinfo();

	return 0;
}
	
