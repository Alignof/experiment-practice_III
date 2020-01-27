#include <lcd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#define LCDEN 0x0C
#define LCDRS 0x0D
#define LCD_BACKLIGHT 0x08
#define EN 0x04
#define RS 0x01
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

void write_four_bits(int fd,int data){
	wiringPiI2CWrite(fd,data|LCD_BACKLIGHT);
	delay(1);
	wiringPiI2CWrite(fd,data|EN|LCD_BACKLIGHT);
	delay(1);
	wiringPiI2CWrite(fd,(data&~EN)|LCD_BACKLIGHT);
	delay(1);
}

void write_data(int fd,int data){
	int upper;
	int lower;
	upper=data&0xF0;
	lower=data&0x0F;

	write_four_bits(fd,upper);
	write_four_bits(fd,lower);
}

void init(int fd){
	delay(15);
	
	write_data(fd,0x03);
	delay(1);
	write_data(fd,0x03);
	delay(1);
	write_data(fd,0x03);
	delay(1);
	write_data(fd,0x02);
	delay(1);

	write_data(fd,LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS | LCD_4BITMODE);
	delay(1);
	write_data(fd,LCD_DISPLAYCONTROL | LCD_DISPLAYON);
	delay(1);
	write_data(fd,LCD_CLEARDISPLAY);
	delay(1);
	write_data(fd,LCD_ENTRYMODESET | LCD_ENTRYLEFT);
	delay(1);
}

void write_char(int fd,char chardata){
	int upper;
	int lower;
	upper=chardata&0xF0;
	lower=(chardata<<4)&0xF0;

	write_four_bits(fd,1|upper);
	write_four_bits(fd,1|lower);
}

void lcd_clear(int fd){
	write_data(fd,LCD_CLEARDISPLAY);
	write_data(fd,LCD_RETURNHOME);
}

void write_string(int fd,char *string){
	int i;
	
	write_data(fd,0x80);
	for(i=0;string[i]!='\0';i++){
		write_char(fd,string[i]);
	}
}

int main(void){
	int fd;
	char *string="hello world!";
	const unsigned char i2cAddress=0x27;

	fd=wiringPiI2CSetup(i2cAddress);
	printf("setup return : %d\n",fd);

	/* setup lcd... */
	init(fd);

	lcd_clear(fd);

	write_char(fd,'a');
	while(getchar()!='\n');

	lcd_clear(fd);

	write_string(fd,string);
	while(getchar()!='\n');
}

