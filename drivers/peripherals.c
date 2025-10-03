#include "stm32l476.h"
#include "peripherals.h"

void rcc_enable(void) {
	RCC_AHB2ENR  |= (1 << 0);  // Enable GPIOA clock
	RCC_AHB2ENR  |= (1 << 1);  // Enable GPIOB clock
	RCC_APB1ENR1 |= (1 << 21); // Enable I2C clock
	RCC_APB1ENR1 |= (1 << 0);  // Enable TIM2 clock
}

void gpio_mode(void) {
	GPIOA_MODER &= ~(3 << 10); 	// Clear PA5 bits
	GPIOA_MODER |= (1 << 10); 	// Set PA5 to output mode
}

void tim2_enable(void) {
	TIM2_SMCR &= ~(0x7 << 0); // Disable slave mode controller (SMS bits 0-2)
	TIM2_PSC = 15; // Define prescaler (CK_CNT = fCK_PSC/(PSC+1) = 16MHz/(15 + 1) = 1 MHz) 
	TIM2_ARR = 999; // Define auto-reload register for 1000 ticks (1000/1Mhz = 1ms)
	TIM2_CNT = 0; // Define counter to start at zero (upcounting mode)
	TIM2_EGR |= (1 << 0); // UG bit synchronizes settings to timer operation
	TIM2_CR1 |= (1 << 0); // Enable TIM2 counter 
}

void delay_ms(uint32_t ms) {
	for (uint32_t i = 0; i < ms; i++) {
		while (!(TIM2_SR & (1 << 0)));
		TIM2_SR &= ~(1 << 0);
	}
}

void led_blink_slow(void) {
	GPIOA_ODR |= (1 << 5); // Set PA5 (LED on)
	delay_ms(100);
	GPIOA_ODR &= ~(1 << 5); // Clear PA5 (LED off)
	delay_ms(100);
}

void led_blink_fast(void) {
        GPIOA_ODR |= (1 << 5); // Set PA5 (LED on)
	delay_ms(10);
        GPIOA_ODR &= ~(1 << 5); // Clear PA5 (LED off)
	delay_ms(10);
}
