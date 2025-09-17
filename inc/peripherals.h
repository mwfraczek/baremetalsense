#ifndef PERIPHERALS_H
#define PERIPHERALS_H

void rcc_enable(void); 
void tim2_init(void);
void gpio_mode(void);
void led_blink(void); 
void delay_ms(uint32_t ms); 

#endif
