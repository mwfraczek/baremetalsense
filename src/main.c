#include "stm32l496.h"

void delay_ms(uint32_t ms) { 
	for (uint32_t i = 0; i < ms * 4000; i++);
	}

int main(void) {
RCC_AHB2ENR |= (1 << 1);   // Enable GPIOB clock

GPIOB_MODER &= ~(0x3 << (LED_USER * 2));     // Clear bits
GPIOB_MODER |= (0x1 << (LED_USER * 2));      // Set PB7 to output mode

GPIOB_MODER &= ~(0x3 << (LED_EXT * 2));  
GPIOB_MODER |= (0x1 << (LED_EXT * 2));       // Set PB13 to output mode

GPIOB_MODER &= ~(0x3 << (SWITCH * 2));
GPIOB_MODER |= (0x0 << (SWITCH * 2));        // Set PB12 to output mode

GPIOB_PUPDR &= ~(0x3 << (LED_SWITCH * 2));
GPIOB_PUPDR |= (0x2 << (LED_SWITCH * 2));    // Set PB10 pull down resistor

GPIOB_MODER &= ~(0x3 << (LED_SWITCH * 2));
GPIOB_MODER |= (0x1 << (LED_SWITCH * 2));    // Set PB10 - output mode


while (1) {
        GPIOB_ODR |= (1 << LED_USER);  // Toggle Blue LED on Nucleo 
	delay_ms(10);
	GPIOB_ODR &= (0 << LED_USER);
	delay_ms(10);
	GPIOB_ODR |= (1 << LED_EXT); // Toggle external breadboard LED 
        delay_ms(10);
        GPIOB_ODR &= (0 << LED_EXT);
        delay_ms(10);
	if (GPIOB_IDR & (1 << SWITCH)) {
			GPIOB_ODR |= (1 << LED_SWITCH); // Toggle 2nd breadboard LED
        		delay_ms(10);
			GPIOB_ODR &= (0 << LED_SWITCH);
			}
	}
}
