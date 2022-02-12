# ¹1
.include "macrolib.s"
	.text
main:
	addi a7,zero,5
	ecall
	add t0,zero,a0	
	addi a7,zero,5
	ecall
	add t1,zero,a0	
	addi a7,zero,5
	ecall
	add t2,zero,a0	
	addi a7,zero,5
	ecall
	add t3,zero,a0
	add t1,t1,t3
	add t0,t0,t2
	li a7,1
	mv a0,t0
	ecall
	newline
	li a7,1
	mv a0,t1
	ecall
	li a7,10
	ecall