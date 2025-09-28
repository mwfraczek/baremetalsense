// I2C Driver Library for STM32L496ZGT3 (Nucleo) applications
#include "stm32l496.h"
#include "i2c.h"
#include "peripherals.h"
#include "bmp390.h"

/*Per STM32, PE must be low >=3 APB cycles to reset. Ensured by SW sequence below. 
CR1 registers not impacted upon reset. Impacted register bits: 
I2C_CR2 = START, STOP, NACK
I2C_ISR = BUSY, TXE, TXIS, RXNE, ADDR, NACKF, TCR, TC, STOPF, BERR, ARLO, OVR*/
void i2c1_reset(void) { 
	I2C1_CR1 &= ~(1 << 0); 
	while (I2C1_CR1 & (1 << 0));
	I2C1_CR1 |= (1 << 0); 
}

void i2c1_init(void) {
	GPIOB_MODER &= ~(0xF << 16); // Clear PB8 and PB9 bits
	GPIOB_MODER |= (0xA << 16); // Set PB8 and PB9 to alternate function
	GPIOB_OTYPER &= ~(0x3 << 8); // Clear
	GPIOB_OTYPER |= (0x3 << 8); // Set PB8, PB9 to open drain
	GPIOB_OSPEEDR &= ~(0xF << 16); // Clear
	GPIOB_OSPEEDR |= (0x0 << 16); // Set I2C1 LOW SPEED
	GPIOB_PUPDR &= ~(0xF << 16); // Clear
	GPIOB_PUPDR |= (0x5 << 16); // Set internal pull-up resistor
	GPIOB_AFRH &= ~(0xFF << 0); // Clear
	GPIOB_AFRH |= (0x44 << 0); // Set PB8-AFSEL8, PB9-AFSEL9 to AF4 (I2C1)
	I2C1_CR1 &= ~(0x00FFDFFF << 0); // Clear CR1 register
	I2C1_CR1 |= (0 << 12); // Enable analog noise filter
	I2C1_CR1 |= (0x2 << 8); // Digital noise filter
	I2C1_TIMINGR = 0x10080803; 
	I2C1_CR1 &= ~(1 << 17); // Enable clock stretching bit
	I2C1_CR1 |= (0x1 << 0); // Enable peripheral
	RCC_CCIPR &= ~(0x3 << 12); // Clear I2C1SEL bits [13:12]
	RCC_CCIPR |= (0x1 << 12);  // Set I2C1SEL to 01 (HSI16)
}

int i2c1_write(uint8_t slave_addr, uint8_t reg_addr, uint8_t data) {
	I2C1_CR2 &= ~(0x07FFFFFF << 0); // Clear CR2 register
	I2C1_CR2 |= (0x0 << 11); // Set addressing mode as 7-bit
	I2C1_CR2 |= (slave_addr << 1); // Slave address
	I2C1_CR2 |= (0x0 << 10); // Set transfer direction (w=0/r=1)
	I2C1_CR2 |= (0x2 << 16); // Number of bytes to transfer
	I2C1_CR2 |= (0x0 << 24); // RELOAD=0 
	I2C1_CR2 |= (0x1 << 25); // AUTOEND=1
	I2C1_CR2 |= (0x1 << 13); // Generate START condition

	uint32_t timeout = 1000;
	while (!(I2C1_ISR & (1 << 1)) && timeout--) { // Wait for empty data register TXIS
		if (!timeout) {
			return -1; }
	}
	I2C1_TXDR = reg_addr; // Write register address
	if (I2C1_ISR & (1 << 4)) { // NACKF check
		I2C1_ICR |= (1 << 4); // Clear NACKF
		return -1;
	}
	timeout = 1000;
	while (!(I2C1_ISR & (1 << 1)) && timeout--) { // Wait for empty data register TXIS
		if (!timeout) {
			return -1; }
	}
	I2C1_TXDR = data; // Write byte	
	if (I2C1_ISR & (1 << 4)) { // NACKF check
		I2C1_ICR |= (1 << 4); // Clear NACKF
		return -1;
	}
	timeout = 1000;
	while (!(I2C1_ISR & (1 << 5)) && timeout--); // Wait for STOPF
	if (!timeout) {
		return -1; }
	I2C1_ICR |= (1 << 5); // Clear STOPF flag
	return 0;
}

int i2c1_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t* data, uint8_t len) {
	I2C1_CR2 &= ~(0x07FFFFFF << 0); // Clear CR2 register
	I2C1_CR2 |= (0x0 << 11); // Set addressing mode as 7-bit
	I2C1_CR2 |= (slave_addr << 1); // Slave address
	I2C1_CR2 |= (0x0 << 10); // Set transfer direction (w=0/r=1)
	I2C1_CR2 |= (0x1 << 16); // Number of bytes to transfer
	I2C1_CR2 |= (0x0 << 24); // RELOAD=0 
	I2C1_CR2 |= (0x0 << 25); // AUTOEND=0
	I2C1_CR2 |= (0x1 << 13); // Generate START condition

	uint32_t timeout = 1000;
	while (!(I2C1_ISR & (1 << 1)) && timeout--) { // Wait for empty data register TXIS
		if (!timeout) {
			return -1; }
	}
	I2C1_TXDR = reg_addr; // Write register address
	
	if (I2C1_ISR & (1 << 4)) { // NACKF check
		I2C1_ICR |= (1 << 4); // Clear NACKF
		return -1;
	}
	timeout = 1000;
	while (!(I2C1_ISR & (1 << 6)) && timeout--) { // Wait for TC (transfer complete)
		if (!timeout) {
			return -1; }
	}

	I2C1_CR2 &= ~(0x07FFFFFF << 0); // Clear CR2 register
	I2C1_CR2 |= (slave_addr << 1); // Slave address
	I2C1_CR2 |= (0x1 << 10); // Set transfer direction (w=0/r=1)
	I2C1_CR2 |= (len << 16); // NBYTES = len (from sensor)
	I2C1_CR2 |= (0x0 << 24); // RELOAD=0 
	I2C1_CR2 |= (0x1 << 25); // AUTOEND=1
	I2C1_CR2 |= (1 << 13); // Generate repeated START
	for (uint8_t i = 0; i <= len; i++) {
		data[i] = I2C1_RXDR;
	}
	if (I2C1_ISR & (1 << 4)) { // NACKF check
		I2C1_ICR |= (1 << 4); // Clear NACKF
		return -1;
	}
	timeout = 1000;
	while (!(I2C1_ISR & (1 << 5)) && timeout--); // Wait for STOPF
	if (!timeout) {
		return -1;
	}
	I2C1_ICR |= (1 << 5); // Clear STOPF flag
	return 0;
}
