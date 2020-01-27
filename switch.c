#include <wiringPi.h>

#define LED_PIN  17
#define SW_PIN  18

int main(void){
	wiringPiSetupGpio();
	
	pinMode(LED_PIN,OUTPUT);
	pinMode(SW_PIN,INPUT);
	pullUpDnControl(SW_PIN, PUD_UP);
	digitalWrite(LED_PIN,HIGH);

	while(1){
		if(digitalRead(SW_PIN)==HIGH){
			digitalWrite(LED_PIN,LOW);
			//delay(1.0*1000);
		}else{
			digitalWrite(LED_PIN,HIGH);
		}
	}

	return 0;
}
