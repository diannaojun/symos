%include "config.inc"
org ADDR_SEG_SET_PROG << 4
bits 16

; ------ 00500
; STACK
; ------ 07c00
; BOOT INFORMATINS
; ------ 08000
; EMPTY
; ------ 9f000
; SETUP
; ------ a0000

jmp _start

gdt:
    .null   gdt_null
    .code   gdt_segment 0x00000000, 0xffffffff, sta_prog | sta_prog_x | sta_prog_xwr | sta_level0 | sta_existent, stt_32def | stt_limitalign4kb
    .data   gdt_segment 0x00000000, 0xffffffff, sta_prog | sta_prog_d | sta_prog_xwr | sta_level0 | sta_existent, stt_32def | stt_limitalign4kb
    .end:
gdt64:
    .null   gdt_null
    .code   gdt_segment 0, 0, sta_prog | sta_prog_x | sta_prog_xwr | sta_level0 | sta_existent, stt_64def
    .end:
gdt_info:
    dw gdt.end - gdt
    dd gdt
gdt64_info:
    dw gdt64.end - gdt64
    dd gdt64
idt_info:
    times 3 dw 0
message:
    .texta  db "[Setup32::err(", 0
    .texte  db "[Setup16::err(", 0
    .textb  db ")] ", 0

_start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov [0x7e02], ax
set_description_table:          ; 設定描述符表
    mov ax, ADDR_SEG_SET_PROG
    mov ds, ax
    lgdt [ds:gdt_info - $$]
    lidt [ds:idt_info - $$]
set_a20:                        ; 設定 A20
    call test_A20
; 方法 1: BIOS 中斷
    ; 支持 A20 ?
    mov ax, 0x2403
    int 0x15
    jb .A20_ns
    test ah, ah
    jnz .A20_ns
    ; 嘗試開啓 A20
    mov ax, 0x2402
    int 0x15
    jb .A20_failed
    test ah, ah
    jnz .A20_failed
    ; 檢驗是否開啓
    cmp al, 1
    jz .A20_activated
    mov ax, 0x2401
    int 0x15
    jb .A20_failed
    test ah, ah
    jnz .A20_failed
    .A20_activated:
        call test_A20
    .A20_failed:
; 方法 2: 鍵盤控制器 8042
    cli
    call wait_8042_2
    mov al, 0xad
    out 0x64, al
    call wait_8042_2
    mov al, 0xd0
    out 0x64, al
    call wait_8042_1
    in al, 0x60
    push ax
    call wait_8042_2
    mov al, 0xd1
    out 0x64, al
    call wait_8042_2
    pop ax
    or al, 2
    out 0x60, al
    call wait_8042_2
    mov al, 0xae
    out 0x64, al
    call wait_8042_2
    sti
    call test_A20
; 方法 3: 0xee 端口
    in al, 0xee
    call test_A20
; 方法 4: 快速 A20 門
    in al, 0x92
    test al, 2
    jnz .skip92
    or al, 2
    and al, 0xfe
    out 0x92, al
    .skip92:
        call test_A20
    .A20_ns:
        mov ax, 0x0007
        push word [0x7c24]
        push word [0x7c26]
        retf
wait_8042_1:
    call step2
    in al, 0x64
    test al, 1
    jnz wait_8042_1
    ret
wait_8042_2:
    call step2
    in al, 0x64
    test al, 2
    jz wait_8042_2
    ret
step2:
    nop
    jmp $+2
    nop
    jmp $+2
    nop
    ret
test_A20:
    pusha
    xor ax, ax
    xor si, si
    mov ds, ax
    mov ax, 0xffff
    mov di, 0x0010
    mov es, ax
    mov word [si], 0x0000
    mov word [di], 0x1145
    mov ax, [si]
    test ax, ax
    popa
    jz set_8259
    ret
set_8259:
    pop ax
    mov al, 0x11
    out 0x20, al
    call step2
    out 0xa0, al
    call step2
    mov al, 0x20
    out 0x21, al
    call step2
    mov al, 0x28
    out 0xa1, al
    call step2
    mov al, 0x04
    out 0x21, al
    call step2
    mov al, 0x02
    out 0xa1, al
    call step2
    mov al, 0x01
    out 0x21, al
    call step2
    out 0xa1, al
    call step2
    mov al, 0xff
    out 0x21, al
    call step2
    out 0xa1, al
    call step2
set_cr0_PE:
    mov eax, cr0
    or eax, 0x00000001
    mov cr0, eax
    jmp dword 0x0008:_start32

bits 32
align 32
_start32:
    mov ax, 0x0010
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x7c00
    mov ebp, esp
    xor edi, edi
    xor esi, esi
check_cpuid:
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    push ecx
    popfd
    test eax, ecx
    mov ax, 0x0004
    jz errors
check_long_mode:
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    mov ax, 0x0005
    jb errors
    cmp eax, 0x80000001
    cpuid
    test edx, 1 << 29
    xchg bx, bx
    mov ax, 0x0006
    jz errors
    mov esi, message.texte
    call puts
    xchg bx, bx
    jmp $
set_page_gdt:
    lgdt [gdt64_info]
    jmp 0x0008:_try64
_try64:
    mov eax, 1010_0000b
    mov cr4, eax
    mov eax, 0x00000000 ; addr of page4
    mov cr3, eax
    mov ecx, 0xc0000080
    rdmsr
    or eax, 0x00000100
    wrmsr
    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax
    jmp _start64
_start64:
    jmp $
errors:
    push ax
    mov esi, message.texta
    call puts
    pop ax
    call putx32
    mov esi, message.textb
    call puts
    jmp $
puts:
    .puts_loop:
        mov al, [esi]
        inc esi
        test al, al
        jz .puts_ret
        call putc32
        jmp .puts_loop
    .puts_ret:
        ret
putc32:               ; void putc (al)
    movzx ecx, word [0x7e02]
    add ecx, 0xb8000
    mov edi, ecx
    mov ah, 0x0f
    cmp al, 10
    mov [edi], ax
    sub ecx, 0xb8000 - 2
    mov [0x7e02], cx
    ret
putx32:               ; void putx (ax)
    mov cx, 4
    .putx_loop:
        push ax
        shr ax, 12
        mov si, ax
        cmp al, 0x0a
        jge .bigger10
        mov ah, '0'
        jmp .less10
        .bigger10:
            mov ah, 'a'-10
        .less10:
            add al, ah
        push cx
        call putc32
        pop cx
        pop ax
        shl ax, 4
    loop .putx_loop
    ret

times 4096 -($ - $$) db 0
