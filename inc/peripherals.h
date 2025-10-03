#ifndef PERIPHERALS_H
#define PERIPHERALS_H

void rcc_enable(void); 
void gpio_mode(void);
void tim2_enable(void);
void delay_ms(uint32_t ms);
void led_blink_slow(void); 
void led_blink_fast(void);

#endif
