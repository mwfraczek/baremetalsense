typedef unsigned int uint32_t;

#define RCC_AHB2ENR  (*(volatile uint32_t*)0x4002104C) // RCC AHB2 peripheral clock enable register
#define GPIOB_MODER  (*(volatile uint32_t*)0x48000400) // GPIOB mode register
#define GPIOB_ODR    (*(volatile uint32_t*)0x48000414) // GPIOB output data register

//#define RCC_APB1ENR1 (*(volatile uint32_t*)0x40004800) // GPS clock enable register 
//#define USART_CR3

#define LED_PIN7      7   // Pin 7 on GPIOB (LD2 on Nucleo board)
#define LED_PIN14     14  // Pin 14 on GPIOB (LD3 on Nucleo)

int main(void) {
// Enable clock for GPIOB
RCC_AHB2ENR |= (1 << 1);  // Set bit 1 of AHB2ENR to enable GPIOB and GPIOC clock

// Set PB7 and PB14 as output (mode: 01 for output, 00 is input)
GPIOB_MODER &= ~(0x3 << (LED_PIN7 * 2));  // Clear bits for PB7
GPIOB_MODER |= (0x1 << (LED_PIN7 * 2));   // Set PB7 to output mode
GPIOB_MODER &= ~(0x3 << (LED_PIN14 * 2)); // Reset state - clears bits for PB14
GPIOB_MODER |= (0x1 << (LED_PIN14 * 2));  // Set PB14 to output mode

while (1) 
{
// Toggle LED on PB7 and PB14
GPIOB_ODR ^= (1 << LED_PIN7);  // Toggle the bit of PB7
GPIOB_ODR ^= (1 << LED_PIN14); // Toggle PB14 bit high
}
}
