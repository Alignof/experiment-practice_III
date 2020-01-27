#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPICH 0
#define SPISPEED 10000


int ad_read(int ch);

int main(){
	int ch,i;
	if(wiringPiSPISetup(SPICH, SPISPEED) < 0){
		printf("initialize failed!\n");
		exit(1);
	}
	while (1){
		printf("input channel>>>");
		scanf("%d",&ch);

		if((ch<0)||(ch>7)){
			for(i=0;i<8;i++){
				printf("ch%d=%d\n",i,ad_read(i));
			}
		}else{
			printf("ch%d=%d\n",ch,ad_read(ch));	
		}
	}
	return 0;
}

int ad_read(int ch){
	unsigned char data[3];
	int val;

	data[0]=0x01;
	data[1]=0x80;
	data[2]=0x00;

	wiringPiSPIDataRW(ch,data,3);

	val=data[2];
	val+=(data[2]>>6)<<8;

	return val;
}
