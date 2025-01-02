%include "config.inc"

org ADDR_SEG_MBR_PROG<<4
bits 16

%include "config.inc"

jmp _start

ident:
    .flag       db "symbol-os", 0
    .version    dw 0x0300
    .magic      db 0x55, 0xaa

align 16

align 16
_start:
    mov ax, ADDR_SEG_MBR_PROG << 4
    mov sp, ax
    mov bp, ax
    xor ax, ax
    mov ss, ax
    mov es, ax
    mov ds, ax
    xor si, si
    xor di, di
    mov [info.drive], dl
log_out:
    call lost_screen
    call clean_screen
    mov si, messages.log_head
    call puts
    mov si, ident
    call puts
    mov al, ' '
    call putc
    mov ax, [ident.version]
    call putx
    mov si, messages.endline
    call puts
read_mem:
    mov ah, 0x88
    int 0x15
    mov [info.memory], ax
read_video:
    mov ah, 0x0f
    int 0x10
    mov [info.v_page], bh
    mov [info.v_mode], al
    mov [info.v_width], ah
    mov ah, 0x12
    mov bl, 0x10
    int 0x10
    mov [info.v_data0], ax
    mov [info.v_data1], bx
    mov [info.v_data2], cx
read_setup:
    mov word [packet.offset], 0x0500
    mov word [packet.segment], 0x0000
    mov word [packet.blocks], DATA_LEN_OF_SETUP
    mov dl, [info.drive]
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
        call putc
        jmp .puts_loop
    .puts_ret:
        ret
putx:               ; void putx (ax)
    mov cx, 4
    .putx_loop:
        push ax
        shr ax, 12
        mov si, ax
        mov al, [si + messages.hex_table]
        push cx
        call putc
        pop cx
        pop ax
        shl ax, 4
    loop .putx_loop
    ret

putc:               ; void putc (al)
    mov ah, 0x0e
    mov bx, 0x0f
    int 0x10
    ret
read_lba:
    pusha
    pushf
    mov ah, 0x42
    int 0x13
    xor ax, ax
    jnc .ret
    mov ax, -1
    .ret:
        popf
        popa
        ret
clean_screen:
    mov ah, 0x06
    xor cx, cx
    mov al, cl
    mov dx, 0xffff
    mov bh, 0x07
    int 0x10
    ret
lost_screen:
    mov ah, 0x02
    xor bx, bx
    xor dx, dx
    int 0x10
    ret
error:
    mov si, messages.err_head
    call puts
    mov ax, 0x0001
    call putx
    mov si, messages.err_foot
    call puts
    mov si, messages.io_error
    call puts
    mov si, messages.endline
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
    .hex_table  db "0123456789abcdef"
    .endline    db 10, 13, 0
    .log_head   db "[L16::log] ", 0
    .err_head   db "[L16::err(", 0
    .err_foot   db ")] ", 0
    .io_error   db "I/O Error", 0

times 496-($-$$) db 0x00
info:
    .drive      db 0
    .memory     dw 0
    .v_page     db 0
    .v_mode     db 0
    .v_width    db 0
    .v_data0    dw 0
    .v_data1    dw 0
    .v_data2    dw 0

times 510-($-$$) db 0x00
db 0x55, 0xaa

