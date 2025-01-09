%include "config.inc"
org ADDR_SEG_SET_PROG << 4
bits 16

; ------ 00500
; STACK
; ------ 08000

jmp _start

gdt:
    .null   gdt_null
    .code   gdt_segment 0x00000000, 0xffffffff, sta_prog | sta_prog_x | sta_prog_xwr | sta_level0 | sta_existent, stt_32def | stt_limitalign4kb
    .data   gdt_segment 0x00000000, 0xffffffff, sta_prog | sta_prog_d | sta_prog_xwr | sta_level0 | sta_existent, stt_32def | stt_limitalign4kb
    .end:
gdt_info:
    dw gdt.end - gdt
    dd gdt
idt_info:
    times 3 dw 0
screan:
    .pos    dw 0
    .texta  db "[SETUP32::err(", 0
    .textb  db ")] ", 0
    .textc  db "0000", 0
    .textd  db "OK!!!", 0

_start:
    xor ax, ax
    mov ds, ax
    cli
setA20e:
    call wait8064
    mov al, 0xd1
    out 0x64, al
    call wait8064
    mov al, 0xdf
    out 0x60, al
    call wait8064
    in al, 0x92
    or al, 0x02
    out 0x92, al
setXDT:
    xchg bx, bx
    mov ax, ADDR_SEG_SET_PROG
    mov ds, ax
    lgdt [ds:gdt_info - $$]
    lidt [ds:idt_info - $$]
setCR0PE:
    mov eax, cr0
    or eax, 0x00000001
    mov cr0, eax
    jmp dword 0x0008:_start32
wait8064:
    in al, 0x64
    test al, 0x02
    jnz wait8064
    ret

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
    mov ax, 0x0006
    jz errors
    mov esi, screan.textd
    call puts
jmp $
errors:
    push ax
    mov esi, screan.texta
    call puts
    pop ax
    call putx
    mov esi, screan.textb
    call puts
    jmp $
puts:
    .puts_loop:
        mov al, [esi]
        inc esi
        test al, al
        jz .puts_ret
        call putc
        jmp .puts_loop
    .puts_ret:
        ret
putc:               ; void putc (al)
    movzx ecx, word [screan.pos]
    add ecx, 0xb8000
    mov edi, ecx
    mov ah, 0x0f
    mov [edi], ax
    movzx ecx, word [screan.pos]
    add ecx, 2
    mov [screan.pos], cx
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
        .big10:
            add al, 'a'-10
        .show:
        push cx
        call putc
        pop cx
        pop ax
        shl ax, 4
    loop .putx_loop
    ret

times 4096 -($ - $$) db 0
