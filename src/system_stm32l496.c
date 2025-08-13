#include "stm32l496.h"

void SystemInit(void) {
    // Reset RCC
    RCC_CR |= (1 << 8); // HSI16ON
    while (!(RCC_CR & (1 << 10))); // Wait HSIRDY

    // Select HSI as system clock
    RCC_CFGR &= ~0x3; // SW = 0x00 for HSI

    // Enable GPIOB and I2C1 clocks
    RCC_AHB2ENR |= (0x1 << 1); // GPIOB clock
    RCC_APB1ENR1 |= (0x1 << 21); // I2C1 clock

    // I2C1 clock source (HSI)
    RCC_CCIPR |= (0x2 << 12); // I2C1SEL = 2

    // Optional: Reset I2C1
    RCC_APB1RSTR1 |= (1 << 21);
    RCC_APB1RSTR1 &= ~(1 << 21);
}
