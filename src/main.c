#include "stm32l496.h"
#include "peripherals.h"
#include "i2c.h"
#include "bmp390.h"

int main(void) {
	rcc_enable();
	gpio_mode();
	i2c1_init();
	//pressure&temp enable, normal mode (0x3), odr sampling period (5ms) 
	bmp390_setup(0x1, 0x1, 0x3, 0x03);
	uint8_t status;
	uint8_t chipid;
	uint8_t data[6]; 
	bmp390_status_check(&status);
	bmp390_read_data(data);
	bmp390_chip_id(&chipid);
}
