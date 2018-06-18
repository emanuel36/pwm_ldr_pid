#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "embedded_linux.h"

#define PERIOD 			2500
#define MIN_DUTY		0
#define LDR_SENSOR 		0
#define POTENCIOMETRO	2
#define MAX_SET_POINT 	1500

double error_meas,
	   kp = 1.0,
	   ki = 0.0,
	   kd = 0.0,
	   proportional = 0,
	   integral = 0,
	   derivative = 0,
	   PID,
	   tempo;

int measure,
    lastMeasure,
    duty = 0,
    set_point;

int verifica_set_point(int duty);
void pid_control();

int main(){
	init_analog_pins();
	config_pwm();
	set_pwm_period(PERIOD);
	set_pwm_duty(MIN_DUTY);
	init_pwm();
	int leitura;
	double pwm;

	clock_t Ticks[2];
    Ticks[0] = clock();

	while(1){
		Ticks[1] = clock();
		tempo = (Ticks[1] - Ticks[0]) * 1000 / CLOCKS_PER_SEC;
		Ticks[0] = clock();	

		set_point = get_value_ain(POTENCIOMETRO);

		measure = get_value_ain(LDR_SENSOR);

		set_point = verifica_set_point(set_point);

		pid_control();

		set_pwm_duty(duty);

		pwm = ((double) duty/ (double) PERIOD) * 100;

		printf("Set Point: %d | Sensor: %d | PWM: %.2lf%\n", set_point, measure, pwm);
	}
}

int verifica_set_point(int set_point){
	if(set_point > MAX_SET_POINT){
		return MAX_SET_POINT;
	}
	return set_point;
}

void pid_control(){
    error_meas = (double) set_point - measure;

    proportional = error_meas * kp;

    integral += error_meas * ki * tempo;

    derivative = (lastMeasure - measure) * kd * tempo; 

    lastMeasure = measure;

    PID = proportional + integral + derivative;
    
    duty = PID + duty;

    if(duty > PERIOD){
    	duty = PERIOD;	
    } 

    if(duty < 0){
    	duty = 0;
    }
}