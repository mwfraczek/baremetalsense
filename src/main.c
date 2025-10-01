#include "stm32l476.h"
#include "peripherals.h"
#include "i2c.h"
#include "bmp390.h"

int main(void) {
	// define variables
	uint8_t chip_id;
	uint8_t status;
	uint8_t bmp_data = 0;
	BMP_Error code; 
	
	// initialization of system clock, gpio pins, and i2c1 clock
	rcc_enable();
	gpio_mode();
	i2c1_init();

	// sensor setup
	code = bmp390_setup(1, 1, 0x3, 0x04);
	if (code != BMP_OK)
		led_blink_fast();
	else led_blink_slow();
	// chip id call and verification
	code = bmp390_chip_id(&chip_id);
	if ((code != BMP_OK) && (chip_id != 0x60))
                led_blink_fast();
        else led_blink_slow();
	i2c1_reset();
	// check if data is ready to read
	code = bmp390_status_check(&status);
	if ((code != BMP_OK) && (status != 0x70))
                led_blink_fast();
        else led_blink_slow();
	i2c1_reset();

	// read pressure data bytes 
	if (i2c1_write_reg(BMP_SLAVE_ADDR, 0x04) != 0)
		led_blink_fast();
	else led_blink_slow();
	if (i2c1_read(BMP_SLAVE_ADDR, &bmp_data, 1) != 0)
		led_blink_fast();
	else led_blink_slow();
	i2c1_reset();
	
	if (i2c1_write_reg(BMP_SLAVE_ADDR, 0x05) != 0)
		led_blink_fast();
        else led_blink_slow();
        if (i2c1_read(BMP_SLAVE_ADDR, &bmp_data, 1) != 0)
		led_blink_fast();
        else led_blink_slow();
	i2c1_reset();

	if (i2c1_write_reg(BMP_SLAVE_ADDR, 0x06) != 0)
		led_blink_fast();
        else led_blink_slow();
        if (i2c1_read(BMP_SLAVE_ADDR, &bmp_data, 1) != 0)
		led_blink_fast();
        else led_blink_slow();
}
