#include <avr/io.h>

#define i r18
#define j r19
#define k r20
#define param1 r21
#define callBlink1 r22


;atTiny12
#define outPort PORTB
#define dirPort DDRB
#define outPin0 0
#define outPin1 3

;atTiny2313
;#define outPort PORTD
;#define dirPort DDRD
;#define outPin0 5
;#define outPin1 4


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
   rjmp tc0i         ; Timer0 overflow
   RETI            ; EEPROM Ready Handler
   RETI             ; Analog Comparitor Handler

;;;;;;;;;;;;;;;;;;;;;;;;MAIN
main:

;init
;saidas IO
sbi  _SFR_IO_ADDR(dirPort), outPin0
sbi  _SFR_IO_ADDR(dirPort), outPin1

rjmp blk2
rjmp end

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

configTimerTiny12:
;---Timer 0 Interrupt----
    ldi R16,0b00000101   ; Prescale: 1.2MHz / 1024
    out _SFR_IO_ADDR(TCCR0), R16 ; Interval: 853us  Overflows: 0.218s
    sei ; enable ints
;---Timer Interrupt Enable
    ldi R16,0b00000010   ; Timer overflow interrupt enable bit set
    out _SFR_IO_ADDR(TIMSK),R16
ret


blink0:
sbi  _SFR_IO_ADDR(outPort), outPin0
rcall delay
cbi  _SFR_IO_ADDR(outPort), outPin0
rcall delay
ret

blink:
sbi  _SFR_IO_ADDR(outPort), outPin0
rcall delay
cbi  _SFR_IO_ADDR(outPort), outPin0
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



blk1:
;_callBlink blink0 4
_callBlink blink 8
rjmp blk1

blk2:
_callBlink blink0 1
_callBlink blink 4
rjmp blk2



tc0i: 
; rjmp blk1
;reti

; [Nominal int rate = 4.57Hz]
   in R19 ,_SFR_IO_ADDR(SREG) ;save SREG
   inc R18      ; Update counter for main loop codes
;   mov R20,R18   ; Store "timer" to temporary register
;   and R20,R17; Mask to determine LED blink rate   
   andi R18, 0b00000001 ;Mask out lsb
   breq led_off      ; If
led_on:
   sbi _SFR_IO_ADDR(outPort), outPin0        ; LED on
   rjmp led_done
led_off:
   cbi _SFR_IO_ADDR(outPort), outPin0        ; LED off
led_done:
   out _SFR_IO_ADDR(SREG),R19
   reti 



end:
rjmp end;






