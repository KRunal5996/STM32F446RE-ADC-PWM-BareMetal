#include "stm32f4xx.h"
#include "adc.h"
#define ADC1EN 		(1U<<8)
#define GPIOAEN 	(1U<<0)
#define ADC_CH1  	(1U<<0)
#define led_pin		(1U<<6)
#define CR2_CONT	(1U<<1)
#define ADC_SEQ_LEN1  0X00
#define ADON_CR2 	(1U<<0)  // ADON = analog to digital ON AND OFF
#define CR2_SWSTART (1U<<30)
#define SR_EOC		(1U<<1)

void pa1_adc_init(void)
{
   /*enable the clock for gpioa*/
	RCC->AHB1ENR |= GPIOAEN;

	/*set the mode for pa1 to analog*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/***configure the ADC module ***/
	/*enable the clock for adc module */
	RCC->APB2ENR |= ADC1EN;

	/* configure the adc parameters */
	/*converstion sequence start*/
	ADC1->SQR3 |= ADC_CH1;
	/*converstion sequence length*/
	ADC1->SQR1 |= ADC_SEQ_LEN1;
	/*enable ADC module*/
	ADC1->CR2 |= ADON_CR2;
}


void strt_converstion(void)
{
	/*ENABLE CONTINOUS CONVERSION*/
	ADC1->CR2 |= CR2_CONT;
	/*start adc conversion*/
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t ADC_read(void)
{
	/*wait for conversion to be complete*/
	while(!(ADC1->SR &SR_EOC))
			{

			}
	/*read converted result*/
	return(ADC1->DR);
}
