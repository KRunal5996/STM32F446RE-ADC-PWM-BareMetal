#include "stm32f4xx.h"


#define GPIOAEN 	(1U<<0)
#define ADC1EN 		(1U<<8)
#define CR2_SWSTART (1U<<30)
#define SR_EOC		(1U<<1)


void pa0pwm_tim2_init(void)
{
	/*Enable clock gpioa*/
	RCC->AHB1ENR |= GPIOAEN;

	/*set pin as alternate mode*/
	GPIOA->MODER &=~(1U<<0);
	GPIOA->MODER |= (1U<<1);

	/*set gpio alternate funcrtion register*/
	GPIOA->AFR[0] |= (1U<<0);
	GPIOA->AFR[0] &=~ (1U<<1);
	GPIOA->AFR[0] &=~ (1U<<2);
	GPIOA->AFR[0] &=~(1U<<3);

	/* timer clock eanble FOR TIM2*/
	RCC->APB1ENR |= (1U<<0);

	/*set the prescaler*/
	TIM2->PSC = 16-1;

	/*set the auto reload register*/
	TIM2->ARR = 1000-1;

	/*set capture/compare register*/
	TIM2->CCR1 = 500;

	/*ENABLE PWM MODE*/
	TIM2->CCMR1 &=~ (1U<<4);
	TIM2->CCMR1 |= (1U<<5);
	TIM2->CCMR1 |= (1U<<6);

	/*ENABLE PRELOAD REGISTER*/
	TIM2->CCMR1 |= (1U<<3);
	/*ENABLE TIMER2 CHANNEL*/
	TIM2->CCER |= (1U<<0);

	/*ENABLE COUNTER*/
	TIM2->CR1 |= (1U<<0);

}


void adc1_init(void)
{
	/*enable clock for GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*set PA1 to analog mode*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/*set pullup and pulldown register to 0 */
	GPIOA->PUPDR &=~ (1U<<2);
	GPIOA->PUPDR &=~ (1U<<3);

	/*Enable clock access to adc1*/
	RCC->APB2ENR |= ADC1EN;

	/*SET RESOLUTION TO 12 BIT */
	ADC1->CR1 &=~ (1U<<24);	// TO SET RESOLUTION YOU NEED TO SET 00 TO BIT 24 AND 25 IN CONTROL REGISTER
	ADC1->CR1 &=~ (1U<<25);

	/*sampling time for channel 1*/
	ADC1->SMPR2 |= (1U<<3);
	ADC1->SMPR2 |= (1U<<4);
	ADC1->SMPR2 |= (1U<<5);

	/*set sequence length to 1 conversion */
	ADC1->SQR1 &=~ (1U<<20);
	ADC1->SQR1 &=~ (1U<<21);
	ADC1->SQR1 &=~ (1U<<22);
	ADC1->SQR1 &=~ (1U<<23);

	/*SELECT CHANNEL 1 AS 1ST CONVERSION*/
	ADC1->SQR3 |= (1U<<0);
	ADC1->SQR3 &=~ (1U<<1);
	ADC1->SQR3 &=~ (1U<<2);
	ADC1->SQR3 &=~ (1U<<3);
	ADC1->SQR3 &=~ (1U<<4);
	/*enable adc1*/
	ADC1->CR2 |= (1U<<0);
}


uint32_t adc1_read1(void)
{
	/*SATRT CONVERSION*/
	ADC1->CR2 |= CR2_SWSTART;

	/*WAIT FOR CONVERSATION TO END*/
	while (!(ADC1->SR&SR_EOC))
	{

	}return ADC1->DR;
}
