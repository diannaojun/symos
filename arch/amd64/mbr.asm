%include "config.inc"

org ADDR_SEG_MBR_PROG << 4
bits 16

%include "config.inc"

jmp _start

ident:
    .flag       db "symbol-os", 0
    .version    dw 0x0300
    .magic      db 0x55, 0xaa

align 16
_start:
    mov ax, cs
    mov ss, ax
    mov es, ax
    mov ds, ax
    xor sp, sp
    xor bp, sp
    xor si, si
    xor di, di
    mov [ident.magic], dl
; log_out:
;     call lost_screen
;     call clean_screen
; read_mem:
;     mov ah, 0x88
;     int 0x15
;     mov [info.memory], ax
; read_video:
;     mov ah, 0x0f
;     int 0x10
;     mov [info.v_page], bh
;     mov [info.v_mode], al
;     mov [info.v_width], ah
;     mov ah, 0x12
;     mov bl, 0x10
;     int 0x10
;     mov [info.v_data0], ax
;     mov [info.v_data1], bx
;     mov [info.v_data2], cx
read_setup:
    mov word [packet.offset], 0
    mov word [packet.segment], ADDR_SEG_SET_PROG
    mov word [packet.blocks], DATA_LEN_OF_SETUP
    mov byte [packet.address], 0x40
    mov dl, [ident.magic]
    mov si, packet
    call read_lba
    ; mov si, messages.log_head
    ; call puts
    ; mov si, ident
    ; call puts
    ; mov al, ' '
    ; call putc
    ; mov ax, [ident.version]
    ; call putx
    ; mov si, messages.endline
    ; call puts
    jmp ADDR_SEG_SET_PROG : 0
; puts:               ; void puts (si)
;     .puts_loop:
;         mov al, [si]
;         inc si
;         test al, al
;         jz .puts_ret
;         call putc
;         jmp .puts_loop
;     .puts_ret:
;         ret
; putx:               ; void putx (ax)
;     mov cx, 4
;     .putx_loop:
;         push ax
;         shr ax, 12
;         mov si, ax
;         cmp al, 0x0a
;         jge .big10
;             add al, '0'
;             jmp .show
;         .big10:
;             add al, 'a'-10
;         .show:
;         push cx
;         call putc
;         pop cx
;         pop ax
;         shl ax, 4
;     loop .putx_loop
;     ret
; putc:               ; void putc (al)
;     mov ah, 0x0e
;     mov bx, 0x0f
;     int 0x10
;     ret
read_lba:
    mov ah, 0x42
    int 0x13
    jc error
    ret
; clean_screen:
;     mov ah, 0x06
;     xor cx, cx
;     mov al, cl
;     mov dx, 0xffff
;     mov bh, 0x07
;     int 0x10
;     ret
; lost_screen:
;     mov ah, 0x02
;     xor bx, bx
;     xor dx, dx
;     int 0x10
;     ret
error:
    ; mov si, messages.err_head
    ; call puts
    ; mov ax, 0x0001
    ; call putx
    ; mov si, messages.err_foot
    ; call puts
    ; mov si, messages.io_error
    ; call puts
    ; mov si, messages.endline
    ; call puts
dead:
    jmp $
packet:
    dw 0x10
    .blocks     dw 0
    .offset     dw 0
    .segment    dw 0
    .address    dq 0
    .bufferl    dq 0
messages:
    .endline    db 10, 13, 0
    .log_head   db "[L16::log] ", 0
    .err_head   db "[L16::err(", 0
    .err_foot   db ")] ", 0
    .io_error   db "I/O Error", 0

times 0x150-($-$$) db 0x00

times (510-64)-($-$$) db 0x00

mbr_null

times (512-2)-($-$$) db 0x00
db 0x55, 0xaa

