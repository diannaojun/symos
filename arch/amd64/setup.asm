%include "config.inc"

org ADDR_SEG_SET_PROG << 4
bits 16

jmp _start

; ------ 00500
; STACK
; ------ 08000




align 16
_start:
mode16:
    cli

    in al, 0x92
    or al, 0x02
    out 0x92, al

    lgdt [0x7d50]
    lidt [0x7d56]

    mov eax, cr0
    or eax, 0x00000001
    mov cr0, eax

    jmp dword 0x0008:mode32

bits 32
align 32
mode32:
    mov ax, 0x0010
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ax, 0x0018
    mov ss, ax
    mov esp, 0x08000 - 0x00500
    mov ebp, esp
    xor edi, edi
    xor esi, esi
test_print:
    hlt
    jmp $

times 4096 -($ - $$) db 0