#ifndef STM32L496_H
#define STM32L496_H

#include <stdint.h>

#define RCC_AHB2ENR   (*(volatile uint32_t*)0x4002104C) // clock - Port B/F GPIO 
#define RCC_APB1ENR1  (*(volatile uint32_t*)0x40021058) // clock - Port B I2C1

#define GPIOB_MODER   (*(volatile uint32_t*)0x48000400) // GPIOB base address/mode
#define GPIOB_OTYPER  (*(volatile uint32_t*)0x48000404) // Type - Open drain vs push/pull
#define GPIOB_OSPEEDR (*(volatile uint32_t*)0x48000408) // GPIOB output speed register
#define GPIOB_IDR     (*(volatile uint32_t*)0x48000410) // GPIOB input data register
#define GPIOB_ODR     (*(volatile uint32_t*)0x48000414) // GPIOB output data register
#define GPIOB_BSRR    (*(volatile uint32_t*)0x48000418) // GPIOB bit set/reset register
#define GPIOB_PUPDR   (*(volatile uint32_t*)0x4800040C) // GPIOB pull up/down register
#define GPIOB_AFRH    (*(volatile uint32_t*)0x48000424) // GPIOB alt function register

#define GPIOF_MODER   (*(volatile uint32_t*)0x48001400) // GPIOF base address/mode
#define GPIOF_OTYPER  (*(volatile uint32_t*)0x48001404) // Type - Open drain vs push/pull
#define GPIOF_IDR     (*(volatile uint32_t*)0x48001410) // GPIOF input data register
#define GPIOF_ODR     (*(volatile uint32_t*)0x48001414) // GPIOF output data register
#define GPIOF_BSRR    (*(volatile uint32_t*)0x48001418) // GPIOF bit set/reset register
#define GPIOF_PUPDR   (*(volatile uint32_t*)0x4800140C) // GPIOF pull up/down register
#define GPIOF_AFRH    (*(volatile uint32_t*)0x48001424) // GPIOF alt function register

#define I2C1_CR1      (*(volatile uint32_t*)0x40005400) //
#define I2C1_CR2      (*(volatile uint32_t*)0x40005404) //
#define I2C1_TIMINGR  (*(volatile uint32_t*)0x40005410) //
#define I2C1_ISR      (*(volatile uint32_t*)0x40005418) //
#define I2C1_ICR      (*(volatile uint32_t*)0x4000541C) //
#define I2C1_TXDR     (*(volatile uint32_t*)0x40005428) //
#define I2C1_RXDR     (*(volatile uint32_t*)0x4000542C) //

#define I2C2_CR1      (*(volatile uint32_t*)0x40005800) //
#define I2C2_CR2      (*(volatile uint32_t*)0x40005804) //
#define I2C2_TIMINGR  (*(volatile uint32_t*)0x40005810) //
#define I2C2_ISR      (*(volatile uint32_t*)0x40005818) //
#define I2C2_ICR      (*(volatile uint32_t*)0x4000581C) //
#define I2C2_TXDR     (*(volatile uint32_t*)0x40005828) //
#define I2C2_RXDR     (*(volatile uint32_t*)0x4000582C) //

#endif
