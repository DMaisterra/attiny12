;.include "tn12def.inc"

;***** Specify Device
;.device ATtiny12

;.include "avr/io.h"
#include <avr/io.h>


;########################
;# Flash Memory         #
;########################
;.cseg               ; (Begin) Code Segment
.org 0x00            ; Start address

   rjmp main         ; Reset Vector
;########################
; Interrupt Vectors      #
; Tiny12            #
;########################
   RETI            ; IRQ0 Handler
   RETI             ; Pin Change Handler
   rjmp tc0i         ; Timer0 overflow
   RETI            ; EEPROM Ready Handler
   RETI             ; Analog Comparitor Handler
main:
;---Port Direction Setup-       
   ldi R16,0b00011000   ; Create input/output states
   out DDRB,R16      ; All ports used for I/O roles
;---Port Initialization--
   ldi R16,0b00011011   ; Pull-up resistors on (PB.5 not equipped)
   out PORTB,R16      ; LED & Alarm on ; No pull-up on IR pin
;---Analog Comparitor Disable
   ldi R16,0b10000000   ; Sent config: [7] Comparitor turn-off
   out ACSR,R16      ; [3] Comparitor interrupt disabled
;---Watchdog Timer Disable
;   ldi R16,0b00010000   ; Sent config: [4] Watchdog turn-off
;   out WDTCR,R16      ; [3] Watchdog disable
;---Timer 0 Interrupt----
   ldi R16,0b00000101   ; Prescale: 1.2MHz / 1024
   out TCCR0,R16      ; Interval: 853us  Overflows: 0.218s

STANDBY:
;---External Interrupt Setup
;   ldi R16,0b01000000   ; Sent config: [6] IRQ0 Enabled
;   out GIMSK,R16      ; [5] Pin-change interrupt disabled
   SEI               ; Global Interrupt Enable
;---Power-down Enable/IRQ Mode
   cbi PORTB,3         ; Alarm latch off
   cbi PORTB,4         ; LED latch off
;   ldi R16,0b00110010   ; Sent config: [5] Sleep Enabled
;   out MCUCR,R16      ; [4] Sleep mode [0,1] falling edge trigger   
;---Micro-power state----
;   sleep            ; Awaken to IRQ0 routine
;---Sleep/IRQ0 Disable---
;   clr R16            ; R16 = 0
;   out GIMSK,R16      ; Sent: [6] IRQ0 Disabled
;   out MCUCR,R16      ; Sent: [5] Sleep Disabled
;---Timer Interrupt Enable
   ldi R16,0b00000010   ; Timer overflow interrupt enable bit set
   out TIMSK,R16      ;
;---Stabilization-Countdown
;   ldi R16,0b00000010      ; Change LED blink rate
;   mov R17,R16      ; New blink rate = ~1.2 Hz
attiny12_iscool:
   rjmp attiny12_iscool                ; <-- LED should be flashing here!

tc0i: ; [Nominal int rate = 4.57Hz]
   in R19,SREG ;save SREG
   inc R18      ; Update counter for main loop codes
;   mov R20,R18   ; Store "timer" to temporary register
;   and R20,R17; Mask to determine LED blink rate   
   andi R18, 0b00000001 ;Mask out lsb
   breq led_off      ; If
led_on:
   sbi PORTB,4         ; LED on
   rjmp led_done
led_off:
   cbi PORTB,4         ; LED off
led_done:
   out SREG,R19
   reti 

