#include "stm32l496.h"
#include "peripherals.h"

void rcc_enable(void) {
  RCC_AHB2ENR |= (1 << 1);  // Enable GPIOB clock (for I2C1 pins PB8/PB9)
  RCC_APB1ENR1 |= (1 << 21);  // Enable I2C1 clock
}

void gpio_mode(void) {
  // Setup PB8/PB9 for I2C1 (already in i2c.c, but if needed here for LED or other)
  // Assuming an LED on PB3 for toggle
  GPIOB_MODER &= ~(3 << 6);  // Clear PB3 bits
  GPIOB_MODER |= (1 << 6);  // Set PB3 to output mode
}

void delay_ms(uint32_t ms) {
  for (uint32_t i = 0; i < ms * 4000; i++) {  // Rough delay, tune for your clock
    __asm__("nop");
  }
}

void led_toggle(void) {
  GPIOB_ODR ^= (1 << 3);  // Toggle PB3 LED
}
