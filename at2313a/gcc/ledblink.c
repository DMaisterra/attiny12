/* ledblink.c, an LED blinking program at2313a */

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define outPort PORTD
#define dirPort DDRD
#define outPin0 PD5
#define outPin1 PD4
#define outPin2 PD3


typedef struct {
 unsigned char b0:1;
 unsigned char b1:1;
 unsigned char b2:1;
 unsigned char b3:1;
 unsigned char b4:1;
 unsigned char b5:1;
 unsigned char b6:1;
 unsigned char b7:1;
} bits_t;



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


main(){
    //IO output
    dirPort |=(1<<outPin0);
    dirPort |=(1<<outPin1);
    //all IO = 0
    outPort &= ~(1<<outPin0);
    outPort &= ~(1<<outPin1);


bits_t bit_array[10];

bit_array[1].b3 = 1;


    while(1){
        ledOn(0);
        sleep(255);
        sleep(255);
        ledOff(0);
        sleep(255);
        sleep(255);
//        sleep(255);
//        sleep(255);
        }
}

