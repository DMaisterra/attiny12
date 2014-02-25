	.file	"ledblink.c"
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	ledOn
	.type	ledOn, @function
ledOn:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	cpse r24,__zero_reg__
	rjmp .L1
	cbi 0x12,5
.L1:
	ret
	.size	ledOn, .-ledOn
.global	ledOff
	.type	ledOff, @function
ledOff:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	cpse r24,__zero_reg__
	rjmp .L4
	sbi 0x12,5
.L4:
	ret
	.size	ledOff, .-ledOff
.global	sleep
	.type	sleep, @function
sleep:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	rjmp .L8
.L9:
	ldi r30,lo8(249)
	ldi r31,hi8(249)
	1: sbiw r30,1
	brne 1b
	rjmp .
	nop
	subi r24,lo8(-(-1))
.L8:
	cpse r24,__zero_reg__
	rjmp .L9
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
.L11:
	ldi r24,0
	rcall ledOn
	ldi r24,lo8(-1)
	rcall sleep
	ldi r24,lo8(-1)
	rcall sleep
	ldi r24,0
	rcall ledOff
	ldi r24,lo8(-1)
	rcall sleep
	ldi r24,lo8(-1)
	rcall sleep
	rjmp .L11
	.size	main, .-main
.global	err_str
	.data
	.type	err_str, @object
	.size	err_str, 24
err_str:
	.string	"Your program has lies !"
	.ident	"GCC: (GNU) 4.7.0"
.global __do_copy_data
