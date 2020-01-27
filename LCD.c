#include <lcd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#define LCDEN 0x0C
#define LCDRS 0x0D
//	{RS,RW,E,light}

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

void waitForEnter(){
	while(getchar()!='\n');
}

void write_upper(int fd,int data){
	int upper;
	upper=data&0xF0;
	//enable(E=1)
	wiringPiI2CWrite(fd,upper|LCDEN);
	delay(1);
	//disable(E=0)
	wiringPiI2CWrite(fd,upper);
	delay(1);
}

void write_byte(int fd,int data){
	int upper;
	int lower;
	upper=data&0xF0;
	lower=data&0x0F;

	//enable(E=1)
	wiringPiI2CWrite(fd,upper|LCDEN);
	delay(1);
	//disable(E=0)
	wiringPiI2CWrite(fd,upper);
	delay(1);

	//enable(E=1)
	wiringPiI2CWrite(fd,lower|LCDEN);
	delay(1);
	//disable(E=0)
	wiringPiI2CWrite(fd,lower);
	delay(1);
}

void write_word(int fd,int data){
	int upper;
	int lower;
	upper=data&0xF0;
	lower=data&0x0F;

	//enable(E=1)
	wiringPiI2CWrite(fd,upper|LCDRS);
	delay(1);
	//disable(E=0)
	wiringPiI2CWrite(fd,upper);
	delay(1);

	//enable(E=1)
	wiringPiI2CWrite(fd,lower|LCDRS);
	delay(1);
	//disable(E=0)
	wiringPiI2CWrite(fd,lower);
	delay(1);
}

void init(int fd){
	delay(15);
	//blight backlight
	write_upper(fd,0x3c);

	//initial
	delay(5);
	write_upper(fd,0x3c);
	delay(1);
	write_upper(fd,0x3c);
	delay(1);
	write_upper(fd,0x2c);
	delay(1);
	write_upper(fd,0x2c);
	delay(1);

/*
	while(getchar()!='\n');
	//display on off control
	write_byte(fd,0x0F);
	delay(5);
	while(getchar()!='\n');
	//display clear
	write_byte(fd,0x01);
	delay(5);
	while(getchar()!='\n');
	//entry mode set
	write_byte(fd,0x07);
	delay(1);
	while(getchar()!='\n');
*/	
	write_word(fd,LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS | LCD_4BITMODE);
	write_word(fd,LCD_DISPLAYCONTROL | LCD_DISPLAYON);
	write_word(fd,LCD_CLEARDISPLAY);
	write_word(fd,LCD_ENTRYMODESET | LCD_ENTRYLEFT);
}

void write_char(int fd){
	write_word(fd,0x00);
}

int main(void){
	int i;
	int c;
	int fd;
	const unsigned char i2cAddress=0x27;

	fd=wiringPiI2CSetup(i2cAddress);
	printf("setup return : %d\n",fd);

	/* setup lcd... */
	init(fd);

	//write_char(fd);

	while(getchar()!='\n');
}

