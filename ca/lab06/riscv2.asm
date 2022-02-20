# ¹2 CheckTriangles
    .include "macrolib.s"
    .data
data_start:
	.word 0
data_end:
	.text
main:

        addi t1, zero, 1
        addi t2, zero, 2
        
    loop:
        read_int(a1)
        read_int(a2)
        read_int(a3)
        jal checktriangles
        beq a0, t1, true
        beq a0, t2, false
        beq a0, zero, output
        j loop

    checktriangles:
        add a4, a1, a2
        add a5, a1, a3
        add a6, a2, a3
        add a7, a6, a1
        beq a7, zero, zero_case
        bgt a3, a4, label2
        bgt a2, a5, label2
        bgt a1, a6, label2
        j label1
        jr ra
        
        label1:
        	addi a0, zero, 1
        	jr ra
	label2:
        	addi a0, zero, 2
        	jr ra
	zero_case:
        	add a0, zero, zero
        	jr ra
	true:
        	li a7, 1
        	sw a7, (sp)
        	addi sp, sp, 4
        	addi t0, t0, 1
        	j loop
 	false:
        	li a7, 0
        	sw a7, (sp)
        	addi sp, sp, 4
        	addi t0, t0, 1
        	j loop
	output:
		beq t0, zero, exit
        	addi t0, t0, -1
        	lw a0, (sp)
        	addi sp, sp, -4
        	beq a0, zero, print_true
        	bne a0, zero, print_false
        	j output
	
	print_true:
        	print_char('Y')
        	newline
        j output
        
        print_false:
        	print_char('N')
        	newline
        	j output
        
	exit:
        	li a7, 10
        	ecall
