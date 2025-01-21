bits 64

section .text
global call, jump, breakpoint

jump:
    push rdi
    ret
call:
    push rdi
    ret
breakpoint:
    xchg bx, bx
    ret
