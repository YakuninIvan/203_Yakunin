.include "macrolib.s"
.text
main:
	read_double (ft1)
	read_double (ft2)
	read_int (t0)
	mv a0, t0
 	fdiv.d fa0, ft1, ft2
	call round
	print_double(fa0)
	j end
    
round:
	addi a1, zero, 10
	fcvt.d.w fa1, a1
	addi a1, zero, 1
	fcvt.d.w fa2, a1
	loop:
        	beq a0, zero, end_funñ
        	addi a0, a0, -1
        	fmul.d fa2, fa2, fa1
        	j loop
	end_funñ:
	fmul.d fa0, fa0, fa2
	fcvt.w.d a0, fa0
	fcvt.d.w fa0, a0
	fdiv.d fa0, fa0, fa2
	ret

end:
	li a7, 10
	ecall
    