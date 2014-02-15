;http://nerdathome.blogspot.com.br/2008/04/avr-as-usage-tutorial.html

#include <avr/io.h>
;.include "/usr/share/avra/tn12def.inc"
;.INCLUDE "tn12def.inc"

;.device attiny12

;.equ PORTB,0x18
;.equ DDRB, 0x17

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
;0 e # saidas IO
sbi  _SFR_IO_ADDR(DDRB), 0
sbi  _SFR_IO_ADDR(DDRB), 3

cbi  _SFR_IO_ADDR(PORTB), 3
sbi  _SFR_IO_ADDR(PORTB), 0
rjmp loopB


;long loop 
loopB:
ldi r16, 0xf

loop1:
ldi r17, 0xf

loop2:
dec r17
brne loop2
dec r16
brne loop1
sbi  _SFR_IO_ADDR(PORTB), 0 ;cbi ddrb, 5
ldi r16, 0xf

loop3:
ldi r17, 0xf

loop4:
dec r17
brne loop4
dec r16
brne loop3
cbi  _SFR_IO_ADDR(PORTB), 0 ;sbi ddrb, 5
rjmp loopB

end:
rjmp end;






