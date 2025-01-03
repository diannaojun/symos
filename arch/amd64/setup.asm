%include "config.inc"

org ADDR_SEG_SET_PROG << 4
bits 16

jmp _start

; ------ 00500
; STACK
; ------ 08000


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
    cli
    call wait8042i
    mov al, 0xad
    out 0x64, al
    call wait8042i
    mov al, 0xd0
    out 0x64, al
    call wait8042o
    in al, 0x60
    push ax
    call wait8042i
    mov al, 0xd1
    out 0x64, al
    call wait8042i
    pop ax
    or al, 0x02
    out 0x64, al

    lidt [idt_info]
    lgdt [gdt_info]

    in al, 0x92
    or al, 0x02
    out 0x92, al
    mov eax, cr0
    or eax, 0x00000001
    mov cr0, eax
    jmp dword 0x0008:mode32
wait8042i:
    mov dx, 0x64
    in al, dx
    test al, 0x02
    jnz wait8042i
    ret
wait8042o:
    mov dx, 0x64
    in al, dx
    test al, 0x01
    jnz wait8042o
    ret

bits 32
align 16
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
    mov esi, 0xb8000
    mov word [esi + 0], ('3' << 8) | 0x0c
    mov word [esi + 2], ('2' << 8) | 0x0c
    mov word [esi + 4], ('M' << 8) | 0x0c
    mov word [esi + 6], ('O' << 8) | 0x0c
    mov word [esi + 8], ('D' << 8) | 0x0c
    mov word [esi + 10], ('E' << 8) | 0x0c
    jmp $

times 4096 -($ - $$) db 0