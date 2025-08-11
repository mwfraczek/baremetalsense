#include "stm32l496.h"
#include "i2c.h"
#include "peripherals.h"
#include "bmp390.h"

BMP_Error bmp390_setup(uint8_t pressure_en, uint8_t temp_en, uint8_t bmp_mode, uint8_t bmp_odr){
	uint8_t pwr_ctrl = (pressure_en << 0) | (temp_en << 1) | (bmp_mode << 4);
	int err = i2c1_write(BMP_SLAVE_ADDR, PWR_CTRL_ADDR, pwr_ctrl);
	if (err != BMP_OK) {
		return BMP_NACK; }
	err = i2c1_write(BMP_SLAVE_ADDR, ODR_ADDR, bmp_odr);
	if (err != BMP_OK) {
		return BMP_NACK; }
	return BMP_OK; 
}


BMP_Error bmp390_status_check(void) {
	uint8_t bmp_status;
	int err = i2c1_read(BMP_SLAVE_ADDR, BMP_STATUS_REG, &bmp_status, 1);
	if (err != 0) {
		return BMP_NACK; }
	if ((bmp_status & 0x60) != 0x60) {
		return BMP_NOT_READY; }
	return BMP_OK; 
}

BMP_Error bmp390_read_data(void) {
	uint8_t bmp_data[6];
	int err = i2c1_read(BMP_SLAVE_ADDR, BMP_DATA_ADDR, bmp_data, 6);
	if (err != 0) {
		return BMP_NACK; }
	return BMP_OK; 
}
