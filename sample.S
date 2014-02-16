#include <avr/io.h>

.equ TIMER_UP, 0xff
.equ TIMER_LOW, 0xff


.MACRO        _DELAY16
ldi r16, TIMER_UP

loopM1:
ldi r17, TIMER_LOW

loopM2:
dec r17
brne loopM2
dec r16
brne loopM1
.ENDM

.MACRO  _DELAY8
     clr r22
   _d8:
     nop
     dec r22
     brne _d8
.ENDM



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
;init
;0 e 3 saidas IO
sbi  _SFR_IO_ADDR(DDRB), 0
sbi  _SFR_IO_ADDR(DDRB), 3

blink:
sbi  _SFR_IO_ADDR(PORTB), 0
rcall delay
cbi  _SFR_IO_ADDR(PORTB), 0
rcall delay
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rcall pause
rjmp blink


delay:
    _DELAY16
ret

pause:
    _DELAY8
ret



end:
rjmp end;






