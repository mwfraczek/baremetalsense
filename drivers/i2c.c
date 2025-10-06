// I2C Driver Library for STM32L476RG (Nucleo) applications
#include "stm32l476.h"
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
	// Configure PB8 (SCL) and PB9 (SDA) for I2C1 (AF4)
	GPIOB_MODER &= ~(0xF << 16); // Clear PB8, PB9
	GPIOB_MODER |= (0xA << 16); // Alternate function
	GPIOB_OTYPER |= (0x3 << 8); // Open-drain
	GPIOB_OSPEEDR &= ~(0xF << 16); // Clear
	GPIOB_OSPEEDR |= (0x0 << 16); // Medium speed (0x5), High (0xA), Low (0x0)
	GPIOB_PUPDR &= ~(0xF << 16); // No pull-up/pull-down (use external pull-ups)
	GPIOB_AFRH &= ~(0xFF << 0); // Clear
	GPIOB_AFRH |= (0x44 << 0); // AF4 for PB8, PB9 (I2C1)

	// Configure I2C1
	I2C1_CR1 &= ~(1 << 0); // Disable I2C1
	I2C1_CR1 &= ~(0x1F << 8); // Clear noise filter bits
	I2C1_CR1 |= (0x2 << 8); // 2-cycle digital filter
	I2C1_CR1 &= ~(1 << 12); // Enable analog filter
	I2C1_TIMINGR = 0x10080202; // 100 kHz timing for 16 MHz HSI16 - 10080803
	I2C1_CR1 &= ~(1 << 17); // Enable clock stretching

	//Set I2C1 clock source to HSI16
	RCC_CCIPR &= ~(0x3 << 12); // Clear I2C1SEL
	RCC_CCIPR |= (1 << 12); // HSI16 (01)

	//Enable I2C1
	I2C1_CR1 |= (1 << 0); // Enable peripheral
}

int i2c1_write_reg(uint8_t slave_addr, uint8_t reg_addr) {
        I2C1_CR2 &= ~(0x07FFFFFF << 0); // Clear CR2 register
        I2C1_CR2 |= (0x0 << 11); // Set addressing mode as 7-bit
        I2C1_CR2 |= (slave_addr << 1); // Slave address
        I2C1_CR2 |= (0x0 << 10); // Set transfer direction (w=0/r=1)
        I2C1_CR2 |= (0x1 << 16); // Number of bytes to transfer
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
        while (!(I2C1_ISR & (1 << 5)) && timeout--); // Wait for STOPF
        if (!timeout) {
                return -1; }
        I2C1_ICR |= (1 << 5); // Clear STOPF flag
        return 0;
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

int i2c1_read(uint8_t slave_addr, uint8_t* data, uint8_t len) {
	I2C1_CR2 &= ~(0x07FFFFFF << 0); // Clear CR2 register
	I2C1_CR2 |= (0x0 << 11);       // 7-bit addressing
	I2C1_CR2 |= (slave_addr << 1); // Slave address
	I2C1_CR2 |= (0x1 << 10); // Read direction (w=0/r=1)
	I2C1_CR2 |= (len << 16); // NBYTES = len (from sensor)
	I2C1_CR2 |= (0x0 << 24); // RELOAD=0 
	I2C1_CR2 &= ~(0x1 << 25); // AUTOEND=1
	I2C1_CR2 |= (1 << 13); // Generate repeated START
	
	uint32_t timeout = 10000;
	for (uint8_t i = 0; i < len; i++) {
		while (!(I2C1_ISR & (1 << 2)) && timeout--) { // Wait for RXNE
			if (!timeout)
				return -1;
		}
		if (I2C1_ISR & (1 << 4)) { // NACKF check
			I2C1_ICR |= (1 << 4); // Clear 
			return -1;
		}
		if (I2C1_ISR & (1 << 8)) { // BERR check
                        I2C1_ICR |= (1 << 8); // Clear 
                        return -1;
		}
		if (I2C1_ISR & (1 << 9)) { // ARLO check
                        I2C1_ICR |= (1 << 9); // Clear
                        return -1;
		}
		if (I2C1_ISR & (1 << 10)) { // OVR check
                        I2C1_ICR |= (1 << 10); // Clear
                        return -1;
		}
		data[i] = I2C1_RXDR; 
		timeout = 10000;
	}
	while (!(I2C1_ISR & (1 << 6)) && timeout--) { // Wait for RXNE
		if (!timeout)
			return -1;
	}
	I2C1_CR2 |= (1 << 14); // Generate STOP
	timeout = 10000;
	while (!(I2C1_ISR & (1 << 5)) && timeout--); // Wait for STOPF
	if (!timeout) {
		return -1;
	}
	I2C1_ICR |= (1 << 5); // Clear STOPF flag
	return 0;
}
