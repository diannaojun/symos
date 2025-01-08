%include "config.inc"
org ADDR_SEG_SET_PROG << 4
bits 16

; ------ 00500
; STACK
; ------ 08000

jmp _start

_start:
    xor ax, ax
    mov ds, ax
    cli
setA20e:
    call wait8064
    mov al, 0xd1
    out 0x64, al
    call wait8064
    mov al, 0xdf
    out 0x60, al
    call wait8064
    in al, 0x92
    or al, 0x02
    out 0x92, al
setXDT:
    lgdt [ds:0x7c28]
    lidt [ds:0x7c2e]
setCR0PE:
    xchg bx, bx
    mov eax, cr0
    or eax, 0x00000001
    mov cr0, eax
    jmp dword 0x0008:mode32
wait8064:
    in al, 0x64
    test al, 0x02
    jnz wait8064
    ret

bits 32
align 32
mode32:
    mov ax, 0x0010
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x7c00
    mov ebp, esp
    xor edi, edi
    xor esi, esi
test_print:
    hlt
    jmp $

times 4096 -($ - $$) db 0
