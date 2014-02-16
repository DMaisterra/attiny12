#include <avr/io.h>

.equ TIMER_UP, 0x25
.equ TIMER_LOW, 0xff


.MACRO        MCR_DELAY
ldi r16, TIMER_UP

loopM1:
ldi r17, TIMER_LOW

loopM2:
dec r17
brne loopM2
dec r16
brne loopM1
;ret

;              LDI    @0, low(@1)
;              OUT    SPL, @0
;              LDI    @0, high(@1)
;              OUT    SPH, @0
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
rjmp cfg;


cfg:
;0 e 3 saidas IO
sbi  _SFR_IO_ADDR(DDRB), 0
sbi  _SFR_IO_ADDR(DDRB), 3

blink:
sbi  _SFR_IO_ADDR(PORTB), 0
rcall delay
cbi  _SFR_IO_ADDR(PORTB), 0
rcall delay
rjmp blink


delay:
    MCR_DELAY
ret


end:
rjmp end;






