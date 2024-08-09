; Symbol DT
; Sym C Lib
; DiannaoJun
; 2024-04-30
BITS 32
GLOBAL memcpy,memset,strlen,strset
[section .text]

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
	mov argd2,rax
	call memset
	ret
memset:
	mov rax,argd1
	call _raxfull
		memset_loop:
	cmp argd2,8
	jl memset_lloop
	mov [argd0],rax
	sub argd2,8
	add argd0,8
	jmp memset_loop
		memset_lloop:
	test argd2,argd2
	jz _ret
	mov [argd0],al
	dec argd2
	inc argd0
	jmp memset_lloop
memcpy:
	mov r10,argd0
	mov r11,argd1
	mov rdi,r10
	mov rsi,r11
    mov rcx,argd2
    rep movsb
    ret
_raxfull:
	xor r11,r11
	or r11,rax
	shl r11,8
	or r11,rax
	shl r11,8
	or r11,rax
	shl r11,8
	or r11,rax
	shl r11,8
	or r11,rax
	shl r11,8
	or r11,rax
	shl r11,8
	or r11,rax
	shl r11,8
	or r11,rax
	mov rax,r11
_ret:
	ret
