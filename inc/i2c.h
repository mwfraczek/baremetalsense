#ifndef I2C_H 
#define I2C_H 

void i2c1_init(void); 
int i2c1_write(uint8_t slave_addr, uint8_t reg_addr, uint8_t data);
int i2c1_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t* data, uint8_t len);

#endif
