/* ledblink.c, an LED blinking program at2313a */
//http://makezine.com/projects/charlieplexing-leds-with-an-avr-atmega328-or-arduino/

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 

#define HIGH 1
#define LOW 0
#define IN 0
#define OUT 1
#define NUMPINS 4 //max leds: n*n-n (4 pins, 12 leds max)
#define LED_COUNT 9 //num leds total
#define PIN_CONFIG 0
#define PIN_STATE 1


#define dirPort DDRD

#define outPin0 PD2
#define outPin1 PD3
#define outPin2 PD4
#define outPin3 PD5

#define  out0 outPort.bit2
#define  out1 outPort.bit3
#define  out2 outPort.bit4
#define  out3 outPort.bit5

#define dirPort1 (*((volatile bits_t*)(&DDRD)))
#define outPort (*((volatile bits_t*)(&PORTD)))
#define fb frameBuffer[0]

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

volatile bits_t frameBuffer[1];


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

void debug(int zeroUm){

	int sleepTime;
	if(zeroUm==0){
		sleepTime = 255;
	}else{
		sleepTime = 75;
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


void pinMode(int pin, int inOut){
//debug(inOut);
	if(inOut==IN){
		dirPort &=~(1<<pin);//input (tristate)
	}else{
		dirPort |=(1<<pin);//output

	}
}


void turnOn(int led ) {
	//dirPort = 0x00;//apaga tudo antes de ligar algo. setar saidas todas com zero tbem?
	//PORTD = 0x00; //TODO 

pinMode( outPin0, matrix[led][PIN_CONFIG][0] );
pinMode( outPin1, matrix[led][PIN_CONFIG][1] );
pinMode( outPin2, matrix[led][PIN_CONFIG][2] );
pinMode( outPin3, matrix[led][PIN_CONFIG][3] );

	out0 = matrix[led][PIN_STATE][0] ;
	out1 = matrix[led][PIN_STATE][1] ;
	out2 = matrix[led][PIN_STATE][2] ;
	out3 = matrix[led][PIN_STATE][3] ;
}

void timer(void)
{
	TCCR1A = 0x00;                //Timer counter control register
	TCCR1B = (0 << WGM02)|(1 << CS02)|(0 << CS01)|(0 << CS00); // WGM=0, prescale at 8
	TIMSK |= (1 << TOIE1);         //Set bit 1 in TIMSK to enable Timer 1 overflow interrupt.
}

int main(void){

	timer();
	//sei();

#define SLEEPTIME 95
while(1){

	sleep(SLEEPTIME);
	turnOn(0);

	sleep(SLEEPTIME);
	turnOn(1);

	sleep(SLEEPTIME);
	turnOn(2);

	sleep(SLEEPTIME);
	turnOn(3);

	sleep(SLEEPTIME);
	turnOn(4);

	sleep(SLEEPTIME);
	turnOn(5);

	sleep(SLEEPTIME);
	turnOn(6);

	sleep(SLEEPTIME);
	turnOn(7);

	sleep(SLEEPTIME);
	turnOn(8);

}

}

ISR (TIMER1_OVF_vect)
{
	out0 = fb.bit0 ;
	out1 = fb.bit1 ;
	out2 = fb.bit2 ;
}
