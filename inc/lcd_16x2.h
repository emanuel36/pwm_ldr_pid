#include <stdio.h>

#define RS 		67
#define ENABLE 	68
#define D0		44
#define D1		26
#define D2		46
#define D3		65
#define D4		66
#define D5		69
#define D6		45
#define D7		47

void initLCD();
void enableLCD();
void sendASCII(char * );
void sendCMD(int value);
void writeLCD(char *frase);
void shiftRight();
void shiftLeft();
void selectLine(int line, int position);
void clear_lcd();