//2014-02-20 
//charlie dice: a dice game that use leds connected with charlieplex method.  
//20140220 - based on http://makezine.com/projects/charlieplexing-leds-with-an-avr-atmega328-or-arduino/

/*
ATtiny2313

4 pins: PD2-5, with 100R resistors
PD2: ---100R---OUT0
PD3: ---100R---OUT1
PD4: ---100R---OUT2
PD5: ---100R---OUT3

9 leds:
dice ---> 1 ------ 2 ----  6
0 3 6 | . . .  | 0 . . | 0 . 0    
1 4 7 | . 0 .  | . . . | 0 . 0
2 5 8 | . . .  | . . 0 | 0 . 0

led0: 32 catode OUT3, anode OUT2 (32) - turn ON when OUT3 is LOW (0V) and OUT2 HIGH (5V)
led1: 23
led2: 31 
led3: 13
led4: 12
led5: 30
led6: 21
led7: 20
led8: 10

*/


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> //rand
#include <avr/eeprom.h>

#define F_CPU 1000000UL //for delay.h
#define HIGH 1 //led with 5V
#define LOW 0 //led with 0V
#define IN 0 //the pin is input
#define OUT 1 //the pin is output

#define NUMPINS 4 //max leds: n*n-n (4 pins, 12 leds max)
#define LED_COUNT 9 //num leds really connected
#define PIN_CONFIG 0
#define PIN_STATE 1

#define outPort (*((volatile bits_t*)(&PORTD)))
#define portOff PORTD
#define dirPort DDRD

#define outPin0 PD2
#define outPin1 PD3
#define outPin2 PD4
#define outPin3 PD5

#define  out0 outPort.bit2
#define  out1 outPort.bit3
#define  out2 outPort.bit4
#define  out3 outPort.bit5


typedef struct {
	unsigned char bit0:1;
	unsigned char bit1:1;
	unsigned char bit2:1;
	unsigned char bit3:1;
	unsigned char bit4:1;
	unsigned char bit5:1;
	unsigned char bit6:1;
	unsigned char bit7:1;
} bits_t;


uint8_t matrix[LED_COUNT][2][NUMPINS] ={
		// pinConfig 0 1 2 3 ------- pinState 0 1 2 3	//X=0v , Y=5v
		{ { IN, IN, OUT, OUT }, { LOW,  LOW, HIGH,LOW } }, //32: 3=0v, 2=5v 
		{ { IN, IN, OUT, OUT }, { LOW,  LOW, LOW, HIGH } }, //23: 2=0v, 3=5v
		{ { IN, OUT, IN, OUT }, { LOW,  HIGH, LOW, LOW } }, //31
		{ { IN, OUT, IN, OUT }, { LOW,  LOW, LOW, HIGH } }, //13

		{ { IN, OUT, OUT, IN }, { LOW,  LOW, HIGH, LOW } }, //12
		{ { OUT, IN, IN, OUT }, { HIGH,  LOW, LOW, LOW } }, //30
		{ { IN, OUT, OUT, IN }, { LOW,  HIGH, LOW, LOW } }, //21
		{ { OUT, IN, OUT, IN }, { HIGH,  LOW, LOW, LOW } }, //20

		{ { OUT, OUT, IN, IN }, { HIGH,  LOW, LOW, LOW } } //10
}; 


void sleep(uint8_t millisec){
	while(millisec){
		_delay_ms(1);
		millisec--;
	}
}

void debug(uint8_t zeroUm){

	uint8_t sleepTime;
	if(zeroUm==0){
		sleepTime = 255; //zero, blink slow
	}else{
		sleepTime = 75; //1, blink fast
	}

	dirPort |=(1<<outPin2);
	dirPort |=(1<<outPin3);

	while(1){
		//blink LED 0
		sleep(sleepTime);
		out2 = LOW;
		out3 = HIGH;

		sleep(sleepTime);
		out3 = LOW;
		out2 = HIGH;
	}

}


