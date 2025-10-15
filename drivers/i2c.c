// I2C Driver Library for STM32L476RG applications

#include "stm32l476.h"
#include "i2c.h"
#include "peripherals.h"
#include "bmp390.h"
#include "utils.h"

// Reset I2C1 peripheral by toggling PE bit 
void i2c1_reset(void) { 
	I2C1_CR1 &= ~(1 << 0); 
	while (I2C1_CR1 & (1 << 0));
	I2C1_CR1 |= (1 << 0); 
}

// Configure I2C1 peripheral 
void i2c1_init(void) {
	I2C1_CR1 &= ~(1 << 0);   // Disable I2C1 peripheral 
	// ANF Enable, DNF Disable, Stretching Enable
	I2C1_CR1 &= ~(1 << 12) | ~(0xF << 8) | ~(1 << 17);
	I2C1_TIMINGR = 0x30420F13; // 100 kHz timing
	I2C1_CR1 |=  (1 << 0);     // Enable peripheral
}

// I2C1 write function 
int i2c1_write(uint8_t slave_addr, uint8_t reg_addr, const uint8_t data, uint8_t len) {
	I2C1_CR2 &= ~(0x7FFFFFF);       // Clear CR2 register bits
	I2C1_CR2 |=  (slave_addr << 1); // 7-bit slave address in write direction
	I2C1_CR2 |=  ((len+1) << 16);   // NBYTES to transfer + register addr
	I2C1_CR2 |=  (1 << 25);         // Set AUTOEND mode
	I2C1_CR2 |=  (1 << 13);         // Send START
	while (!(I2C1_ISR & (1 << 1))); // Wait for TXIS flag (TXDR is empty & ready)
	I2C1_TXDR = reg_addr; 		// Write register address
	while (!(I2C1_ISR & (1 << 1))); // Wait for TXIS flag
	I2C1_TXDR = data;		// Write data byte 
	while (!(I2C1_ISR & (1 << 5))); // Wait for STOP
}

// I2C1 read function
int i2c1_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data) {
	// Write Phase
	I2C1_CR2 &= ~(0x7FFFFFF);       // Clear CR2 register bits
        I2C1_CR2 |=  (slave_addr << 1); // 7-bit slave address in write direction
	I2C1_CR2 |=  (1 << 16);         // NBYTES to transfer (reg address)
	I2C1_CR2 |=  (1 << 13);         // Send START
	while (!(I2C1_ISR & (1 << 1))); // Wait for TXIS flag (TXDR is empty & ready)
        I2C1_TXDR = reg_addr;           // Write register address

	//Read Phase
	I2C1_CR2 &= ~(0x7FFFC00);       // Clear CR2 register bits (leave SADD unchanged)
	I2C1_CR2 |=  (1 << 10);         // Read direction
	I2C1_CR2 |=  (1 << 16);         // NBYTES to transfer (data)
	I2C1_CR2 |=  (1 << 25);         // Set AUTOEND mode
	I2C1_CR2 |=  (1 << 13);         // Send repeated START
	while (!(I2C1_ISR & (1 << 2))); // Wait for RXDR to be empty 
	*data = I2C1_RXDR;		// Read RXDR 
}
