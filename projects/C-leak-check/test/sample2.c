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
	str2 = calloc(5, 200);
	str3 = malloc(300);
	
	free(str3);
	
	display_leakinfo();

	return 0;
}
	
