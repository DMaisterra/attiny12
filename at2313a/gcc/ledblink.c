/* ledblink.c, an LED blinking program */
#include <avr/io.h>
#include <util/delay.h>

#define outPort PORTD
#define dirPort DDRD
#define outPin0 PD5
#define outPin1 PD4
#define outPin2 PD3



void sleep(uint8_t millisec)
{
        while(millisec)

        {
                _delay_ms(1);/* 1 ms delay */
                millisec--;
        }
}
main()
{

        dirPort |=(1<<outPin0);  /* PC2 will now be the output pin */
        dirPort |=(1<<outPin1);  /* PC2 will now be the output pin */
        outPort &= ~(1<<outPin1);/* PC2 LOW */

        while(1)
        {
                outPort &= ~(1<<outPin0);/* PC2 LOW */
                sleep(10);/* 100 ms delay */

                outPort |=(1<<outPin0); /* PC2 HIGH */
                sleep(100);/* 100 ms delay */
        }
}

