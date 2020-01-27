#include <wiringPi.h>
#include<stdio.h>
#include<stdlib.h>

#define SIZE 100
#define LED_PIN  17
#define SW_PIN  18

typedef struct tmp{
	int data;
	struct tmp *next;
	struct tmp *prev;
}circular;

void circular_list_setup(circular *now){
	int i;
	circular *new;
	circular *tmp;
	circular *head;

	head=now;
	head->data=0;
	tmp=head;

	for(i=0;i<SIZE-1;i++){
		new=(circular*)malloc(sizeof(circular));
		tmp->next=new;
		new->data=0;
		new->prev=tmp;
		tmp=new;
	}
	tmp->next=head;
	head->prev=tmp;
}

int main(void){
	int i;
	int flag=0;
	int is_stable=0;
	circular *now;

	wiringPiSetupGpio();

	pinMode(LED_PIN,OUTPUT);
	pinMode(SW_PIN,INPUT);
	pullUpDnControl(SW_PIN, PUD_UP);
	digitalWrite(LED_PIN,LOW);

	now=(circular*)malloc(sizeof(circular));
	circular_list_setup(now);

	while(1){
		if(digitalRead(SW_PIN)==LOW){
			now->data=1;
			now=now->next;
		}else{
			now->data=0;
			now=now->next;
		}
			
		
		is_stable=1;
		for(i=0;i<(SIZE);i++){
			if(!(now->data)){
				is_stable=0;
				break;
			}
			now=now->next;
		}
		
		if(is_stable) flag=!flag;
		
		if(flag){
			digitalWrite(LED_PIN,LOW);
		}else{
			digitalWrite(LED_PIN,HIGH);
		}
	}

	return 0;
}
