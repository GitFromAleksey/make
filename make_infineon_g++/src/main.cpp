//#include <iostream>
//#include <C:\devel\hightec\toolchains\tricore\v4.9.1.0-infineon-1.1\tricore\include\c++\4.9.4\iostream>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "functions.h"

// using namespace std;

static const char *my_str = "\r\n		-> Hello world!";

int main()
{
	int i = 0;

	puts(my_str);
		
    print_hello();
    // cout << endl;
    // cout << "The factorial of 5 is " << factorial(5) << endl;
	
	while(i < 0xF)
	{
		printf("i = %u\r\n", i);
		i++;
	}

	printf("i = %u\r\n\r\n", i);

    return 0;
}