    .intel_syntax noprefix
    .globl hello_asm

    .data
msg:
    .asciz "Hello from Assembly!\n"

    .text
hello_asm:
    lea rax, [rip + msg]  # put address of string in RAX (return value)
    ret
