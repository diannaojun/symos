; Symbol DT
; SymOS
; DiannaoJun
; 2024-03-31
org 0x7c00
bits 16
; %define dbg

jmp _start

disk_id:
    dd 0x00
packet:
    db 0x10, 0x00
    .blocks     dw 42
    .offset     dw 0
    .segment    dw 0
    .address    dq 0
    .bufferl    dq 0

_start:
    mov ax, cs
    mov ds, ax
    mov es, ax
    xor ax, ax
    mov ss, ax
    mov sp, 0x7c00
    mov [disk_id], dl
entry:
    ; 清屏
    call lost_screen
    call clean_screen
    ; 输出 IPL 信息
    mov si, words.log_head
    call puts
    mov si, words.symbol_os
    call puts
    mov si, words.endl
    call puts
    ; 读磁盘
    mov word [packet.offset], 0x7c00
    mov dl, [disk_id]
    mov si, packet
    call read_lba
    mov [disk_id], dl
    jc error
    ; 输出成功信息
    mov si, words.log_head
    call puts
    mov si, words.initialization
    call puts
    mov si, words.successfully
    call puts
    mov si, words.endl
    call puts
    call lost_screen
    call 0x7e00
hang:
    jmp $

error:; 输出失败信息
    mov si, words.err_head
    call puts
    mov si, words.initialization
    call puts
    mov si, words.failed
    call puts
    mov si, words.endl
puts:
    mov al, [si]
    inc si
    cmp al, 0x00
    jne .PUTLOOP
    ret
    .PUTLOOP:
        mov ah, 0x0e
        mov bx, 0x0f
        int 0x10
    jmp puts
read_lba:
    mov ah, 0x42
    int 0x13
    ret
clean_screen:
    mov ah, 6
    xor cx, cx
    mov al, cl
    mov dx, 0xffff
    mov bh, 0x07
    int 0x10
    ret
lost_screen:
    mov ah, 2
    xor bx, bx
    xor dx, dx
    int 0x10
    ret

words:
    .log_head:
        db "[loader16::log] ", 0x00
    .err_head:
        db "[loader16::error(1)] ", 0x00
    .endl:
        db 0x0a, 0x0d, 0x00
    .symbol_os:
        db "symbol-os", 0x00
    .initialization:
        db "initialization ", 0x00
    .successfully:
        db "successfully ", 0x00
    .failed:
        db "failed(by I/O Error) ", 0x00


%ifdef dbg
HEX_MESSAGE:
    db "0x##", 0x00
HEX_TABLE:
    db "0123456789ABCDEF"

PUT_HEX:
    mov bl, al
    shr bl, 4
    and ax, 0x000f
    and bx, 0x000f
    add ax, HEX_TABLE
    add bx, HEX_TABLE
    mov si, ax
    mov al, [si]
    mov si, bx
    mov ah, [si]
    mov [HEX_MESSAGE+2], ax
    mov si, HEX_MESSAGE
    call PUTS
    ret
%endif


times 510-($-$$) db 0x00
db 0x55, 0xaa

