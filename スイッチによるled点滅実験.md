---
title: "スイッチによるLED点滅実験"
tags: ""
---
# スイッチによるLED点滅実験

この実験ではソフトウェア的にスイッチのチャタリングを防ぐことで安定してLEDをオンオフできることを目標に実験を行った。  
チャタリングはソフトウェア、ハードウェアの双方でチャタリングを防止できるが、今回はソフトウェア的にチャタリングを防止するプログラムをスイッチのオンオフ回路に組み込んだ。  

# 作成したプログラム

以下に作成したプログラムを示す。

```c
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
```

今回は過去50件の入力データを扱い、それらが安定した状態になったらLEDの状態を切り替えることでチャタリング防止とした。  
まず、循環リストに必要な構造体を用意する。  

```c
typedef struct tmp{
	int data;
	struct tmp *next;
	struct tmp *prev;
}circular;
```

念のため、`*prev`を用意したが順方向のみの循環リストではこれは不要である。  

これらの構造痛を組み合わせることで循環リストを構築する。  
具体的にはこれらの次の構造体のポインタを各構造体が保持し、参照することで値を見ていく。  

```c
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
```

必要な数だけ構造体を生成し、次のポインタの値と前の構造体の値を格納し、最終的に参照関係が一つの環になるようにデータを繋げる。  
これらを参照しながらLEDの状態を決定する。

```c
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
```

もし、ボタンが押されているなら今のdataを1にセットし、過去のデータを現在のところに戻ってくるまで見る。  
全てが1なら安定してHIGHの状態になっていると判断し、is_stableを1にセットする。  
変数flagがLEDの状態を決定しているので`flag=!flag`でLEDの状態を反転させる。  

これにより安定して入力が1の状態のときのみLEDの状態が反転するので安定してスイッチ入力をすることが可能になる。  
