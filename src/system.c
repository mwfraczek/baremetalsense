#include "stm32l476.h"

void SystemInit(void) {
    // Enable HSI16 (16 MHz) for STM32L476RG
    RCC_CR |= (1 << 8); // RCC_CR_HSI16ON
    while (!(RCC_CR & (1 << 10))); // Wait for RCC_CR_HSI16RDYF
}

void _init(void) {
    // Empty, as no C runtime initialization is needed
}
