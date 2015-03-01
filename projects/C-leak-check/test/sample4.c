#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../leak_check.h"

int main()
{

	char str1[] = "HELLO How are you";
	char *str2;

	init_leakcheck();

	str2 = strdup(str1);

    printf("Out :%s\n", str2);
    
    //free(str2);
    
    display_leakinfo();

	return 0;
}
	
