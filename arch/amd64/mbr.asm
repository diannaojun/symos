org 0x7c00
bits 16

%include "config.inc"

jmp _start

ident:
    db "symbol-os", 0
    db 3, 0
    .magic  db 0x55, 0xaa

align 16

_start:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    xor sp, sp
    mov [ident.magic], dl
    call lost_screen
    call clean_screen
    mov si, messages.log_head
    call puts
    mov si, ident
    call puts
    mov si, messages.endl
    call puts
    mov word [packet.offset], 0x0500
    mov word [packet.segment], 0x0000
    mov word [packet.blocks], DATA_LEN_OF_SETUP
    mov dl, [ident.magic]
    mov si, packet
    call read_lba
    jc error
    call ADDR_SEG_SET_PROG:0
    jmp dead

align 16

puts:               ; void puts (si)
    .puts_loop:
        mov al, [si]
        inc si
        test al, al
        jz .puts_ret
        mov ah, 14
        mov bx, 15
        int 16
        jmp .puts_loop
    .puts_ret:
        ret
putx:               ; void puts (al)
    mov ah, al
    shr al, 4
    and ah, 15
    movzx si, al
    mov al, [si + messages.hex_table]
    movzx si, ah
    mov ah, [si + messages.hex_table]
    mov [messages.hex_head], ax
    mov si, messages.hex_head
    call puts
    ret
read_lba:
    mov ah, 0x42
    int 0x13
    ret
clean_screen:
    mov ah, 6
    xor cx, cx
    mov al, cl
    mov dx, 0xffff
    mov bh, 7
    int 16
    ret
lost_screen:
    mov ah, 2
    xor bx, bx
    xor dx, dx
    int 16
    ret
error:
    mov si, messages.err_head
    call puts
    mov al, 1
    call putx
    mov si, messages.err_foot
    call puts
    mov si, messages.io_error
    call puts
    mov si, messages.endl
    call puts
dead:
    jmp $

align 16

packet:
    db 0x10, 0x00
    .blocks     dw 0
    .offset     dw 0
    .segment    dw 0
    .address    dq 0
    .bufferl    dq 0

align 16

messages:
    .log_head:
        db "[L16::log] ", 0
    .err_head:
        db "[L16::err(", 0
    .err_foot:
        db ")] ", 0
    .endl:
        db 10, 13, 0
    .io_error:
        db "I/O Error", 0
    .hex_head:
        db "##", 0
    align 16
    .hex_table:
        db "0123456789abcdef"

times 510-($-$$) db 0x00
db 0x55, 0xaa
