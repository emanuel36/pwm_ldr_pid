#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "embedded_linux.h"
#include "lcd_16x2.h"

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
	   tempo,
	   pwm;

int measure,
    lastMeasure,
    duty = 0,
    set_point;

char msg1[16], msg2[16];

int verifica_set_point(int duty);
void pid_control();
void atualiza_display();
void init_system();

int main(){
	init_system();
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

		pwm = ((double) duty / (double) PERIOD) * 100;

		atualiza_display();

		usleep(10000);
	}
}

void init_system(){
	initLCD();
	init_analog_pins();
	config_pwm();
	set_pwm_period(PERIOD);
	set_pwm_duty(MIN_DUTY);
	init_pwm();
}

void atualiza_display(){
	sprintf(msg1, " LDR: %d/%d", set_point, measure);
	sprintf(msg2, " PWM: %.2lf", pwm);

	clear_lcd();
	selectLine(1,1);
	writeLCD(msg1);
	selectLine(2,1);
	writeLCD(msg2);
	sendASCII("%");
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