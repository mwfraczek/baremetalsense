#ifndef BMP390_H
#define BMP390_H

// BMP390 Memory Address
#define BMP_CHIPID_ADDR   0x00
#define BMP_STATUS_ADDR   0x03
#define BMP_DATA_ADDR     0x04
#define BMP_PWRCTRL_ADDR  0x1B
#define BMP_OSR_ADDR      0x1C
#define BMP_ODR_ADDR      0x1D
#define BMP_CONFIG_ADDR   0x1F
#define BMP_SLAVE_ADDR    0x76

// BMP390 Settings 
#define BMP_PWRCTRL       0x13 // Forced Mode - Temp/Pressure Enable
#define BMP_OSR           0x00 // No Oversampling
#define BMP_ODR           0x00 // 5ms Sampling Period

int bmp390_setup(void);
int bmp390_chipid(void);
int bmp390_status(void);

#endif
