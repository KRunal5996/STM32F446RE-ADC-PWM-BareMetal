# STM32F446RE ADC Controlled PWM Bare-Metal Project

## Overview
This project demonstrates ADC-controlled PWM generation on STM32F446RE using bare-metal register-level programming in Embedded C without using HAL libraries.

The ADC reads analog input values and dynamically adjusts PWM duty cycle generated through TIM2.

## Features
- ADC driver development
- PWM generation using TIM2
- UART communication
- SysTick delay implementation
- GPIO configuration
- Register-level peripheral programming
- Bare-metal Embedded C development

## Microcontroller
STM32F446RE

## Development Environment
STM32CubeIDE

## Language
Embedded C

## Peripherals Used
- GPIO
- ADC1
- TIM2 PWM
- UART2
- SysTick Timer

## Project Workflow
1. ADC reads analog input from potentiometer
2. ADC value is converted into PWM duty cycle
3. TIM2 generates PWM output based on ADC value
4. PWM signal updates dynamically in real-time

## Future Improvements
- DMA-based ADC
- Interrupt-driven UART
- FreeRTOS integration
- OLED/LCD display support
