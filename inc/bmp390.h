#ifndef BMP390_H 
#define BMP390_H

#define BMP_SLAVE_ADDR 0x77
#define PWR_CTRL_ADDR  0x1B
#define ODR_ADDR       0x1D
#define BMP_STATUS_REG 0x03
#define BMP_DATA_ADDR  0x04

void bmp390_setup(uint8_t pressure_en, uint8_t temp_en, uint8_t bmp_mode, uint8_t bmp_odr);
void bmp390_status_check(void);
void bmp390_read_data(void);

#endif
