#include "stm32l476.h"
#include "peripherals.h"
#include "utils.h"
#include "i2c.h"
#include "bmp390.h"

int main(void) {
	// Setup STM32 peripherals 
	rcc_enable();
	gpio_config();
	tim2_enable();

	// Setup I2C1 peripheral 
	i2c1_init();

	// bmp390 sensor setup code here...
	bmp390_setup();
	bmp390_chipid();
	while (1) 
		led_blink_slow();
}
