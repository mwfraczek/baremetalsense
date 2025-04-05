#ifndef STM32L496_H
#define STM32L496_H

typedef unsigned int uint32_t;

#define RCC_AHB2ENR  (*(volatile uint32_t*)0x4002104C) // LED clock enable
#define RCC_APB1ENR1 (*(volatile uint32_t*)0x40021058) // GPS clock enable

#define GPIOB_MODER  (*(volatile uint32_t*)0x48000400) // GPIOB base address and mode register
#define GPIOB_ODR    (*(volatile uint32_t*)0x48000414) // GPIOB output data register

#define GPIOD_MODER  (*(volatile uint32_t*)0x48000C00) // GPIOD base address and mode register
#define GPIOD_AFRH   (*(volatile uint32_t*)0x48000C24) // GPIOD alternate function register

#define USART3_CR1   (*(volatile uint32_t*)0x40004800)
#define USART3_BRR   (*(volatile uint32_t*)0x4000480C)
#define USART3_RDR   (*(volatile uint32_t*)0x40004824)
#define USART3_ISR   (*(volatile uint32_t*)0x4000481C)

#define LED_PIN7      7   // LD2 on Nucleo board
#define LED_PIN14     14  // LD3 on Nucleo board
#define USART3_RXPIN  9

#endif
