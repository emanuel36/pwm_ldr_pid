#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "embedded_linux.h"

void init_gpio(unsigned int gpio, unsigned int direction){
	FILE* f = NULL;
	f = fopen("/sys/class/gpio/export", "w");
	fprintf(f, "%d", gpio);
	fclose(f);

	//DIRECTION
	char path[50];
	sprintf(path, "/sys/class/gpio/gpio%d/direction", gpio);
	f = fopen(path, "w");
	
	if(direction == OUTPUT){
		fprintf(f, "out");
		fclose(f);	
	}
	else{
		fprintf(f, "in");
		fclose(f);	
	}
}

///INPUT
int get_value(unsigned int gpio){
	FILE* f = NULL;
	char leitura, path[50];
	sprintf(path, "/sys/class/gpio/gpio%d/value", gpio);
	f = fopen(path, "r");
	leitura = fgetc(f);
	fclose(f);
	if(strncmp(&leitura, "1", 1) == 0){
		return 1;
	}else{
		return 0;
	}
}

//OUTPUT
void set_gpio_high(unsigned int gpio){
	FILE* f = NULL;
	char path[50];

	sprintf(path, "/sys/class/gpio/gpio%d/value", gpio);
	f = fopen(path, "w");
	fprintf(f, "1");
	fclose(f);
}

void set_gpio_low(unsigned int gpio){
	FILE* f = NULL;
	char path[50];

	sprintf(path, "/sys/class/gpio/gpio%d/value", gpio);
	f = fopen(path, "w");
	fprintf(f, "0");
	fclose(f);
}

void init_analog_pins(){
	FILE* f = NULL;

	f = fopen("/sys/devices/bone_capemgr.9/slots", "w");
	fprintf(f, "cape-bone-iio");
	fclose(f);
	usleep(500000);
}

int get_value_ain(unsigned int ain){
	FILE* f = NULL;
	char path[50], leitura[10];

	sprintf(path, "/sys/devices/ocp.3/helper.15/AIN%d", ain);
	f = fopen(path, "r");
	fgets(leitura, 5, f);
	fclose(f);
	int n = atoi(leitura);
	return n;
}

void config_pwm(){
	FILE* f = NULL;

	f = fopen("/sys/devices/bone_capemgr.9/slots", "w");
	fprintf(f, "cape-universaln");
	fclose(f);
	usleep(500000);

	system("config-pin P9.14 pwm");

	f = fopen("/sys/class/pwm/export", "w");
	fprintf(f, "3");
	fclose(f);
	usleep(500000);
}

	

void set_pwm_period(int period){
	FILE* f = NULL;

	f = fopen("/sys/class/pwm/pwm3/period_ns", "w");
	fprintf(f, "%d", period);
	fclose(f);
}

void set_pwm_duty(int duty){
	FILE* f = NULL;

	f = fopen("/sys/class/pwm/pwm3/duty_ns", "w");
	fprintf(f, "%d", duty);
	fclose(f);
}

void init_pwm(){
	FILE* f = NULL;

	f = fopen("/sys/class/pwm/pwm3/run", "w");
	fprintf(f, "1");
	fclose(f);
}

void stop_pwm(){
	FILE* f = NULL;

	f = fopen("sys/class/pwm/pwm3/run", "w");
	fprintf(f, "0");
	fclose(f);
}