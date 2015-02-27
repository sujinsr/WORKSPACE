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
	str2 = malloc(200);
	str3 = malloc(300);
	str4 = malloc(400);
	str5 = malloc(500);
	str2 = malloc(2000);

	free(str3);
	
	free(str5);
	
	free(str2);
	
	display_leakinfo();

	return 0;
}
	
