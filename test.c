#include <wiringPi.h>
#include<stdio.h>
#include<stdlib.h>

#define SIZE 10
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
		new->data=i+1;
		new->prev=tmp;
		tmp=new;
	}


	tmp->next=head;
	head->prev=tmp;

	printf("tmp->next:%d\n",tmp->next);
	printf("head->next:%d\n",head->next);
	printf("head->prev:%d\n",head->prev);
}

int main(void){
	int i;
	circular *now;
	now=(circular*)malloc(sizeof(circular));
	
	circular_list_setup(now);
	for(i=0;i<100;i++){
		printf("NO.%2d \tprev:%d now:%d  next:%d data:%d\n",i ,now->prev ,now ,now->next,now->data);
		now=now->next;
	}

	return 0;
}
