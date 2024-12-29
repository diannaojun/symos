org 0x7c00
bits 16

DATA_LEN_OF_SETUP   equ 3
ADDR_SEG_MBR_PROG   equ 0x07c0
ADDR_SEG_SET_PROG   equ 0x9f00
ADDR_SEG_INI_PROG   equ 0x9000
ADDR_SEG_SYS_PROG   equ 0x1000

jmp _start

ident:
    db "SYMBOL OS", 0
    db 3, 0
    .magic  db 0x55, 0xaa

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
    ; call 0x7e00
    jmp dead
puts:
    mov al, [si]
    inc si
    test al, al
    jnz .puts_loop
    ret
    .puts_loop:
        mov ah, 14
        mov bx, 15
        int 16
    jmp puts
putx:
    mov bl, al
    shr bl, 4
    and ax, 0x000f
    and bx, 0x000f
    add ax, messages.hex_head
    add bx, messages.hex_head
    mov si, ax
    mov al, [si]
    mov si, bx
    mov ah, [si]
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
packet:
    db 0x10, 0x00
    .blocks     dw 0
    .offset     dw 0
    .segment    dw 0
    .address    dq 0
    .bufferl    dq 0
messages:
    .log_head:
        db "[l16::log] ", 0
    .err_head:
        db "[l16::err(", 0
    .err_foot:
        db ")] ", 0
    .endl:
        db 10, 13, 0
    .io_error:
        db "IO ERROR", 0
    .hex_head:
        db "##", 0
    .hex_table:
        db "0123456789abcdef"

times 16-(($-$$)&15) db 0xff
times 510-($-$$) db 0x00
db 0x55, 0xaa
times 4096 db 0x00