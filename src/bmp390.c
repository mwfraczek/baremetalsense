#include "stm32l496.h"
#include "i2c.h"
#include "peripherals.h"
#include "bmp390.h"

BMP_Error bmp390_chip_id(uint8_t *id){
	return i2c1_read(BMP_SLAVE_ADDR, BMP_CHIPID_ADDR, id, 1);
}

BMP_Error bmp390_setup(uint8_t pressure_en, uint8_t temp_en, uint8_t bmp_mode, uint8_t bmp_odr){
	uint8_t pwr_ctrl = (pressure_en << 0) | (temp_en << 1) | (bmp_mode << 4);
	i2c1_write(BMP_SLAVE_ADDR, BMP_PWR_CTRL_ADDR, pwr_ctrl);
	i2c1_write(BMP_SLAVE_ADDR, BMP_ODR_ADDR, bmp_odr);
	return BMP_OK; 
}

BMP_Error bmp390_status_check(uint8_t *bmp_status){
	return i2c1_read(BMP_SLAVE_ADDR, BMP_STATUS_ADDR, bmp_status, 1);
}

BMP_Error bmp390_read_data(uint8_t *bmp_data){
	return i2c1_read(BMP_SLAVE_ADDR, BMP_DATA_ADDR, bmp_data, 6);
}
