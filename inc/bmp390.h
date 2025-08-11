#ifndef BMP390_H 
#define BMP390_H

#define BMP_SLAVE_ADDR  0x77
#define PWR_CTRL_ADDR   0x1B
#define ODR_ADDR        0x1D
#define BMP_STATUS_REG  0x03
#define BMP_DATA_ADDR   0x04
#define BMP_OSR_ADDR    0x1C
#define BMP_CONFIG_ADDR 0x1F

typedef enum {
	BMP_OK = 0, BMP_TIMEOUT = -1, BMP_NACK = -2, BMP_NOT_READY = -3
} BMP_Error;

BMP_Error bmp390_setup(uint8_t pressure_en, uint8_t temp_en, uint8_t bmp_mode, uint8_t bmp_odr);
BMP_Error bmp390_status_check(void);
BMP_Error bmp390_read_data(void);

#endif
