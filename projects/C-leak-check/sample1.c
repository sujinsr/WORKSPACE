#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define LEAK_CHECK

int main()
{

	char *str;
#ifdef LEAK_CHECK
	init_leakdetector();
#endif

	str = malloc(100);
	str = malloc(200);

	free(str);

	return 0;
}
	
