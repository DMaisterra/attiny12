/* ledblink.c, an LED blinking program at2313a */

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 

#define dirPort DDRD
#define outPin0 PD5
#define outPin1 PD4
#define outPin2 PD3
#define outPort (*((volatile bits_t*)(&PORTD)))

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



//teste gcc
#define set_bits_macro(port,mask) ((port) |= (mask))


char err_str[] = "Your program has lies !";

//teste gcc - fim

volatile bits_t bit_array[1];


void ledOn(uint8_t ledNum){
    switch(ledNum){
    case 0: 
	{outPort &= ~(1<<outPin0);}break;
    }
}

void ledOff(uint8_t ledNum){
    switch(ledNum){
    case 0: 
	{outPort |= (1<<outPin0);}break;
    }
}


void sleep(uint8_t millisec){
    while(millisec){
        _delay_ms(1);
        millisec--;
    }
}

void timer0(void)
{
   TCCR0A = 0x00;                //Timer counter control register
   TCCR0B = (0 << WGM02)|(1 << CS02)|(0 << CS01)|(0 << CS00); // WGM=0, prescale at 8
         TIMSK |= (1 << TOIE0);         //Set bit 1 in TIMSK to enable Timer 1 overflow interrupt.
    }

main(){

    timer0();
    sei();

    //IO output
    dirPort |=(1<<outPin0);
    dirPort |=(1<<outPin1);
    //all IO = 0
    outPort &= ~(1<<outPin0);
    outPort &= ~(1<<outPin1);

    set_bits_macro (outPort, 0xf0);


bit_array[0].b0 = 1;




    while(1){
        ledOn(0);
        //sleep(55);
        sleep(255);
        //ledOff(0);
        sleep(255);
        //sleep(255);
        //sleep(255);
//        sleep(255);
        }
}

ISR (TIMER0_OVF_vect)
{

     outPort.bit5 = bit_array[0].b0 ;

   //ledOff(0);
}
