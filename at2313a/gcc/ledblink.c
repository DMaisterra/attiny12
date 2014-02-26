/* ledblink.c, an LED blinking program at2313a */

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 

#define ON 1
#define OFF 0
#define dirPort DDRD

#define outPin0 PD3
#define outPin1 PD4
#define outPin2 PD5
#define  out0 outPort.bit3
#define  out1 outPort.bit4
#define  out2 outPort.bit5

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


void sleep(uint8_t millisec){
	while(millisec){
		_delay_ms(1);
		millisec--;
	}
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




	while(1){

		//dirPort &=~(1<<outPinX);//input triz
		//dirPort |=(1<<outPinX); //output


		dirPort &=~(1<<outPin0);//triz
		dirPort |=(1<<outPin1);
		dirPort |=(1<<outPin2);

		//LED 0
		out1 = ON;
		out2 = OFF;
		sleep(255);

		//LED1
		out1 = OFF;
		out2 = ON;
		sleep(255);

		dirPort |=(1<<outPin0);
		dirPort &=~(1<<outPin1);//triz
		dirPort |=(1<<outPin2);

		//LED 3
		out0 = ON;
		out2 = OFF;
		sleep(255);

		//LED4
		out0 = OFF;
		out2 = ON;
		sleep(255);



	}

}

ISR (TIMER1_OVF_vect)
{
	out0 = fb.bit0 ;
	out1 = fb.bit1 ;
	out2 = fb.bit2 ;
}
