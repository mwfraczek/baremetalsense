#include "stm32l496.h"
#include "peripherals.h"
#include "i2c.h"
#include "bmp390.h"

int main(void) {
	rcc_enable();
	gpio_mode();
	i2c1_init();
	bmp390_setup(0x1, 0x1, 0x3, 0x7); // enable sensors, normal mode, data rate
}
