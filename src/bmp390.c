#include "stm32l496.h"
#include "i2c.h"
#include "peripherals.h"
#include "bmp390.h"

void bmp390_setup(uint8_t pressure_en, uint8_t temp_en, uint8_t bmp_mode, uint8_t bmp_odr){
uint8_t pwr_ctrl = (pressure_en << 0) | (temp_en << 1) | (bmp_mode << 4);
i2c1_write(BMP_SLAVE_ADDR, PWR_CTRL_ADDR, pwr_ctrl);
delay_ms(1);
i2c1_write(BMP_SLAVE_ADDR, ODR_ADDR, bmp_odr);
}

void bmp390_status_check(void) {
uint8_t bmp_status;
i2c1_read(BMP_SLAVE_ADDR, BMP_STATUS_REG, &bmp_status, 1);
}

void bmp390_read_data(void) {
uint8_t bmp_data[6];
i2c1_read(BMP_SLAVE_ADDR, BMP_DATA_ADDR, bmp_data, 6);
}
