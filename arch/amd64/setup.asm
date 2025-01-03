%include "config.inc"

org ADDR_SEG_SET_PROG << 4
bits 16

jmp _start

; ------ 00500
; STACK
; ------ 08000


align 16
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

align 16
_start:
    mov ax, ADDR_SEG_SET_PROG
    mov ds, ax
    mov es, ax
    mov ax, ADDR_SEG_MBR_PROG
    mov ss, ax
    xor ax, ax
    mov sp, ax
    mov bp, ax
    xor si, si
    xor di, di
mode16:
    mov ax, 0x0124
    int 0x15
    mov ax, 0xec00
    mov bl, 0x03
    int 0x15

    lidt [idt_info]
    lgdt [gdt_info]

    call wait8042
    mov al, 0xd1
    out 0x64, al
    call wait8042
    mov al, 0xdf
    out 0x60, al
    call wait8042
    mov al, 0x11
    out 0x20, al
    jmp $ + 2
    jmp $ + 2
    out 0xa0, al
    jmp $ + 2
    jmp $ + 2
    mov al, 0x20
    out 0x21, al
    jmp $ + 2
    jmp $ + 2
    mov al, 0x28
    out 0xa1, al
    jmp $ + 2
    jmp $ + 2
    mov al, 0x04
    out 0x21, al
    jmp $ + 2
    jmp $ + 2
    mov al, 0x02
    out 0xa1, al
    jmp $ + 2
    jmp $ + 2
    mov al, 0x01
    out 0x21, al
    jmp $ + 2
    jmp $ + 2
    out 0xa1, al
    jmp $ + 2
    jmp $ + 2
    mov al, 0xff
    out 0x21, al
    jmp $ + 2
    jmp $ + 2
    out 0xa1, al

    in al, 0x92
    or al, 0x02
    out 0x92, al
    mov eax, cr0
    or eax, 0x00000001
    mov cr0, eax
    jmp dword 0x0008:mode32
wait8042:
    jmp $ + 2
    jmp $ + 2
    mov dx, 0x64
    in al, dx
    test al, 0x02
    jnz wait8042
    ret

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