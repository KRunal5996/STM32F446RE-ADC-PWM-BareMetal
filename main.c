
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systic.h"
#include "TIMER.h"






int main(void)
{
	uint32_t  adc_value;
	uint32_t  pwm_value;


	pa0pwm_tim2_init();
	adc1_init();


	while(1)
	{
		adc_value = adc1_read1();

		/*convert adc value to pwm value*/
		pwm_value = (adc_value*999)/4095;

		TIM2->CCR1 = pwm_value;
	}

}