void pinMode(uint8_t pin, uint8_t inOut){
//debug(inOut);
	if(inOut==0){
		dirPort &=~(1<<pin);//input (tristate)
	}else{
		dirPort |=(1<<pin);//output

	}
}


void turnOn(uint8_t led ) {
	dirPort = 0x00;//turn all tristate, disconnected.
	portOff = 0x00; // all pins 0V. Avoid the flickering ghost led.

pinMode( outPin0, matrix[led][PIN_CONFIG][0] );
pinMode( outPin1, matrix[led][PIN_CONFIG][1] );
pinMode( outPin2, matrix[led][PIN_CONFIG][2] );
pinMode( outPin3, matrix[led][PIN_CONFIG][3] );

	out0 = matrix[led][PIN_STATE][0] ;
	out1 = matrix[led][PIN_STATE][1] ;
	out2 = matrix[led][PIN_STATE][2] ;
	out3 = matrix[led][PIN_STATE][3] ;
}


#define DICE_SLEEP 3
void showDice(uint8_t num){

switch(num){

case 1:{
	turnOn(4);
	break;
	}	


case 2:{
	turnOn(0);
	sleep(DICE_SLEEP);
	turnOn(8);
	sleep(DICE_SLEEP);
	break;
	}	

case 3:{
	turnOn(0);
	sleep(DICE_SLEEP);
	turnOn(4);
	sleep(DICE_SLEEP);
	turnOn(8);
	sleep(DICE_SLEEP);
	break;
	}	

case 4:{
	turnOn(0);
	sleep(DICE_SLEEP);
	turnOn(2);
	sleep(DICE_SLEEP);
	turnOn(6);
	sleep(DICE_SLEEP);
	turnOn(8);
	sleep(DICE_SLEEP);
	break;
	}	

case 5:{
	turnOn(0);
	sleep(DICE_SLEEP);
	turnOn(2);
	sleep(DICE_SLEEP);
	turnOn(4);
	sleep(DICE_SLEEP);
	turnOn(6);
	sleep(DICE_SLEEP);
	turnOn(8);
	sleep(DICE_SLEEP);
	break;
	}	

case 6:{
	turnOn(0);
	sleep(DICE_SLEEP);
	turnOn(1);
	sleep(DICE_SLEEP);
	turnOn(2);
	sleep(DICE_SLEEP);
	turnOn(6);
	sleep(DICE_SLEEP);
	turnOn(7);
	sleep(DICE_SLEEP);
	turnOn(8);
	sleep(DICE_SLEEP);
	break;
	}	


}


}

void showSequence(uint8_t delay1){
	sleep(delay1);
	turnOn(0);

	sleep(delay1);
	turnOn(1);

	sleep(delay1);
	turnOn(2);

	sleep(delay1);
	turnOn(3);

	sleep(delay1);
	turnOn(4);

	sleep(delay1);
	turnOn(5);

	sleep(delay1);
	turnOn(6);

	sleep(delay1);
	turnOn(7);

	sleep(delay1);
	turnOn(8);

}


void initRand(void)
{
        uint8_t state;
        static uint8_t EEMEM sstate;

        state = eeprom_read_byte(&sstate);

        // Check if it's unwritten EEPROM (first time). Use something funny
        // in that case.
        if (state == 0xff)
                state = 0xAA;
        srand(state);
        eeprom_write_dword(&sstate, rand());
} 

int main(void){

	initRand();

#define SLEEPTIME 5
#define MAX_DICE 5
while(1){

	//some blinking, as if rolling
	for(uint8_t i=0;i<=20;i++){
		showSequence(SLEEPTIME);
		sleep(SLEEPTIME);
	}


	//show result	
	uint8_t dice = rand() / (RAND_MAX / MAX_DICE + 1);
	while(1){
		showDice(dice+1);
	}
}

}

