#include <stdio.h>
#include <wiringPi.h>

#define CYCLE ((0.95*0.001)/90)
#define DIVISION_RATIO (CYCLE*19.2*1000000)
#define PWMRANGE (20*0.001)/CYCLE
#define CENTERPOS PWMRANGE*(1.45/20)
#define PWMPIN 18

int main(){
	int angle,qflag;
	wiringPiSetupGpio();
	pinMode(PWMPIN,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(DIVISION_RATIO);   
	pwmSetRange(PWMRANGE);     
	pwmWrite(PWMPIN,CENTERPOS);
	printf("\n");
	printf("************************************\n");
	printf("|    servo control                 |\n");
	printf("|  ------------------------------  |\n");
	printf("|   PWM(Orange) connect to GPIO18  |\n");
	printf("|   Vcc(Red) connect to +5V        |\n");
	printf("|   GND(Brown) connect to GND      |\n");
	printf("|                                  |\n");
	printf("************************************\n");
	qflag = 0;

	printf("CYCLE:%lf\n",CYCLE);
	printf("DIVITION_RATIO:%lf\n",DIVISION_RATIO);
	printf("PWMRANGE:%lf\n",PWMRANGE);
	printf("CENTERPOS:%lf\n",CENTERPOS);

	while(qflag == 0){
		printf("\nInput angle (right:-90 ~ 0 ~ +90:left) : ");
		scanf("%d",&angle);
		if ((angle >= -90) && (angle <=95)){
			pwmWrite(PWMPIN,angle+CENTERPOS);
		} else {
			qflag = 1;
		}
	}
}

