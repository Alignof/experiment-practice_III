---
title: "サーボモータの制御実験"
---

# 概要
この実験ではサーボモータを扱った。  
[wikipedia](https://ja.wikipedia.org/wiki/%E3%82%B5%E3%83%BC%E3%83%9C%E3%83%A2%E3%83%BC%E3%82%BF)によるとサーボモータとは、

> サーボ機構において位置、速度等を制御する用途に使用するモーターである。

とある。  
つまり、ぐるぐる回すのが目的ではなくある角度に回転させるよう制御するモータのことである。  
これらの制御にはPDM制御を使った。  

# 作成したプログラム
以下に作成したプログラムを示す。  

```C
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
```

今回はある程度プログラムが与えられていたので使用する定数にフォーカスをあてて説明する。  
今回使用している定数は以下の5つだ。

```C
#define CYCLE ((0.95*0.001)/90)
#define DIVISION_RATIO (CYCLE*19.2*1000000)
#define PWMRANGE (20*0.001)/CYCLE
#define CENTERPOS PWMRANGE*(1.45/20)
#define PWMPIN 18
```

これらについて順を追って説明する。  

まず、今回のサーボモータのデータシートを読むと、90度変化するのに0.95msの幅が必要なことが分かる。
すなわち、1度のときに必要な秒数Tは、

$$
T = \frac{0.95ms}{90^\circ}
$$

となる。
指数の換算をすると、

```C
CYCLE ((0.95*0.001)/90)
```
となる。
  
そこで、分周比はラズパイの基準クロックである19.2MHzに先ほどのTをかけたものになるので、 

$$
T = \frac{N}{19.2MHz} 
$$
  
つまりNは
  
$$
N = T \times 19.2MHz = \frac{0.95ms}{90^\circ} \times 19.2MHz
$$

と表すことができ、

```C
DIVISION_RATIO (CYCLE*19.2*1000000)
```

となる。

