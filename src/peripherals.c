#include "stm32l496.h"
#include "peripherals.h"

void rcc_enable(void) {
	RCC_AHB2ENR   |= (0x1 << 1);      // Enable GPIOB clock
	RCC_APB1ENR1  |= (0x1 << 21);     // Enable I2C1 clock
	RCC_CR        |= (0x1 << 8);      // Enable HSI16 clock
	while (!(RCC_CR & (0x1 << 10)));  // Wait for HSIRDY
	RCC_CCIPR     |=  (0x2 << 12);    // I2C1SEL  (HSI is I2C1 clock source)
}

void gpio_mode(void) {
	GPIOB_MODER   &= ~(0x3 << 14);   // Clear bits
	GPIOB_MODER   |=  (0x1 << 14);   // Set PB7 to output
}

void delay_ms(uint32_t ms) {
	for (uint32_t i = 0; i < ms * 4000; i++);   // Rough delay, tune for your clock
}

void led_toggle(void) {
	GPIOB_ODR |= (1 << 7);  // Toggle PB3 LED
	delay_ms(50);
	GPIOB_ODR &= ~(1 << 7);  // Toggle PB3 LED
	delay_ms(50);
}
