# task 1 #2

    .data
str:
       .asciz "Hello, ACOS"
       .text
main:
    li a7, 4
    la a0, str
    ecall