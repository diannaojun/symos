bits 64

section .text
global call, jump, breakpoint
global in8, in16, in32
global out8, out16, out32
global sti, cli, std, cld
global hlt, nop, pass

jump:
    push rdi
    ret
call:
    push rdi
    ret
breakpoint:
    xchg bx, bx
    ret
in8:
    mov rdx, rdi
    xor rax, rax
    in al, dx
    ret
in16:
    mov rdx, rdi
    xor rax, rax
    in ax, dx
    ret
in32:
    mov rdx, rdi
    xor rax, rax
    in eax, dx
    ret
out8:
    mov rdx, rdi
    mov rax, rsi
    out dx, al
    ret
out16:
    mov rdx, rdi
    mov rax, rsi
    out dx, ax
    ret
out32:
    mov rdx, rdi
    mov rax, rsi
    out dx, eax
    ret
hlt:
    hlt
    ret
sti:
    sti
    ret
cli:
    cli
    ret
std:
    std
    ret
cld:
    cld
    ret
pass:
    .step0  jmp .step1
    .step1  jmp .step2
    .step2  nop
    ret
