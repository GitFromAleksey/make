#include <iostream>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "functions.h"

using namespace std;

static const char *my_str = "\r\n		-> Hello world!";

int main()
{
	unsigned int i = 0;

	puts(my_str);
		
    print_hello();
    // cout << endl;
    //cout << "The factorial of 5 is " << factorial(5) << endl;
	
	while(i < 33)
	{
		i++;
		cout << "The factorial of " << i << " is " << factorial(i) << endl;
	}

	printf("i = %u\r\n\r\n", i);

    return 0;
}