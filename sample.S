#include <avr/io.h>

#define i r22
#define j r23
#define k r24


.equ TIMER_UP, 0xff
.equ TIMER_LOW, 0xff


.MACRO        _DELAY16
ldi i, TIMER_UP

_d16_1:
ldi j, TIMER_LOW

_d16_2:
dec j
brne _d16_2
dec i
brne _d16_1
.ENDM

.MACRO  _DELAY8
     clr i
   _d8:
     nop
     dec i
     brne _d8
.ENDM



.org 0x00
rjmp main;
   RETI            ; IRQ0 Handler
   RETI             ; Pin Change Handler
   reti;rjmp tc0i         ; Timer0 overflow
   RETI            ; EEPROM Ready Handler
   RETI             ; Analog Comparitor Handler

;;;;;;;;;;;;;;;;;;;;;;;;MAIN
main:
;init
;0 e 3 saidas IO
sbi  _SFR_IO_ADDR(DDRB), 0
sbi  _SFR_IO_ADDR(DDRB), 3
;cbi  _SFR_IO_ADDR(PORTB), 3

;blink0 n times
;ldi  r24,5
;   _m:
;     rjmp blink
;     dec r24
;     brne _m

;rjmp blink0
rjmp blink
;rjmp blink0
;rjmp blink
rjmp end
;rjmp main
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

blink0:
sbi  _SFR_IO_ADDR(PORTB), 0
rcall delay
cbi  _SFR_IO_ADDR(PORTB), 0
rcall delay
;rjmp blink0
ret

blink:
cbi  _SFR_IO_ADDR(PORTB), 0
rcall delay
sbi  _SFR_IO_ADDR(PORTB), 0
;rcall delay
rcall pause
rcall pause
rcall pause
;rjmp blink
ret

delay:
    _DELAY16
ret

pause:
    _DELAY8
ret

end:
rjmp end;






