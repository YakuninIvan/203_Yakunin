   .macro print_imm_int (%x)
   li a7, 1
   li a0, %x
   ecall
   .end_macro

   .macro read_int(%x)
   li a7, 5
   ecall
   mv %x, a0
   .end_macro
  
  .macro print_int(%x)
  li a7, 1
  mv a0, %x
  ecall
  .end_macro
   
   .macro read_float(%x)
   li a7, 6
   ecall
   fmv.s %x, fa0
   .end_macro
   
   .macro print_float(%x)
   li a7, 2
   fmv.s fa0, %x
   ecall
   .end_macro
   
   .macro read_double(%x)
   li a7, 7
   ecall
   fmv.d %x, fa0
   .end_macro
   
   .macro print_double(%x)
   li a7, 3
   fmv.s fa0, %x
   ecall
   .end_macro

   .macro print_str (%x)
   .data
str:
   .asciz %x
   .text
   li a7, 4
   la a0, str
   ecall
   .end_macro

   .macro print_char(%x)
   li a7, 11
   li a0, %x
   ecall
   .end_macro

   .macro newline
   print_char('\n')
   .end_macro
   
   .macro push(%x)
   addi sp, sp, -4
   sw %x, 0(sp)
   .end_macro
   
   .macro pop(%x)
   lw %x, 0(sp)
   addi sp, sp, 4
   .end_macro
   
   .macro push_float
   addi, sp, sp, -4
   fsw %x, 0(sp)
   .end_macro
   
   .macro pop_float(%x)
   flw %x, 0(sp)
   addi sp, sp, 4
   .end_macro
