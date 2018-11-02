/*====================================================================
* Project:  Board Support Package (BSP) examples
* Function: simple test example for simulator usage
*
* Copyright HighTec EDV-Systeme GmbH 1982-2014
*====================================================================*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

class A
{
public:
	int i;
	
	A(){i = 0;}
	~A(){}
	
private:
	
};

static const char *my_str = "\r\nHello world - 1!\r";

int main(void)
{
	A a;

	int i = 0;

	//while(i++ < 10)
	while(a.i++ < 10)
	{
		puts(my_str);
		printf("i = %u", i);
	}

	exit(0);

	return EXIT_SUCCESS;
}
