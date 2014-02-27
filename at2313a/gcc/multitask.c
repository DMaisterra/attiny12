#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define PRIO_1 0
#define PRIO_2 1
#define PRIO_3 2
#define PRIO_4 3
#define PRIO_5 4
#define PRIO_6 5
#define PRIO_7 6
#define PRIO_8 7

void tasker_init(void);
void task_dispatch(void);
void prio1_task(void);
void prio2_task(void);
void prio3_task(void);
void prio4_task(void);
void prio5_task(void);
void prio6_task(void);
void prio7_task(void);
void prio8_task(void);

typedef void(*f_ptr_t)(void);

f_ptr_t const tasks[] PROGMEM = {
 (f_ptr_t) prio1_task,
 (f_ptr_t) prio2_task,
 (f_ptr_t) prio3_task,
 (f_ptr_t) prio4_task,
 (f_ptr_t) prio5_task,
 (f_ptr_t) prio6_task,
 (f_ptr_t) prio7_task,
 (f_ptr_t) prio8_task
};

#define NUM_TASKS (sizeof(tasks)/sizeof(tasks[0]))

volatile uint8_t task_flag = 0; /* if non-zero, a tick has elapsed */
uint8_t task_timer[NUM_TASKS];

ISR(TIMER0_COMPA_vect)
{
 static uint8_t tasker_ticks = 0;

 if (++tasker_ticks == 10)
 {
  task_flag = 1;         /* scan tasks every 10 ms */
  tasker_ticks = 0;
 }
}

void tasker_init(void)
{
   /* port 0..5 as outputs */
 DDRB = _BV(PB5)|_BV(PB4)|_BV(PB3)|_BV(PB2)|_BV(PB1)|_BV(PB0);
 TCCR0A = _BV(WGM01);   /* CTC mode */
 OCR0A = 250;           /* 1 ms @ 16 MHz and prescaler = 64 */
 TIMSK0 = _BV(OCIE0A);   /* Enable Timer/Counter0 Compare Match A interrupt */
 TCCR0B = _BV(CS00) | _BV(CS01); /* prescaler 64, start timer */

 /* experimental attempt to spread the (initial dispatch of) tasks */
 uint8_t prime_number[]={2, 3, 5, 7, 11, 13, 17, 19};

 for(int i = 0; i< NUM_TASKS; i++)
 {
  task_timer[i] = prime_number[i & 0x07];
 }
 sei();
}

void prio1_task(void)
{
 task_timer[PRIO_1] = 10; /*(placeholder) unused in this example*/
}

void prio2_task(void)
{
 task_timer[PRIO_2] = 10; /*(placeholder) unused in this example*/
}

void prio3_task(void)
{
 PORTB ^= _BV(PB0);
 task_timer[PRIO_3] = 10; /* every 100ms */
}

void prio4_task(void)
{
 PORTB ^= _BV(PB1);
 task_timer[PRIO_4] = 20; /* every 200ms */
}

void prio5_task(void)
{
 PORTB ^= _BV(PB2);
 task_timer[PRIO_5] = 30; /* every 300ms */
}

void prio6_task(void)
{
 PORTB ^= _BV(PB3);
 task_timer[PRIO_6] = 40; /* every 400ms */
}

void prio7_task(void)
{
 PORTB ^= _BV(PB4);
 task_timer[PRIO_7] = 50; /* every 500ms */
}

void prio8_task(void)
{
 PORTB ^= _BV(PB5);
 task_timer[PRIO_8] = 60; /* every 600ms */
}

void task_dispatch(void)
{
 f_ptr_t fptr;
 for (uint8_t task = 0; task < NUM_TASKS; task++)
 {
  if (task_timer[task])
  {
   if (!--task_timer[task])
   {
    fptr = (f_ptr_t)pgm_read_word(&tasks[task]);
    fptr();
   }
  }
 }
}

int main( void )
{
 tasker_init();

 while(1)
 {
  if (task_flag)
  {
   task_flag = 0;
   task_dispatch();
  }
 }
}





