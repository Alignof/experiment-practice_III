#include <wiringPi.h>

#define PIN_LED  (4)

int main(void){
	wiringPiSetupGpio();
	
	pinMode(PIN_LED,OUTPUT);

	while(1){
		digitalWrite(PIN_LED,HIGH);
		delay(1.0*1000);
		
		digitalWrite(PIN_LED,LOW);
		delay(1.0*1000);
	}

	return 0;
}
