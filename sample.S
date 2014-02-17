#include <avr/io.h>

#define i r18
#define j r19
#define k r20
#define param1 r21
#define callBlink1 r22


.equ TIMER_UP, 0xff
.equ TIMER_LOW, 0xff


;blink n times
.macro callBlink p count=1
    ldi  callBlink1, \count
	0:
         rcall \p
	 dec callBlink1
        brne 0b
.endm

.macro wait
    clr j
    0:
	inc j
	brne 0b
	dec param1
	brne 0b
.endm


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

blk:
callBlink blink0 4
callBlink blink 8


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
    ldi param1,200
    WAIT
;    _DELAY16
ret

pause:
    _DELAY8
ret

end:
rjmp end;






