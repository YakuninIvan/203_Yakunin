#
# Example that demonstrates MMIO in Digital Lab Sim.
#
# It works with hexadecimal keyword.
#
# See Help on Digital Lab Sim for details.
#
	.macro exit
li 	a7, 10
ecall
	.end_macro

	.macro print_hex(%x)
mv 	a0, %x
li 	a7, 34
ecall
	.end_macro

	.macro newline
li 	a0, '\n'
li 	a7, 11
ecall
	.end_macro
	
	.macro read_int(%x)
li	a7, 5
ecall
mv 	%x, a0
  	.end_macro
  	
  	.macro print_str (%x)
   	.data
str:
   	.asciz %x
   	.text
li 	a7, 4
la 	a0, str
ecall
   .end_macro

	.data
display_start:
	.word 	0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f
display_end:
key_start:
	.word	0x11, 0x21, 0x41, 0xffffff81, 0x12, 0x22, 0x42, 0xffffff82, 0x14, 0x24, 0x44, 0xffffff84, 0x18, 0x28, 0x48, 0xffffff88
key_end:

    	.text
main:

	read_int(s4)

	lui s0, 0xffff0   	# MMIO base
    	mv s1, zero      	# counter
    	mv s2, zero      	# previous value
    	li s3, 20        	# counter limit
loop:
    	li t0, 1         	# check first row
    	sb t0, 0x12(s0)  	# scan
    	lb t1, 0x14(s0)  	# get result
    	bnez t1, pressed   	# process key pressed

    	li t0, 2         	# check second row
    	sb t0, 0x12(s0)
    	lb t1, 0x14(s0)
    	bnez t1, pressed
    	li t0, 4         	# check third row
    	sb t0, 0x12(s0)
    	lb t1, 0x14(s0)
    	bnez t1, pressed
    	li t0, 8         	# check fourth row
    	sb t0, 0x12(s0)
    	lb t1, 0x14(s0)
    	bnez t1, pressed
    	mv s2, zero  	# reset previous value
    	j loop  		# nothing is pressed (t1 == 0) - repeat
pressed:
    	beq t1, s2, loop 	# repeat if the same key value
    	mv s2, t1 		# save current value

    	# Prints the pressed key in format 0xXY, where X is column, Y is row.
    	# Both X and Y are specified as bit flags (0x1, 0x2, 0x4, 0x8).
    	# Bit position means the number of row/column (0x1 -> 1, 0x2 -> 2, 0x4 -> 3, x8 -> 4).
	
	la t0, key_start
	lw t5, (t0)
	add t6, zero, zero
	pressed_loop:
		beq t1, t5, printDig
		addi t0, t0, 4
		lw t5, (t0)
		addi t6, t6, 1
		j pressed_loop
	printDig:
	
	beq t6, s4, found
	beq t6, zero, stopped
    	addi s1, s1, 1    	# counter increment
    	ble s1, s3, loop 	# repeat if s1 <= s3
    	
found:
	print_str("FOUND")
	j end

stopped:
	print_str("STOPPED")
	j end

end:
    	exit
