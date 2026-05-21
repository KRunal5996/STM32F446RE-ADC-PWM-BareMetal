#include "uart.h"



#define GPIOAEN (1U<<0)
#define USART2EN (1U<<17)
#define CR1_TE (1U<<3)
#define CR1_UE (1U<<13)
#define CR1_RE (1U<<2)
#define SR_TXE (1U<<7)
#define SR_RXNE (1U<<5)
#define sys_freq	16000000
#define APB1_CLK  sys_freq
#define BD_rate 115200

static void uart_set_baudRate(USART_TypeDef *USARTx,uint32_t pheripclk,uint32_t baudRate);
static uint16_t uart_comp_bd(uint32_t pheripclk , uint32_t baudRate);

void uart_tx_init(void);
void uart2_write(int ch);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}


void uart2_tx_init(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &=~ (1U<<4);
	GPIOA->MODER |= (1U<<5);

	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~ (1U<<11);

	RCC->APB1ENR |= USART2EN;

	uart_set_baudRate(USART2,APB1_CLK,BD_rate);

	USART2->CR1 = CR1_TE;
	USART2->CR1 |= CR1_UE;
}

void uart2_rxtx_init(void)
{
	/**************configure UART gpio pin ********************/
	/* enable clock for gpioA*/
	RCC->AHB1ENR |= GPIOAEN;
	/* set PA2 mode to alternate*/
	GPIOA->MODER &=~ (1U<<4);
	GPIOA->MODER |= (1U<<5);

	/* set PA2 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~ (1U<<11);

	/* set PA3 mode to alternate function*/
	GPIOA->MODER &=~ (1U<<6);
	GPIOA->MODER |= (1U<<7);
	/* set PA3 alternate function type to UART_RX (AF07)*/
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &=~ (1U<<15);

	/* enable clock for UART*/
	RCC->APB1ENR |= USART2EN;

	uart_set_baudRate(USART2,APB1_CLK,BD_rate);

	USART2->CR1 = (CR1_TE |CR1_RE);
	USART2->CR1 |= CR1_UE;

}

char uart2_read(void)
{
	while(!(USART2->SR & SR_RXNE))
	{

	}
	return USART2->DR;
}

void uart2_write(int ch)
{
	while(!(USART2->SR & SR_TXE))
	{

	}
	USART2->DR = (ch & 0xFF);
}
static void uart_set_baudRate(USART_TypeDef *USARTx,uint32_t pheripclk,uint32_t baudRate)
{
	USARTx -> BRR = uart_comp_bd(pheripclk,baudRate);
}
static uint16_t uart_comp_bd(uint32_t pheripclk , uint32_t baudRate)
{
	return((pheripclk+(baudRate/2U))/baudRate);
}
