/* ledblink.c, an LED blinking program at2313a */

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define outPort PORTD
#define dirPort DDRD
#define outPin0 PD5
#define outPin1 PD4
#define outPin2 PD3



void onLed(uint8_t ledNum){
    switch(ledNum++){
    case 0: {
	outPort &= ~(1<<outPin0);break;
    }
    
    }
}




void sleep(uint8_t millisec){
    while(millisec){
        _delay_ms(1);
        millisec--;
    }
}




main(){
    dirPort |=(1<<outPin0);
    dirPort |=(1<<outPin1);
    outPort &= ~(1<<outPin0);
    outPort &= ~(1<<outPin1);

    while(1){
        outPort &= ~(1<<outPin0);
        sleep(255);
        sleep(255);
        outPort |=(1<<outPin0);
        sleep(255);
        sleep(255);
        sleep(255);
        sleep(255);
        }
}

