#ifndef BMP390_H
#define BMP390_H

#define BMP_CHIPID_ADDR   0x00
#define BMP_STATUS_ADDR   0x03
#define BMP_DATA_ADDR     0x04
#define BMP_PWR_CTRL_ADDR 0x1B
#define BMP_OSR_ADDR      0x1C
#define BMP_ODR_ADDR      0x1D
#define BMP_CONFIG_ADDR   0x1F
#define BMP_SLAVE_ADDR    0x77

typedef enum {
	BMP_OK = 0, BMP_TIMEOUT = -1, BMP_NACK = -2, BMP_NOT_READY = -3
}BMP_Error;

BMP_Error bmp390_chip_id(uint8_t *id);
BMP_Error bmp390_setup(uint8_t pressure_en, uint8_t temp_en, uint8_t bmp_mode, uint8_t bmp_odr);
BMP_Error bmp390_status_check(uint8_t *bmp_status);
BMP_Error bmp390_read_data(uint8_t *bmp_data);

#endif
