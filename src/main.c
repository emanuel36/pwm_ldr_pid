#include <stdio.h>
#include <unistd.h>
#include "embedded_linux.h"

#define PERIOD 			2500
#define MIN_DUTY		0
#define MAX_DUTY		2500
#define LDR_SENSOR 		0
#define POTENCIOMETRO	2
#define MAX_SET_POINT 	1500

int ajusta_duty(int duty, int set_point, int leitura);
int verifica_set_point(int duty);

int main(){
	init_analog_pins();
	config_pwm();
	set_pwm_period(PERIOD);
	set_pwm_duty(MIN_DUTY);
	init_pwm();
	int leitura, duty = MIN_DUTY, set_point;
	double pwm;

	while(1){
		set_point = get_value_ain(POTENCIOMETRO);

		leitura = get_value_ain(LDR_SENSOR);

		set_point = verifica_set_point(set_point);

		duty = ajusta_duty(duty, set_point, leitura);

		set_pwm_duty(duty);

		pwm = ((double) duty/ (double) PERIOD) * 100;

		printf("Set Point: %d | Sensor: %d | PWM: %.2lf%\n", set_point, leitura, pwm);
	}
}

int ajusta_duty(int duty, int set_point, int leitura){
	if(leitura < set_point){
			duty++;
	}
	else if(leitura > set_point){
			duty--;
	}

	if(duty < MIN_DUTY | duty > MAX_DUTY){
		return MIN_DUTY;
	}
	return duty;
}

int verifica_set_point(int set_point){
	if(set_point > MAX_SET_POINT){
		return MAX_SET_POINT;
	}
	return set_point;
}