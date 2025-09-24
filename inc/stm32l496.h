#ifndef STM32L496_H
#define STM32L496_H

#include <stdint.h>

#define RCC_AHB2ENR   (*(volatile uint32_t*)0x4002104C) // clock - Port B/F GPIO 
#define RCC_APB1ENR1  (*(volatile uint32_t*)0x40021058) // clock - Port B I2C1
#define RCC_CR        (*(volatile uint32_t*)0x40021000) // clock - HSI16 oscillator
#define RCC_CCIPR     (*(volatile uint32_t*)0x40021088) // clock source select
#define RCC_APB1RSTR1 (*(volatile uint32_t*)0x40021038) // clock reset 
#define RCC_CFGR      (*(volatile uint32_t*)0x40021008) // clock configuration

// TIM2 is on the APB1 Bus
#define TIM2_CR1      (*(volatile uint32_t*)0x40000000) // TIM2 control register 
#define TIM2_SMCR     (*(volatile uint32_t*)0x40000008) // TIM2 slave mode control  
#define TIM2_SR       (*(volatile uint32_t*)0x40000010) // TIM2 status register (flags)
#define TIM2_EGR      (*(volatile uint32_t*)0x40000014) // TIM2 event generation
#define TIM2_CNT      (*(volatile uint32_t*)0x40000024) // TIM2 slave mode control
#define TIM2_PSC      (*(volatile uint32_t*)0x40000028) // TIM2 prescaler
#define TIM2_ARR      (*(volatile uint32_t*)0x4000002C) // TIM2 auto-reload 

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

#define I2C1_CR1      (*(volatile uint32_t*)0x40005400) // I2C1 configuration register
#define I2C1_CR2      (*(volatile uint32_t*)0x40005404) // I2C1 transaction/control register
#define I2C1_TIMINGR  (*(volatile uint32_t*)0x40005410) // I2C1 timing register
#define I2C1_ISR      (*(volatile uint32_t*)0x40005418) // I2C1 status register
#define I2C1_ICR      (*(volatile uint32_t*)0x4000541C) // I2C1 flag clearing register
#define I2C1_TXDR     (*(volatile uint32_t*)0x40005428) // I2C1 transmit data register
#define I2C1_RXDR     (*(volatile uint32_t*)0x4000542C) // I2C1 receive data register

#define I2C2_CR1      (*(volatile uint32_t*)0x40005800) // I2C2 configuration register
#define I2C2_CR2      (*(volatile uint32_t*)0x40005804) // I2C2 transaction/control register
#define I2C2_TIMINGR  (*(volatile uint32_t*)0x40005810) // I2C2 timing register
#define I2C2_ISR      (*(volatile uint32_t*)0x40005818) // I2C2 status register
#define I2C2_ICR      (*(volatile uint32_t*)0x4000581C) // I2C2 flag clearing register
#define I2C2_TXDR     (*(volatile uint32_t*)0x40005828) // I2C2 transmit data register
#define I2C2_RXDR     (*(volatile uint32_t*)0x4000582C) // I2C2 receive data register

#endif
