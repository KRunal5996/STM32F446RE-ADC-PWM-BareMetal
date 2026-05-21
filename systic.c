#include "stm32f4xx.h"


#define SYS_LOAD_VAL 	16000
#define  SYSEN			(1U<<0)
#define CTRL_CLKSRC 	(1U<<2)
#define CTRL_CFLAG		(1U<<16)

void SysticDelay(int n)
{
	/*SYSTIC CONFIGURE*/
	SysTick->LOAD 	= SYS_LOAD_VAL;

	/*clear systick current value  */
	SysTick->VAL = 0;

	/*enable systic and select internal clk src*/
	SysTick->CTRL |= CTRL_CLKSRC |SYSEN;

	for(int i=0; i<n; i++)
	{
		/*wait until countflag set*/
		while((SysTick->CTRL & CTRL_CFLAG) == 0)
		{
		}
	}
		SysTick->CTRL = 0;
}

