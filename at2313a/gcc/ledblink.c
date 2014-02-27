/* ledblink.c, an LED blinking program at2313a */

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 

#define HIGH 1
#define LOW 0
#define NUMPINS 4 //max 12 leds: n*n-n
#define LED_COUNT 12 //num leds instalados

#define dirPort DDRD
#define outPin3 PD2
#define outPin2 PD3
#define outPin1 PD4
#define outPin0 PD5

#define  out3 outPort.bit2
#define  out2 outPort.bit3
#define  out1 outPort.bit4
#define  out0 outPort.bit5

#define outPort (*((volatile bits_t*)(&PORTD)))
//#define fb frameBuffer[0]

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


int matrix[LED_COUNT][2][NUMPINS] = {};

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

/*
void sleep(uint8_t millisec){
	while(millisec){
		_delay_ms(1);
		millisec--;
	}
}

void allTriz(){
	dirPort =0xff;
}

void timer(void)
{
	TCCR1A = 0x00;                //Timer counter control register
	TCCR1B = (0 << WGM02)|(1 << CS02)|(0 << CS01)|(0 << CS00); // WGM=0, prescale at 8
	TIMSK |= (1 << TOIE1);         //Set bit 1 in TIMSK to enable Timer 1 overflow interrupt.
}
*/
int main(){

	//timer();
	//sei();


	//dirPort &=~(1<<outPin0);//triz
	//allTriz();
	/*dirPort |=(1<<outPin0);
	dirPort |=(1<<outPin1);
	dirPort |=(1<<outPin2);
	dirPort |=(1<<outPin3);

	//LED 0
	out1 = HIGH;
	out0 = LOW;
*/
	dirPort |=(1<<PD5);
	dirPort |=(1<<PD4);
	out0 = HIGH;
	out1 = LOW;
/*
	while(0){

		//dirPort &=~(1<<outPinX);//input triz
		//dirPort |=(1<<outPinX); //output


		dirPort &=~(1<<outPin0);//triz
		dirPort |=(1<<outPin1);
		dirPort |=(1<<outPin2);

		//LED 0
		out1 = HIGH;
		out2 = LOW;
		sleep(255);


		//LED1
		out1 = LOW;
		out2 = HIGH;
		sleep(255);

		dirPort |=(1<<outPin0);
		dirPort &=~(1<<outPin1);//triz
		dirPort |=(1<<outPin2);

		//LED 3
		out0 = HIGH;
		out2 = LOW;
		sleep(255);

		//LED4
		out0 = LOW;
		out2 = HIGH;
		sleep(255);

	}
*/
}

//ISR (TIMER1_OVF_vect)
//{
	//out0 = fb.bit0 ;
	//out1 = fb.bit1 ;
	//out2 = fb.bit2 ;
//}
