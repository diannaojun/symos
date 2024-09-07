; Symbol DT
; SymOS
; DiannaoJun
; 2024-08-03

; rcx rdx r8 r9 rdi rsi xmm0-xmm3 rax(xmm0)
; rdi rsi rdx rcx r8 r9 xmm0-xmm7 rax
; 前六個參數以rdi,rsi,rdx,rcx,r8,r9傳遞
; 其他參數從rsp+8*6+8開始

%define argd0 rdi
%define argd1 rsi
%define rdx rdx
%define argd3 rcx
%define argd4 r8
%define argd5 r9
%define argf0 xmm0
%define argf1 xmm1
%define argf2 xmm2
%define argf3 xmm3

global _hlt, _sti, _cli, _nop, _fin
global _in8,_in16,_in32
global _out8,_out16,_out32
global memcpy,memset,strlen,strset

[bits 64]
[section .text]

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
    mov rdx,rdi
    xor rax,rax
    in al,dx
    ret

_in16:
    mov rdx,rdi
    xor rax,rax
    in ax,dx
    ret

_in32:
    mov rdx,rdi
    xor rax,rax
    in eax,dx
    ret

_out8:
    mov rdx,rdi
    mov rax,rsi
    out dx,al
    ret

_out16:
    mov rdx,rdi
    mov rax,rsi
    out dx,ax
    ret

_out32:
    mov rdx,rdi
    mov rax,rsi
    out dx,eax
    ret

strlen:
	xor rax,rax
	xor rbx,rbx
		strlen_loop:
	mov bl,[argd0]
	test bl,bl
	jz _ret
	inc rax
	inc argd0
	jmp strlen_loop

strset:
	push argd0
	call strlen
	pop argd0
	mov rdx,rax
	call memset
	ret

memset:
	test rdx, rdx
	jz _ret

	and rsi, 0x0ff
	xor rax, rax
	or rax, rsi
	shl rsi, 8
	or rax, rsi
	mov rsi, rax
	shl rsi, 16
	or rax, rsi
	mov rsi, rax
	shl rsi, 32
	or rax, rsi

	_memset_loop8:
		cmp rdx, 8
		jl _memset_loop
		mov [rdi], rax
		add rdi, 8
		sub rdx, 8
		jmp _memset_loop8
	_memset_loop:
		test rdx, rdx
		jz _ret
		mov [rdi], al
		dec rdx
		inc rdi
		jmp _memset_loop
	ret

memcpy:
	mov r10,rdi
	mov r11,rsi
    mov rcx,rdx
    rep movsb
    ret

_ret:
	ret
