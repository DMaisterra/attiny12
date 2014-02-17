#include <avr/io.h>

#define i r18
#define j r19
#define k r20
#define param1 r21
#define callBlink1 r22


;.equ TIMER_UP, 0xff
;.equ TIMER_LOW, 0xff


;blink n times
.macro _callBlink p count=1
    ldi  callBlink1, \count
	0:
         rcall \p
	 dec callBlink1
        brne 0b
.endm

.macro _wait8
    clr j
    0:
	inc j
	brne 0b
	dec param1
	brne 0b
.endm


.MACRO  _wait16 upper8=1 lower8=255
ldi i, \upper8

0:
ldi j, \lower8

1:
dec j
brne 1b
dec i
brne 0b
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

blk:
_callBlink blink0 4
_callBlink blink 8


;rcall blink0
;rcall blink0
;rcall blink0
rjmp blk
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

blink0:
sbi  _SFR_IO_ADDR(PORTB), 0
rcall delay
cbi  _SFR_IO_ADDR(PORTB), 0
rcall delay
ret

blink:
sbi  _SFR_IO_ADDR(PORTB), 0
rcall delay
cbi  _SFR_IO_ADDR(PORTB), 0
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
ret

delay:
    ;parametrs
    ldi param1,200
    _wait8
    ;hardcoded
    _wait16 255 255
ret

pause:
    ldi param1,1
    _wait8
ret

end:
rjmp end;






