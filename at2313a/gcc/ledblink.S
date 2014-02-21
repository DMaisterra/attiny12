	.file	"ledblink.c"
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	onLed
	.type	onLed, @function
onLed:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	cpse r24,__zero_reg__
	rjmp .L1
	cbi 0x12,5
.L1:
	ret
	.size	onLed, .-onLed
.global	sleep
	.type	sleep, @function
sleep:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	rjmp .L5
.L6:
	ldi r30,lo8(249)
	ldi r31,hi8(249)
	1: sbiw r30,1
	brne 1b
	rjmp .
	nop
	subi r24,lo8(-(-1))
.L5:
	cpse r24,__zero_reg__
	rjmp .L6
/* epilogue start */
	ret
	.size	sleep, .-sleep
	.section	.text.startup,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	sbi 0x11,5
	sbi 0x11,4
	cbi 0x12,5
	cbi 0x12,4
.L8:
	cbi 0x12,5
	ldi r24,lo8(-1)
	rcall sleep
	ldi r24,lo8(-1)
	rcall sleep
	sbi 0x12,5
	ldi r24,lo8(-1)
	rcall sleep
	ldi r24,lo8(-1)
	rcall sleep
	ldi r24,lo8(-1)
	rcall sleep
	ldi r24,lo8(-1)
	rcall sleep
	rjmp .L8
	.size	main, .-main
	.ident	"GCC: (GNU) 4.7.0"
