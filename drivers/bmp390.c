// BMP390 Device Driver Library 

#include "stm32l476.h"
#include "i2c.h"
#include "peripherals.h"
#include "bmp390.h"

// BMP390 Configuration Function 
int bmp390_setup(void) {
	i2c1_write(BMP_SLAVE_ADDR, BMP_PWRCTRL_ADDR, BMP_PWRCTRL, 1);
	i2c1_write(BMP_SLAVE_ADDR, BMP_OSR_ADDR, BMP_OSR, 1);
	i2c1_write(BMP_SLAVE_ADDR, BMP_ODR_ADDR, BMP_ODR, 1);
}

int bmp390_chipid(void) {
	uint8_t chipid; 
	i2c1_read(BMP_SLAVE_ADDR, BMP_CHIPID_ADDR, &chipid); 
}

int bmp390_status(void) {
        uint8_t status; 
        i2c1_read(BMP_SLAVE_ADDR, BMP_STATUS_ADDR, &status); 
}

