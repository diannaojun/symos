; Symbol DT
; SymOS
; DiannaoJun
; 2024-04-27

global memcpy,memset,delay
global _hlt,_sti,_cli,_fin,_nop
global _in8,_in16,_in32
global _out8,_out16,_out32
global support_CPUID
global support_long_mode,enter_long_mode

[bits 32]
[section .data]

REG_TEMP:
    .ESI    DD 0
    .EBX    DD 0
    .ECX    DD 0
    .EDX    DD 0

[section .text]

memcpy:
    push ebp
    mov ebp,esp
    push esi
    push edi
    mov edi,[ebp+08h]
    mov esi,[ebp+0ch]
    mov ecx,[ebp+10h]
    rep movsb
    pop edi
    pop esi
    pop ebp
    ret

memset:
    push ebp
    mov ebp,esp
    push esi
    push edi
    mov edi,[ebp+08h]
    mov eax,[ebp+0ch]
    xor ecx,ecx 
    mov cl,al
    mov ch,al
    mov eax,ecx
    shr ecx,16
    or eax,ecx
    mov ecx,[ebp+10h]
    .LOOP:
        cmp ecx,4
        jl .END
        mov [edi],eax
        add edi,4
        sub ecx,4
        jmp .LOOP
    .END:
        test ecx,ecx
        jz .RET
        mov [edi],al
        inc edi
        dec ecx
        jmp .END
    .RET:
    pop edi
    pop esi
    pop ebp
    ret

delay:
    push ebp
    mov ebp,esp
    mov eax,[ebp+08h]
    .NOP:
        nop
        test eax,eax
        jz .RET
        dec eax
        jmp .NOP
    .RET:
    pop ebp
    ret

_hlt:
    hlt
    ret

_sti:
    sti
    ret

_cli:
    cli
    ret

_nop:
    nop
    ret

_fin:
    hlt
    nop
    jmp _fin
    ret

_in8:
    push ebp
    mov ebp,esp
    mov eax,[ebp+0x08]
    mov dx,ax
    xor eax,eax
    in al,dx
    pop ebp
    ret

_in16:
    push ebp
    mov ebp,esp
    mov eax,[ebp+0x08]
    mov dx,ax
    xor eax,eax
    in ax,dx
    pop ebp
    ret

_in32:
    push ebp
    mov ebp,esp
    mov eax,[ebp+0x08]
    mov dx,ax
    xor eax,eax
    in eax,dx
    pop ebp
    ret

_out8:
    push ebp
    mov ebp,esp
    mov eax,[ebp+0x08]
    mov dx,ax
    mov eax,[ebp+0x0c]
    out dx,al
    pop ebp
    ret

_out16:
    push ebp
    mov ebp,esp
    mov eax,[ebp+0x08]
    mov dx,ax
    mov eax,[ebp+0x0c]
    out dx,ax
    pop ebp
    ret

_out32:
    push ebp
    mov ebp,esp
    mov eax,[ebp+0x08]
    mov dx,ax
    mov eax,[ebp+0x0c]
    out dx,eax
    pop ebp
    ret

[section .data]

%include "./lib/loader/xdt.inc"
GDT64_BGN:
    SEG_NULL                                ; #0 空段
    SEG STA_X|STA_R,0x0,0x0,GDT64           ; #1 代码段
    SEG STA_W,0x0,0x0,GDT64                 ; #2 数据段
GDT64_END:
GDT64_INFO:
    dw GDT64_END-GDT64_BGN-1
    dd GDT64_BGN

[section .text]

support_CPUID:
    push ebx
    push ecx
    push edx
    pushfd
    pop eax
    mov ebx,eax
    xor eax,0x200000
    push eax
    popfd
    pushfd
    pop eax
    push ebx
    popfd
    xor ecx,ecx
    mov edx,0x1
    xor eax,ebx
    cmovz edx,ecx
    mov eax,edx
    pop edx
    pop ecx
    pop ebx
    ret

support_long_mode:
    mov eax,0x80000000
    cpuid
    cmp eax,0x80000001
    setnb al
    jb support_long_mode
    mov eax,0x80000001
    cpuid
    bt edx,29
    setc al
    movzx eax,al
    ret

enter_long_mode:
    lgdt [GDT64_INFO]
    mov ax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax
    mov esp,0x7c00
    ; 禁用分页
    mov eax,cr0
    btr eax,31
    mov cr0,eax
    ; 开启“物理地址扩展”
    mov eax,cr4
    bts eax,5
    mov cr4,eax
    ; 开启 Long-Mode
    mov ecx,0xc0000080
    rdmsr
    bts eax,8
    wrmsr
    ; 设置页面地址
    mov eax,0x00d000
    mov cr3,eax
    ; 启用分页
    mov eax,cr0
    bts eax,31
    mov cr0,eax
    mov ax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    jmp dword 0x0008:MODE64
    ret

[bits 64]

MODE64:
    call 0x00020000
