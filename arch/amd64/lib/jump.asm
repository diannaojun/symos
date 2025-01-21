bits 64

section .text
global call, jump

jump:
    push rdi
    ret

call:
    push rdi
    ret
