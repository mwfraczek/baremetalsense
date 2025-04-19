#ifndef STM32L496_H
#define STM32L496_H

typedef unsigned int uint32_t;

#define RCC_AHB2ENR  (*(volatile uint32_t*)0x4002104C) // Port B clock enable

#define GPIOB_MODER  (*(volatile uint32_t*)0x48000400) // GPIOB base address and mode register
#define GPIOB_ODR    (*(volatile uint32_t*)0x48000414) // GPIOB output data register
#define GPIOB_IDR    (*(volatile uint32_t*)0x48000410) // GPIOB input data register
#define GPIOB_PUPDR  (*(volatile uint32_t*)0x4800040C) // GPIOB pull up/down register

#define LED_USER      7   // LD2 on Nucleo board - Output
#define LED_EXT       13  // D18 on Nucleo board - Output
#define SWITCH        12  // D19 on Nucleo board - Input 
#define LED_SWITCH    10  // D27 on Nucleo board - Output

#endif
