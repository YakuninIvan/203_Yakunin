# ¹3 FuncSort
.include "macrolib.s"

	.data
data_start:
     .word 0
data_end:
     .text
     
main:
	read_int(t1)
	la t5, data_start
	loop:
		beqz t1, update_pointer
		read_int(t2)
		sw t2, (t5)
		addi t5,t5,4
		addi t1,t1, -1
		j loop
	update_pointer:
		la a0, data_start
		la a1, data_end
		jal bubble_sort
	output:
		beq t6,t5, end
		lw t2, (t6)
		print_int(t2)
		newline
		addi t6, t6, 4
		j output
		
	end:
		li a7, 10
		ecall
bubble_sort:
	loop2:
		beq a0, a1, end_step
		lw a2, (a0)
		addi a0, a0, 4
		lw a3, (a0)
		bgt a2, a3 , swap
		
	swap:
		addi a0, a0, -4
		sw a3, (a0)
		addi a0, a0, 4
		sw a2, (a0)
		j loop2
		
	end_step:
		la a0, data_start
		addi a1, a1, -4
		beq a1,a0, end_func
		j loop2
		
	end_func:
		jr ra
	