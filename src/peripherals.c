#include "stm32l496.h"
#include "peripherals.h"

void rcc_enable(void) {
	RCC_AHB2ENR |= (0x1 << 1);// Enable GPIOB clock
	RCC_APB1ENR1 |= (0x1 << 21);// Enable I2C1 clock
	RCC_APB1ENR1 |= (0x1 << 0); // Enable TIM2 timer clock 
}

void tim2_init(void) {
	TIM2_CR1  =  0;     // Disable TIM2
	TIM2_PSC  =  15999; // Prescaler for 1MHz clock (16MHz HSI / 16000)
	TIM2_ARR  =  999;   // Auto-reload for 1ms (1000 cycles at 1MHz)
	TIM2_EGR  =  1;     // Reset TIM2 - Generate update event
	TIM2_CR1 |=  1;     // Enable TIM2 timer
}

void gpio_mode(void) {
	GPIOB_MODER &= ~(3 << 14);// Clear PB3 bits
	GPIOB_MODER |= (1 << 14);// Set PB3 to output mode
}

void delay_ms(uint32_t ms) {
	while(ms--) {
		TIM2_CNT = 0; // Reset counter register
		TIM2_SR  = 0; // Clear update interrupt flag (UIF)
		while(!(TIM2_SR & 0x1));
	}
}


void led_blink(void) {
	GPIOB_ODR |= (1 << 7);// Toggle PB3 LED
	delay_ms(10);
	GPIOB_ODR &= ~(1 << 7);// Toggle PB3 LED
}
