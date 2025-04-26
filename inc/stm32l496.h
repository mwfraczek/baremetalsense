#ifndef STM32L496_H
#define STM32L496_H

typedef unsigned int uint32_t;

#define RCC_AHB2ENR   (*(volatile uint32_t*)0x4002104C) // clock - Port B GPIO 
#define RCC_APB1ENR1  (*(volatile uint32_t*)0x40021058) // clock - Port B I2C1

#define GPIOB_MODER   (*(volatile uint32_t*)0x48000400) // GPIOB base address and mode register
#define GPIOB_IDR     (*(volatile uint32_t*)0x48000410) // GPIOB input data register
#define GPIOB_ODR     (*(volatile uint32_t*)0x48000414) // GPIOB output data register
#define GPIOB_PUPDR   (*(volatile uint32_t*)0x4800040C) // GPIOB pull up/down register
#define GPIOB_AFRH    (*(volatile uint32_t*)0x48000424) // GPIOB alternate function hi register

#define I2C1_CR1      (*(volatile uint32_t*)0x40005400) //
#define I2C1_CR2      (*(volatile uint32_t*)0x40005404) //
#define I2C1_TIMINGR  (*(volatile uint32_t*)0x40005410) //
#define I2C1_ISR      (*(volatile uint32_t*)0x40005418) //
#define I2C1_ICR      (*(volatile uint32_t*)0x4000541C) //
#define I2C1_TXDR     (*(volatile uint32_t*)0x40005428) //
#define I2C1_RXDR     (*(volatile uint32_t*)0x4000542C) //

#define LED_USER      7   // LD2 - Output
#define LED_EXT       13  // D18 - Output
#define SWITCH        12  // D19 - Input 
#define LED_SWITCH    10  // D27 - Output
#define I2C1_SCL      8   // D15  
#define I2C1_SDA      9   // D16

#endif
