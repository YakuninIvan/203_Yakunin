# task 3 #2
	.text
main:
	addi a7, zero, 5
	ecall
	add t0, zero, a0
	addi a7, zero, 5
	ecall
	add t1, zero, a0
	mul t0,t0,t1
	li a7, 1
	mv a0, t0
	ecall