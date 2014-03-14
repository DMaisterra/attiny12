;http://nerdathome.blogspot.com.br/2008/04/avr-as-usage-tutorial.html

;#include <avr/io.h>
;.include "/usr/share/avra/tn12def.inc"
.INCLUDE "tn12def.inc"

;.device attiny12

.equ PORTB,0x18
.equ DDRB, 0x17

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
cbi DDRB, 0;
cbi DDRB, 3;
;cbi DDRB, 0;
cbi PORTB, 3;
sbi PORTB, 0;;


end:
rjmp end;

