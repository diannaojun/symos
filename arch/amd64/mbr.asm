%include "config.inc"
org ADDR_SEG_MBR_PROG << 4
bits 16
; ------ 00500
; STACK
; ------ 07c00
; MBR
; ------ 07e00
; BUFFER
; ------ 08000

header  jmp _start

ident:
    .flag       db "symbol-os", 0
    .version    dd 0x00030001
packet:
    .size       dw 0x0010
    .count      dw 0x0001
    .offset     dw 0x7e00
    .segment    dw 0x0000
    .address    dq 0x0000000000000001
port:
    .errs_func  dw 0, errors
    .puts_func  dw 0, puts
    .putc_func  dw 0, putc
    .putx_func  dw 0, putx
message:
    .texta      db "[MBR::err(", 0
    .textb      db ")]", 0
    .textc      db "Loading kernel...", 0x0a, 0x0d, 0
_start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ax, ADDR_SEG_MBR_PROG << 4
    mov sp, ax
    mov bp, ax
    mov [header], dl
clear:
    mov ax, 0x0400
    int 0x10
    mov ah, 0x02
    xor bx, bx
    xor dx, dx
    int 0x10
    mov ax, 0x0600
    mov dx, 0xffff
    mov bh, 0x0f
    xor cx, cx
    int 0x10
    mov si, message.textc
    call puts
check_int13hx:
    mov ah, 0x41
    mov dl, [header]
    mov bx, 0x55aa
    int 0x13
    mov ax, 0x0001
    jc errors
    cmp bx, 0xaa55
    jne errors
read_sdmpart:
    mov ah, 0x42
    mov dl, [header]
    mov si, packet
    int 0x13
    mov ax, 0x0002
    jc errors
    mov cx, 0x04
    mov si, 0x7e10
    mov di, packet.address
    .loop:
        mov ax, [si]
        mov [di], ax
        add si, 0x02
        add di, 0x02
        loop .loop
    mov ax, [0x7e0a]
    mov bx, [0x7e0c]
    mov cx, [0x7e0e]
    and cx, 0x000f
    shl cx, 12
    mov [packet.count], ax
    mov [packet.offset], bx
    mov [packet.segment], cx
read_bootsect:
    mov ah, 0x42
    mov dl, [header]
    mov si, packet
    int 0x13
    mov ax, 0x0003
    jc errors
    xor ax, ax
    mov al, [header]
    mov [0x7e00], ax
    push word [packet.segment]
    push word [packet.offset] 
    retf
errors:
    push ax
    mov si, message.texta
    call puts
    pop ax
    call putx
    mov si, message.textb
    call puts
dead:
    jmp $
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
        cmp al, 0x0a
        jge .big10
        add al, '0'
        jmp .show
        .big10  add al, 'a'-10
        .show:
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

times (510-64)-($-$$) db 0x00

mbr_null

times (512-2)-($-$$) db 0x00
db 0x55, 0xaa
