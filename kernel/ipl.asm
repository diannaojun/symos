; Symbol DT
; SymOS
; DiannaoJun
; 2024-03-31
ORG 0x7c00
BITS 16
; %define dbg
jmp START

DAT_OEM     DB "SYMOS1.0"
DAT_DL      DB "SYMOS1.0"
DAT_UUID    DD 0xffffffff
DAT_RS      DW 16
DAT_SNO     DQ 64
DAT_SYS     DB 0x01
ROT_STR		DQ 529

TIMES 64-($-$$) DB 0x00


SWAPPING_BUFFER:
    DRIVER_NUMBER   DB  0x00
    TIMES 3 DB 0

START:
    mov ax,cs
    mov ds,ax
    mov es,ax
    xor ax,ax
    mov ss,ax
    mov sp,0x7c00
    mov [DRIVER_NUMBER],dl
    call ENTRY
    jmp FINAL
IPL_MESSAGE:
    DB "SZS deno Symbol Devep Gtem Zce.",0x0a,0x0d,0x00
ERR_MESSAGE:
    DB "ZukXitiatdo nas! Ylom-L01",0x0a,0x0d,0x00
SCS_MESSAGE:
    DB "ZukXitiatdo hos!",0x0a,0x0d,0x00
PACKET:
    DB 0x10,0x00
    PACKET_BLKCNT   DW 42
    PACKET_BFROFS   DW 0
    PACKET_BFRSEG   DW 0
    PACKET_BLKNUM   DQ 0
    DD 0

ENTRY:
    ; 清屏
    call START_SCN_INFO
    ; 输出IPL信息
    mov si,IPL_MESSAGE
    call PUTS
    ; 读磁盘
    mov word [PACKET_BFROFS],0x7c00
    mov dl,[DRIVER_NUMBER]
    mov si,PACKET
    call READ_LBA
    mov [DRIVER_NUMBER],dl
    shr si,64
    jc ERR
    ; 输出成功信息
    mov si,SCS_MESSAGE
    call PUTS
    call SAVE_SCN_INFO
    call 0x7e00
    jmp FINAL
ERR:; 输出失败信息
    mov si,ERR_MESSAGE
    call PUTS
    ret
PUTS:
    mov al,[si]
    inc si
    cmp al,0x00
    jne .PUTLOOP
    ret
    .PUTLOOP:
        mov ah,0x0e
        mov bx,0x0f
        int 0x10
    jmp PUTS
READ_LBA:
    mov ah,0x42
    int 0x13
    ret
START_SCN_INFO:
    xor bx,bx
    xor dx,dx
    mov ah,2
    int 0x10
    mov ah,6
    xor cx,cx
    mov al,cl
    mov dx,0xffff
    mov bh,0x07
    int 0x10
    ret
SAVE_SCN_INFO:
    mov ah,2
    xor bx,bx
    xor dx,dx
    int 0x10
    ret
FINAL:
    jmp $

%ifdef dbg
HEX_MESSAGE:
    DB "0x##",0x00
HEX_TABLE:
    db "0123456789ABCDEF"
PUT_HEX:
    mov bl,al
    shr bl,4
    and ax,0x000f
    and bx,0x000f
    add ax,HEX_TABLE
    add bx,HEX_TABLE
    mov si,ax
    mov al,[si]
    mov si,bx
    mov ah,[si]
    mov [HEX_MESSAGE+2],ax
    mov si,HEX_MESSAGE
    call PUTS
    ret
%endif


TIMES 510-($-$$) DB 0x00
DB 0x55, 0xaa

