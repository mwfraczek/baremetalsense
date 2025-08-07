#ifndef PERIPHERALS_H
#define PERIPHERALS_H

void rcc_enable(void); 
void gpio_mode(void);
void led_toggle(void); 
void delay_ms(uint32_t ms); 

#endif
