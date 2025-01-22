bits 64

section .text
global call, call_far
global jump, jump_far
global in8, in16, in32
global out8, out16, out32
global sti, cli, std, cld
global hlt, nop, pass, breakpoint
global swap_seg, swap_reg, swap_cs
global lidt, lgdt, int80

jump:
    push rdi
    ret
jump_far:
    push rdi
    push rsi
    retf
call:
    push .ret
    push rdi
    ret
    .ret    ret
call_far:
    push .ret
    push rdi
    push rsi
    retf
    .ret    ret
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
lidt:
    xchg bx, bx
    lidt [rdi]
    xchg bx, bx
    ret
lgdt:
    xchg bx, bx
    push rsi
    lea rsi, [rel .ret]
    push rsi
    lgdt [rdi]
    retf
    .ret:
        mov ds, dx
        mov es, dx
        mov fs, dx
        mov gs, dx
        mov ss, dx
    xchg bx, bx
    ret
swap_seg:
    pushq
    mov ax, ds
    mov bx, es
    mov cx, fs
    mov dx, gs
    call swap_reg
    mov ds, ax
    mov es, bx
    mov fs, cx
    mov gs, dx
    popq
    ret
swap_reg:
    .ab test di, di
    jnz .ac
    xchg rax, rbx
    ret
    .ac dec di
    jnz .ad
    xchg rax, rcx
    ret
    .ad dec di
    jnz .bc
    xchg rax, rdx
    ret
    .bc dec di
    jnz .bd
    xchg rbx, rcx
    ret
    .bd dec di
    jnz .cd
    xchg rbx, rdx
    ret
    .cd dec di
    jnz .err
    xchg rcx, rdx
    .err ret
int80:
    int 0x80
    ret
