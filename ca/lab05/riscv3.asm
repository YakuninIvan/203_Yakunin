# ¹3
.include "macrolib.s"
	.text
main:
	read_int(t0)
	addi t2,t2,1
	label1:
		beq t0,zero,label2
		addi t0,t0,-1
		read_int(t1)
		mul t1,t1,t2
		neg t2,t2
		add t3,t3,t1
		j label1
	label2:
	print_int(t3)
	li a7,10
	ecall