//#include <iostream>
//#include <C:\devel\hightec\toolchains\tricore\v4.9.1.0-infineon-1.1\tricore\include\c++\4.9.4\iostream>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "functions.h"

#include "Ifx_Types.h"


// using namespace std;

static const char *my_str = "\r\n\t\t\t-> Hello world!";

int main()
{
	int i = 0;
	int j = 0;
	
	printf("\r\n\t\t\tIFX_PI=%1.31f\r\n",IFX_PI);
	
	puts(my_str);
		
    print_hello();
    // cout << endl;
    // cout << "The factorial of 5 is " << factorial(5) << endl;

	while(1)
	{
		i = 0;
		j++;
		printf("j = %u\r\n", j);
		while(i < 0xFFFF)
		{
		//	printf("i = %u\r\n", i);
			i++;
// 			k = i/j + k;
		}
	}

	printf("i = %u\r\n\r\n", i);

    return 0;
}