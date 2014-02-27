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
#define NUMPINS 4 //max 12 leds: n*n-n
#define LED_COUNT 3 //num leds instalados
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


int matrix[LED_COUNT][2][NUMPINS] ={
		{ { IN, IN, OUT, OUT }, { LOW,  LOW, HIGH,LOW } },
		{ { IN, IN, OUT, OUT }, { LOW,  LOW, LOW, HIGH } },
		{ { IN, OUT, IN, OUT }, { LOW,  HIGH, LOW, LOW } }
		//{ { IN, OUT, OUT, IN }, { LOW, HIGH, LOW, LOW } }
}; // AB 0

/*
int matrix[LED_COUNT][2][4] = {
// PIN_CONFIG --- PIN_STATE
// A B C D    --- A B C D
{ { OUTPUT, OUTPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW } }, // AB 0
{ { OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW } }, // BA 1
{ { INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, HIGH, LOW, LOW } }, // BC 2
{ { INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW } }, // CB 3
{ { OUTPUT, INPUT, OUTPUT, INPUT }, { HIGH, LOW, LOW, LOW } }, // AC 4
{ { OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW } }, // CA 5
{ { OUTPUT, INPUT, INPUT, OUTPUT }, { HIGH, LOW, LOW, LOW } }, // AD 6
{ { OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // DA 7
{ { INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, HIGH, LOW, LOW } }; // BD 8

{ { INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // DB 9
{ { INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, HIGH, LOW } }, // CD 10
{ { INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } } // DC 11
};*/

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

	if(inOut==IN){
		dirPort &=~(1<<pin);//triz
	}else{
		dirPort |=(1<<pin);

	}
}


void turnOn( int led ) {
	dirPort = 0xff;//apaga tudo antes de ligar algo. setar saidas todas com zero tbem?

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

int main(){

	timer();
	sei();

#define SLEEPTIME 10
while(1){

	sleep(SLEEPTIME);
	turnOn(0);

	sleep(SLEEPTIME);
	turnOn(1);

	sleep(SLEEPTIME);
	turnOn(2);


}

}

ISR (TIMER1_OVF_vect)
{
	out0 = fb.bit0 ;
	out1 = fb.bit1 ;
	out2 = fb.bit2 ;
}
