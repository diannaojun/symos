%include "config.inc"
org ADDR_SEG_SET_PROG << 4
bits 16

; ------ 00000
; IDT
; ------ 01000
; GDT
; ------ 02000
; PML5
; ------ 03000
; PML4
; ------ 04000
; PDPT
; ------ 05000
; PD
; ------ 06000
; STACK
; ------ 07e00
; BOOT INFORMATINS
;   0   2   BOOT DEV
;   2   2   SCREAN POS
;   4   1   VGA MODE
;   5   1   VGA ROWS
;   6   1   VGA MEM CNT
;   7   1   VGA STAT
;   8   2   VGA ATTR
;   A   2   MEM
;  e0   6   IDT HDR
;  f0   6   GDT HDR
; ------ 08000
; EMPTY
; ------ 9f000
; SETUP
; ------ a0000

jmp _start

gdt:
    .null   gdt_null
    .code   gdt_segment 0x00000000, 0xffffffff,\
        sta_prog | sta_prog_x | sta_prog_xwr | sta_level0 | sta_present,\
        stt_32def | stt_limitalign4kb
    ; 32位程序代码段, 内核级, 平坦模式
    .data   gdt_segment 0x00000000, 0xffffffff,\
        sta_prog | sta_prog_d | sta_prog_xwr | sta_level0 | sta_present,\
        stt_32def | stt_limitalign4kb
    ; 32位程序数据段, 内核级, 平坦模式
    .code64 gdt_segment 0, 0,\
        sta_prog | sta_prog_x | sta_prog_xwr | sta_level0 | sta_present,\
        stt_64def
    ; 64位程序代码段
    .data64 gdt_segment 0, 0,\
        sta_prog | sta_prog_d | sta_prog_xwr | sta_level0 | sta_present, 0
    ; 64位程序数据段
    .end:
pagings:
    .pml5   paging 0x3000, pag_present | pag_writable, 0            ; 5级分页
    .pml4   paging 0x4000, pag_present | pag_writable, 0            ; 4级分页
    .pdpt   paging 0x5000, pag_present | pag_writable, 0            ; 3级分页
    .pd:    ; 2级大分页 2MB 映射低 16mb
        paging 0x000000, pag_present | pag_writable | pag_huge, 0
        paging 0x200000, pag_present | pag_writable | pag_huge, 0
        paging 0x400000, pag_present | pag_writable | pag_huge, 0
        paging 0x600000, pag_present | pag_writable | pag_huge, 0
        paging 0x800000, pag_present | pag_writable | pag_huge, 0
        paging 0xa00000, pag_present | pag_writable | pag_huge, 0
        paging 0xc00000, pag_present | pag_writable | pag_huge, 0
        paging 0xe00000, pag_present | pag_writable | pag_huge, 0
gdt_info:   ; 32位全局段描述符表标识
    dw gdt.end - gdt
    dd gdt
idt_info:   ; 32位空中断门描述符表标识
    times 3 dw 0
message:
    .texta  db "[Setup32::err(", 0
    .texte  db "[Setup16::err(", 0
    .textb  db ")] ", 0
    .textc  db "Loading kernel32...", 10, 13, 0
    .textrega   db " EAX=", 0
    .textregc   db " ECX=", 0
    .textregd   db " EDX=", 0
    .textregb   db " EBX=", 0

_start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
bootinfo:
    mov ah, 0x0f
    int 0x10
    mov [0x7e04], ax
    mov ah, 0x12
    mov bl, 0x10
    int 0x10
    mov [0x7e06], bx
    mov [0x7e08], cx
    mov ah, 0x88
    int 0x15
    add ax, 1024
    mov [0x7e0a], ax
    mov ax, [0x7e04]
    xchg al, ah
    xor ah, ah
    shl ax, 1
    mov word [0x7e02], ax
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
; 无法开启 A20, 报错
    .A20_ns:
        mov ax, 0x0007
        push word [0x7c20]
        push word [0x7c22]
        retf
wait_8042_1:    ; 等待函数 1
    call step2
    in al, 0x64
    test al, 1
    jnz wait_8042_1
    ret
wait_8042_2:    ; 等待函数 2
    call step2
    in al, 0x64
    test al, 2
    jz wait_8042_2
    ret
step2:          ; 等待函数 3
    nop
    jmp $+2
    nop
    jmp $+2
    nop
    ret
