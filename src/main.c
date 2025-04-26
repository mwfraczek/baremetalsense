#include "stm32l496.h"
#include "peripherals.h" 

int main(void) {
	rcc_enable();
	led_indicators();
	delay_ms(100); 

	while (1) {
	}
}

void rcc_enable(void) {
RCC_AHB2ENR  |= (1 << 1);   // Enable GPIOB clock
RCC_APB1ENR1 |= (1 << 21);  // Enable I2C1 clock
	}

void gpiob_i2c1_init(void) {
GPIOB_MODER  &= ~(0xF << 16); 	// Clear PB8 and PB9 bits
GPIOB_MODER  |= (0xA << 16);  	// Set PB8 and PB9 to AF4
GPIOB_PUPDR  &= ~(0xF << 16); 	// Clear PUPD bits  
GPIOB_PUPDR  |= (0x5 << 16);  	// Set PB8,PB9 pull-down resistors
GPIOB_AFRH   &= ~(0xFF << 0);   // Clear AFSEL8, AFSEL9
GPIOB_AFRH   |= (0x44 << 0);    // Set PB8, PB9 to AF4 (I2C1)
}

void led_indicators(void) {
GPIOB_MODER &= ~(0x3 << (LED_USER * 2));     // Clear bits
GPIOB_MODER |= (0x1 << (LED_USER * 2));      // Set PB7 to output
GPIOB_MODER &= ~(0x3 << (LED_EXT * 2));  
GPIOB_MODER |= (0x1 << (LED_EXT * 2));       // Set PB13 to output
GPIOB_MODER &= ~(0x3 << (SWITCH * 2));
GPIOB_MODER |= (0x0 << (SWITCH * 2));        // Set PB12 to input
GPIOB_PUPDR &= ~(0x3 << (LED_SWITCH * 2));
GPIOB_PUPDR |= (0x2 << (LED_SWITCH * 2));    // Set PB10 pull down resistor
GPIOB_MODER &= ~(0x3 << (LED_SWITCH * 2));
GPIOB_MODER |= (0x1 << (LED_SWITCH * 2));    // Set PB10 to output
}


// delay function 
void delay_ms(uint32_t ms) { 
	for (uint32_t i = 0; i < ms * 4000; i++);
	}
