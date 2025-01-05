%include "config.inc"
org ADDR_SEG_SET_PROG << 4
bits 16

; ------ 00500
; STACK
; ------ 08000

jmp _start

gdt:
    .null   gdt_null
    .code   gdt_segment 0x00000000, 0xffffffff, sta_prog_x | sta_prog_xr, stt_32def | stt_limitalign4kb
    .data   gdt_segment 0x00000000, 0xffffffff, sta_prog_d | sta_prog_wr, stt_32def | stt_limitalign4kb
    .stack  gdt_segment 0x00008000, 0x08000 - 0x00500, sta_prog_d | sta_prog_wr | sta_prog_gd, stt_32def
    .end:
gdt_info:
    dw gdt.end - gdt
    dd gdt
idt_info:
    times 3 dw 0

_start:
mode16:
    mov ax, cs
    mov ds, ax
    lgdt [ds:gdt_info]
    lidt [ds:gdt_info]
    in al, 0x92
    or al, 0x02
    out 0x92, al
    cli
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