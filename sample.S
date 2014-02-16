#include <avr/io.h>

.MACRO        LSP
              LDI    @0, low(@1)
              OUT    SPL, @0
              LDI    @0, high(@1)
              OUT    SPH, @0
.ENDM

.equ TIMER_UP, 0x55
.equ TIMER_LOW, 0xff


.org 0x00
reset:
rjmp main;
rjmp defaultInt;
rjmp defaultInt;
rjmp defaultInt;
rjmp defaultInt;
rjmp defaultInt;
rjmp defaultInt;
rjmp defaultInt;
rjmp defaultInt;
rjmp defaultInt;
rjmp defaultInt;
rjmp defaultInt;
rjmp defaultInt;
rjmp defaultInt;
rjmp defaultInt;

defaultInt:
reti;

main:
rjmp cfg;


cfg:
;0 e 3 saidas IO
sbi  _SFR_IO_ADDR(DDRB), 0
sbi  _SFR_IO_ADDR(DDRB), 3

cbi  _SFR_IO_ADDR(PORTB), 3
sbi  _SFR_IO_ADDR(PORTB), 0
;rjmp loopB

loopMacro:
ldi r16, TIMER_LOW

loopM1:
ldi r17, TIMER_UP

loopM2:
dec r17
brne loopM2
dec r16
brne loopM1
sbi  _SFR_IO_ADDR(PORTB), 0 ;cbi ddrb, 5
ldi r16,  TIMER_LOW

loopM3:
ldi r17,  TIMER_UP

loopM4:
dec r17
brne loopM4
dec r16
brne loopM3
cbi  _SFR_IO_ADDR(PORTB), 0 ;sbi ddrb, 5
rjmp loopMacro



;long loop 
loopB:
ldi r16, 0xff

loop1:
ldi r17, 0xff

loop2:
dec r17
brne loop2
dec r16
brne loop1
sbi  _SFR_IO_ADDR(PORTB), 0 ;cbi ddrb, 5
ldi r16, 0xff

loop3:
ldi r17, 0xff

loop4:
dec r17
brne loop4
dec r16
brne loop3
cbi  _SFR_IO_ADDR(PORTB), 0 ;sbi ddrb, 5
rjmp loopB

end:
rjmp end;






