#include "stm32l496.h"

int main(void) {
RCC_AHB2ENR |= (1 << 1);   // Enable GPIOB clock
RCC_APB1ENR1 |= (1 << 18); // Enable USART3 clock 

GPIOD_MODER &= ~(0x3 << (USART3_RXPIN * 2)); // clear rx bit 
GPIOD_MODER |= (0x2 << (USART3_RXPIN * 2));  // set to alternate function mode
GPIOD_AFRH &= ~(0xF << 0);		     // tx clear
GPIOD_AFRH |= (7 << 0);			     // tx AF7 
GPIOD_AFRH &= ~(0xF << 4);		     // rx clear
GPIOD_AFRH |= (7 << 4);			     // rx AF7

USART3_CR1 = (1 << 2) | (1 << 0);            // RX, TX, USART enable
USART3_BRR = 0x683;                          // 9600 baud rate @ 16 Mhz

GPIOB_MODER &= ~(0x3 << (LED_PIN7 * 2));  // Clear bits for PB7
GPIOB_MODER |= (0x1 << (LED_PIN7 * 2));   // Set PB7 to output mode
GPIOB_MODER &= ~(0x3 << (LED_PIN14 * 2)); // Reset state - clears bits for PB14
GPIOB_MODER |= (0x1 << (LED_PIN14 * 2));  // Set PB14 to output mode

while (1) {
if (USART3_ISR & (1 << 5)) {           // RXNE
        char c = USART3_RDR;           // Read GPS byte
        GPIOB_ODR ^= (1 << LED_PIN7);  // Toggle LED
	char gps_data[80];
	static int i = 0;
	gps_data[i] = c;
	i++;
}	

else if (USART3_ISR & (0 << 5)) {
	GPIOB_ODR ^= (1 << LED_PIN14); // Toggle LED
}
}
}
