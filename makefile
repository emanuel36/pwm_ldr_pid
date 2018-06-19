CC = arm-linux-gnueabihf-gcc
INC = -I./inc

all: main

main: folder embedded_linux.o lcd_16x2.o main.o
	$(CC) obj/embedded_linux.o obj/lcd_16x2.o obj/main.o -o APP/app.bin

embedded_linux.o: 
	$(CC) -o embedded_linux.o -c $(INC) src/embedded_linux.c -o obj/embedded_linux.o

lcd_16x2.o: 
	$(CC) -o lcd_16x2.o -c $(INC) src/lcd_16x2.c -o obj/lcd_16x2.o

main.o:
	$(CC) -o main.o -c $(INC) src/main.c -o obj/main.o 

send:
	scp APP/app.bin root@192.168.7.2:~/

folder: 
	mkdir -p obj APP

clean:
	rm -rf obj APP