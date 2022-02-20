 # ¹1 ASC||Grid
     .include "macrolib.s"
     
     .macro printline (%x, %y, %z)
     mv a1, %x
     label:
     li a7, 11
     li a0, %y
     ecall
     li a0, %z
     ecall
     addi a1, a1, -1
     bne a1, zero, label
     li a0, %y
     ecall
     .end_macro
   
     .text
 main:
     read_int(t0)
     read_int(t1)
     loop:
         printline t0, '+', '-'
         newline
         printline t0, '|', ' '
         newline
         addi t1, t1, -1
         bne t1, zero, loop
    printline t0, '+', '-'
    li a7, 10
    ecall