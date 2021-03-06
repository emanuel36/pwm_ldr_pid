#include <stdio.h>

#define INPUT  0
#define OUTPUT 1
#define LOW    0
#define HIGH   1

void init_gpio(unsigned int , unsigned int);
void set_gpio_high(unsigned int );
void set_gpio_low(unsigned int );
int get_value(unsigned int);
void init_analog_pins();
int get_value_ain(unsigned int ain);
void config_pwm();
void set_pwm_period(int period);
void set_pwm_duty(int duty);
void init_pwm();
void stop_pwm();