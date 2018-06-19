#include <stdio.h>
#include <unistd.h>
#include "embedded_linux.h"
#include "lcd_16x2.h"

void initLCD(){
	init_gpio(RS, OUTPUT);
	init_gpio(ENABLE, OUTPUT);
	init_gpio(D0, OUTPUT);
	init_gpio(D1, OUTPUT);
	init_gpio(D2, OUTPUT);
	init_gpio(D3, OUTPUT);
	init_gpio(D4, OUTPUT);
	init_gpio(D5, OUTPUT);
	init_gpio(D6, OUTPUT);
	init_gpio(D7, OUTPUT);
	set_gpio_low(RS);
	set_gpio_low(ENABLE);
	set_gpio_low(D0);
	set_gpio_low(D1);
	set_gpio_low(D2);
	set_gpio_low(D3);
	set_gpio_low(D4);
	set_gpio_low(D5);
	set_gpio_low(D6);
	set_gpio_low(D7);
    sendCMD(0x30); //Linha 1, modo 8 bits
    sendCMD(0x38); //Linha 2, modo 8 bits
    sendCMD(0x0C); //Display on, cursor off
    clear_lcd();
}

void enableLCD(){
	set_gpio_high(ENABLE);
	set_gpio_low(ENABLE);
}

void sendASCII(char *caractere){
    int value = (int) *caractere;
    set_gpio_high(RS);
    if(value & (0x1 << 7)){
        set_gpio_high(D7);
    }else{
        set_gpio_low(D7);
    }

    if(value & (0x1 << 6)){
        set_gpio_high(D6);
    }else{
        set_gpio_low(D6);
    }

    if(value & (0x1 << 5)){
        set_gpio_high(D5);
    }else{
        set_gpio_low(D5);
    }

    if(value & (0x1 << 4)){
        set_gpio_high(D4);
    }else{
        set_gpio_low(D4);
    }

    if(value & (0x1 << 3)){
        set_gpio_high(D3);
    }else{
        set_gpio_low(D3);
    }

    if(value & (0x1 << 2)){
        set_gpio_high(D2);
    }else{
        set_gpio_low(D2);
    }

    if(value & (0x1 << 1)){
        set_gpio_high(D1);
    }else{
        set_gpio_low(D1);
    }

    if(value & 0x1){
        set_gpio_high(D0);
    }else{
        set_gpio_low(D0);
    }
    enableLCD();
    int i = 3;
    while(i){
        i--;
    }
}


void sendCMD(int value){
    set_gpio_low(RS);
    if(value & (0x1 << 7)){
    	set_gpio_high(D7);
    }else{
    	set_gpio_low(D7);
    }

    if(value & (0x1 << 6)){
    	set_gpio_high(D6);
    }else{
    	set_gpio_low(D6);
    }

    if(value & (0x1 << 5)){
    	set_gpio_high(D5);
    }else{
    	set_gpio_low(D5);
    }

    if(value & (0x1 << 4)){
    	set_gpio_high(D4);
    }else{
    	set_gpio_low(D4);
    }

    if(value & (0x1 << 3)){
    	set_gpio_high(D3);
    }else{
    	set_gpio_low(D3);
    }

    if(value & (0x1 << 2)){
    	set_gpio_high(D2);
    }else{
    	set_gpio_low(D2);
    }

    if(value & (0x1 << 1)){
    	set_gpio_high(D1);
    }else{
    	set_gpio_low(D1);
    }

    if(value & 0x1){
    	set_gpio_high(D0);
    }else{
    	set_gpio_low(D0);
    }
    enableLCD();
}

void writeLCD(char *frase){
    int i;
    for(i = 0; frase[i] != '\0'; i++){
        sendASCII(&frase[i]);
    }
}

void shiftRight(){
    sendCMD(0x1C);
}

void shiftLeft(){
    sendCMD(0x18);  
}

void selectLine(int line, int position){
    if(line == 1)   sendCMD(0x80 + position);
    if(line == 2)   sendCMD(0xC0 + position);
}

void clear_lcd(){
    sendCMD(0x1);
    int i = 165;
    while(i){
        i--;
    }
}