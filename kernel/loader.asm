; Symbol DT
; SymOS
; DiannaoJun
; 2024-04-04

ORG 0x7e00
BITS 16

; %define dbg
%include "./lib/loader/xdt.inc"

DRIVER_NUMBER   EQU 0x7c20

JMP ENTRY

GDT_BGN:
    SEG_NULL                                ; #0 空段
    SEG STA_X|STA_R,0x0,0xffffffff,GDT32    ; #1 代码段
    SEG STA_W,0x0,0xffffffff,GDT32          ; #2 数据段
GDT_END:
IDT_BGN:
    dq 0
IDT_END:
GDT_INFO:
    dw GDT_END-GDT_BGN-1
    dd GDT_BGN
IDT_INFO:
    dw IDT_END-IDT_BGN-1
    dd IDT_BGN

ENTRY:
    mov ax,cs
    mov ds,ax
    mov es,ax
    mov ss,ax
    mov sp,0x00
    mov ax,0B800h
    mov gs,ax
    call START
    ret
START:
    MODE16:
        ; 打开A20
        mov al,0x01
        mov ah,0x24
        int 0x15
        mov ax,0xec00
        mov bl,0x03
        int 0x15
        cli                 ; 关闭中断
        call WAIT8042IBE
        mov al,0xad
        out 0x64,al         ; 禁止键盘操作
        call WAIT8042IBE
        mov al,0xd0
        out 0x64,al
        call WAIT8042OBE
        in al,0x60
        push ax
        call WAIT8042IBE
        mov al,0xd1
        out 0x64,al
        call WAIT8042IBE
        pop ax
        or al,0x02
        out 0x60,al
        call WAIT8042IBE
        mov al,0xae
        out 0x64,al         ; 允许键盘操作
        in al,0x92
        or al,0x02
        out 0x92,al
        ; GDT/IDT设置
        lgdt [GDT_INFO]
        ; lidt [IDT_INFO]
        ; 打开CR0
        mov eax,cr0
        bts eax,0
        mov cr0,eax
        jmp dword 0x0008:MODE32
        WAIT8042IBE:
            mov dx,64h
            in al,dx
            test al,02h
            jnz WAIT8042IBE
            ret
        WAIT8042OBE:
            mov dx,64h
            in al,dx
            test al,01
            jz WAIT8042OBE
            ret

BITS 32
MODE32: ; 进入32位保护模式
    mov ax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax
    mov ebp,0x7c00
    mov esp,ebp
    jmp dword 0x0008:0x8000
