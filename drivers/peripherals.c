#include "stm32l476.h"
#include "peripherals.h"

void rcc_enable(void) {
	RCC_AHB2ENR  |= (1 << 0);  // Enable GPIOA clock
	RCC_AHB2ENR  |= (1 << 1);  // Enable GPIOB clock
	RCC_APB1ENR1 |= (1 << 21); // Enable I2C clock
}

void gpio_mode(void) {
	GPIOA_MODER &= ~(3 << 10); 	// Clear PA5 bits
	GPIOA_MODER |= (1 << 10); 	// Set PA5 to output mode
}

void led_blink_slow(void) {
	GPIOA_ODR |= (1 << 5); // Set PA5 (LED on)
	for (volatile uint32_t i = 0; i < 100000; i++); // Delay
	GPIOA_ODR &= ~(1 << 5); // Clear PA5 (LED off)
	for (volatile uint32_t i = 0; i < 100000; i++); // Delay
}

void led_blink_fast(void) {
        GPIOA_ODR |= (1 << 5); // Set PA5 (LED on)
        for (volatile uint32_t i = 0; i < 10000; i++); // Delay
        GPIOA_ODR &= ~(1 << 5); // Clear PA5 (LED off)
        for (volatile uint32_t i = 0; i < 10000; i++); // Delay
}
