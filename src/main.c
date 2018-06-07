#include <stdio.h>
#include <unistd.h>
#include "embedded_linux.h"

#define PERIOD 10000

int main(){
	init_analog_pins();
	config_pwm();
	set_pwm_period(PERIOD);
	set_pwm_duty(1);
	init_pwm();
	int leitura, duty = 0, set_point = 1500;
	double pwm;

	while(1){
		leitura = get_value_ain(0);

		if(leitura < set_point){
			duty++;
		}
		else if(leitura > set_point){
			duty--;
		}
		if(duty < 0 | duty > 10000){
			duty = 1;
		}
		set_pwm_duty(duty);
		pwm = ((double) duty/ (double) PERIOD) * 100;
		printf("Sensor: %d | PWM: %.2lf%\n", leitura, pwm);
	}
}