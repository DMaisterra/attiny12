	.file	"ledblink.c"
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	sleep
	.type	sleep, @function
sleep:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	rjmp .L2
.L3:
	ldi r30,lo8(249)
	ldi r31,hi8(249)
	1: sbiw r30,1
	brne 1b
	rjmp .
	nop
	subi r24,lo8(-(-1))
.L2:
	cpse r24,__zero_reg__
	rjmp .L3
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
	cbi 0x12,4
.L5:
	cbi 0x12,5
	ldi r24,lo8(10)
	rcall sleep
	sbi 0x12,5
	ldi r24,lo8(100)
	rcall sleep
	rjmp .L5
	.size	main, .-main
	.ident	"GCC: (GNU) 4.7.0"
