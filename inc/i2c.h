#ifndef I2C_H 
#define I2C_H 

#include <stdbool.h>
#include <stdint.h>

void i2c1_reset(void);
void i2c1_init(void); 
int i2c1_write(uint8_t slave_addr, uint8_t reg_addr, const uint8_t data, uint8_t len); 
int i2c1_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data);

#endif
