; Symbol DT
; Sym C Lib
; DiannaoJun
; 2024-04-30

global memcpy,memset

[bits 32]
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