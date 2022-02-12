# ¹4
.include "macrolib.s"
	.text
.macro push(%x)
    addi sp, sp, -4
    sw %x, 0(sp)
.end_macro 
    
.macro pop(%x)
    lw %x, 0(sp)
    addi sp, sp, 4
.end_macro

    .text
main:
	read_int(t1)
	addi t2,t2,2
	label1:
		beq t1,zero,label2
		addi, t1,t1,-1
		read_int(t3)
		rem t4,t3,t2
		beq t4,zero,label3
		j label1
	label3:
		addi t5,t5,1
		push(t3)
		j label1
	label2:
		beq t5,zero,label4
		addi t5,t5,-1
		pop(t1)
		print_int(t1)
		newline
		j label2
	label4:
		li a7,10
		ecall