test_A20:       ; 测试 A20
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
set_8259:       ; 8259 中断控制芯片编程
    ; 将硬件中断重定向到 32~47
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
set_description_table:          ; 設定描述符表
    mov ax, ADDR_SEG_SET_PROG
    mov ds, ax
    lgdt [ds:gdt_info - $$]
    lidt [ds:idt_info - $$]
set_cr0_PE:                     ; 开启保护模式
    mov eax, cr0
    or eax, 0x00000001          ; 置PE位
    mov cr0, eax
    jmp dword 0x0008:_start32   ; 刷新流水线

bits 32
align 4
errors32:
    pushad
    mov esi, message.texta
    call puts32
    mov eax, [esp + 4]
    call putx32
    mov esi, message.textb
    call puts32
    mov esi, message.textrega
    call puts32
    mov eax, [esp + 28]
    call putx32
    mov esi, message.textregc
    call puts32
    mov eax, [esp + 24]
    call putx32
    mov esi, message.textregd
    call puts32
    mov eax, [esp + 20]
    call putx32
    mov esi, message.textregb
    call puts32
    mov eax, [esp + 16]
    call putx32
    popad
    jmp $
puts32:
    pushad
    .puts_loop:
        mov al, [esi]
        inc esi
        test al, al
        jz .puts_ret
        call putc32
        jmp .puts_loop
    .puts_ret:
        popad
        ret
putc32:               ; void putc (al)
    pushad
    xor ecx, ecx
    mov cx, [0x7e02]
    cmp al, 10
    je .newline
    cmp al, 13
    je .return
    cmp al, 9
    je .tab
    add ecx, 0xb8000
    mov edi, ecx
    mov ah, 0x0f
    mov [edi], ax
    sub ecx, 0xb8000 - 2
        jmp .ret
    .ret:
        mov [0x7e02], cx
        popad
        ret
    .newline:
        add cx, 0xa0
        jmp .ret
    .return:
        mov ax, cx
        xor dx, dx
        mov bx, 0xa0
        div bx
        sub cx, dx
        jmp .ret
    .tab:
        shr cx, 2
        inc cx
        shl cx, 2
        jmp .ret
putx32:               ; void putx (eax)
    pushad
    mov ecx, 8
    .putx_loop:
        push eax
        shr eax, 28
        cmp al, 0x0a
        jge .bigger10
        mov ah, '0'
        jmp .less10
        .bigger10   mov ah, 'a'-10
        .less10     add al, ah
        call putc32
        pop eax
        shl eax, 4
    loop .putx_loop
    popad
    ret
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
clean_low16k:                   ; 清空低 24kb 地址
    lea edi, [0]
    mov ecx, 0x1800
    xor eax, eax
    rep stosd
build_paging:                   ; 建立临时分页表
    mov eax, [pagings.pml5]
    mov ebx, [pagings.pml5 + 4]
    mov [0x2000], eax
    mov [0x2004], ebx
    mov eax, [pagings.pml4]
    mov ebx, [pagings.pml4 + 4]
    mov [0x3000], eax
    mov [0x3004], ebx
    mov eax, [pagings.pdpt]
    mov ebx, [pagings.pdpt + 4]
    mov [0x4000], eax
    mov [0x4004], ebx
    mov ecx, 8*8/4
    lea esi, [pagings.pd]
    lea edi, [0x5000]
    .loop1:
        lodsd
        stosd
        loop .loop1
    
check_cpuid:                    ; 检查 CPUID 指令支持
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
    mov esi, 0x00000004
    jz errors32
check_long_mode:                ; 检查 Long-Mode 标志位
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    mov esi, 0x00000005
    jb errors32
    mov eax, 0x80000001
    cpuid
    and edx, 1 << 29
    test edx, edx
    mov esi, 0x00000006
    jz errors32
    mov esi, message.textc
    call puts32
_try64:
    mov eax, cr4                ; 开启物理地址扩展 & LA57
    or eax, 0x00000120  ; 0x00000120
    mov cr4, eax
    mov eax, 0x00003000 ; 0x00001000    ; 设置分页地址
    mov cr3, eax
    mov ecx, 0xc0000080         ; 开启长模式
    rdmsr
    or eax, 0x00000100
    wrmsr
    mov eax, cr0                ; 开启分页
    or eax, 0x80000001
    mov cr0, eax
    jmp dword 0x0018:_start64   ; 刷新流水线
bits 64
_start64:
    mov ax, 0x0020
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov rsp, 0x7e00
    mov rbp, rsp
    xor rdi, rdi
    xor rsi, rsi
    jmp 0x00008800

times 4096 -($ - $$) db 0
