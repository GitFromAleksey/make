//#include <iostream>
//#include <C:\devel\hightec\toolchains\tricore\v4.9.1.0-infineon-1.1\tricore\include\c++\4.9.4\iostream>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "functions.h"

#include "Compilers.h"
#include "IfxSrc_reg.h"
#include "illd_config/Ifx_Cfg.h"

#define D    (*(long int*)0xF0038000u)
// using namespace std;

static const char *my_str = "\r\n\t\t\t-> Hello world!";

volatile Ifx_SRC_SRCR *srcr;

//IFX_INTERRUPT(stm0Sr0ISR, 0, IFX_INTPRIO_STM0_SR0, ISR_GROUP_PRIO_STM0)
//{

//}

void init(void)
{
	srcr = &(MODULE_SRC.STM.STM[0].SR0);
	
	srcr->B.SRPN = 10; // priority;
    srcr->B.TOS  = 0; // typOfService;
	srcr->B.CLRR = 1; // clearRequest
	srcr->B.SRE = 1; // enables an interrupt
}

int main()
{
	int i = 0;
	int j = 0;
	
	puts(my_str);
		
    print_hello();
    // cout << endl;
    // cout << "The factorial of 5 is " << factorial(5) << endl;

	init();
	
	//printf("D = %lu\r\n", (long int)(D));
	
	srcr->B.SETR = 1;
	//srcr->B.CLRR = 1;
	
	if(srcr->B.SRR == 1)
		printf("srcr->B.SRR == 1\r\n");
	
	while(1)
	{
		i = 0;
		j++;
		//printf("j = %u\r\n", j);
		while(i < 0xFFFF)
		{
			//printf("i = %u\r\n", i);
			i++;
// 			k = i/j + k;
		}
	}

	//printf("i = %u\r\n\r\n", i);

    return 0;
}