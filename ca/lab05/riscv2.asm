# ¹2
.include "macrolib.s"
	.text
main:
	read_int(t0)
	addi t1,zero,10
	bge t0,zero,label1
	neg t0,t0
	label1:
	label2:
		beq t0,zero,label3
		rem t2,t0,t1
		add t3,t3,t2
		div t0,t0,t1
		j label2
	label3:
	print_int(t3)