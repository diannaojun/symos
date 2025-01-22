	.file	"kernel.c"
	.intel_syntax noprefix
# GNU C17 (Ubuntu 13.3.0-6ubuntu2~24.04) version 13.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 13.3.0, GMP version 6.3.0, MPFR version 4.2.1, MPC version 1.3.1, isl version isl-0.26-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -m64 -masm=intel -mtune=generic -march=x86-64 -ffunction-sections -ffreestanding -fno-builtin -fno-pie -fasynchronous-unwind-tables -fstack-clash-protection -fcf-protection
	.text
	.section	.rodata
.LC0:
	.string	"FROM C: Loading Kernel64...\n\r"
	.section	.text.main,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64	
	push	rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp	#,
	.cfi_def_cfa_register 6
# kernel.c:9:     putsk((char *)0x980c7);
	mov	edi, 622791	#,
	call	putsk	#
# kernel.c:10:     breakpoint();
	call	breakpoint	#
# kernel.c:11:     putsk("FROM C: Loading Kernel64...\n\r");
	mov	edi, OFFSET FLAT:.LC0	#,
	call	putsk	#
# kernel.c:12:     breakpoint();
	call	breakpoint	#
.L2:
# kernel.c:13:     for (;;)
	jmp	.L2	#
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.text.putck,"ax",@progbits
	.globl	putck
	.type	putck, @function
putck:
.LFB1:
	.cfi_startproc
	endbr64	
	push	rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp	#,
	.cfi_def_cfa_register 6
	sub	rsp, 16	#,
	mov	eax, edi	# tmp119, ch
	mov	BYTE PTR [rbp-4], al	# ch, tmp120
# kernel.c:19:     ch = toascii(ch);
	movsx	eax, BYTE PTR [rbp-4]	# _1, ch
	mov	edi, eax	#, _1
	call	toascii	#
# kernel.c:19:     ch = toascii(ch);
	mov	BYTE PTR [rbp-4], al	# ch, _2
# kernel.c:20:     switch (ch) {
	movsx	eax, BYTE PTR [rbp-4]	# _3, ch
	cmp	eax, 13	# _3,
	je	.L4	#,
	cmp	eax, 13	# _3,
	jg	.L5	#,
	cmp	eax, 9	# _3,
	je	.L6	#,
	cmp	eax, 10	# _3,
	je	.L7	#,
	jmp	.L5	#
.L6:
# kernel.c:22:         *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
	mov	eax, 32258	# _4,
	movzx	eax, WORD PTR [rax]	# _5, *_4
# kernel.c:22:         *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
	add	eax, 7	# _7,
# kernel.c:22:         *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
	mov	edx, 32258	# _9,
# kernel.c:22:         *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
	and	eax, -8	# _10,
# kernel.c:22:         *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
	mov	WORD PTR [rdx], ax	# *_9, _10
# kernel.c:23:         break;
	jmp	.L8	#
.L7:
# kernel.c:25:         *((short *)0x7e02) += 160;
	mov	eax, 32258	# _11,
	movzx	eax, WORD PTR [rax]	# _12, *_11
# kernel.c:25:         *((short *)0x7e02) += 160;
	lea	edx, [rax+160]	# _14,
# kernel.c:25:         *((short *)0x7e02) += 160;
	mov	eax, 32258	# _15,
# kernel.c:25:         *((short *)0x7e02) += 160;
	mov	WORD PTR [rax], dx	# *_15, _16
# kernel.c:26:         break;
	jmp	.L8	#
.L4:
# kernel.c:28:         *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
	mov	eax, 32258	# _17,
	movzx	eax, WORD PTR [rax]	# _18, *_17
# kernel.c:28:         *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
	add	eax, 7	# _20,
# kernel.c:28:         *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
	mov	edx, 32258	# _22,
# kernel.c:28:         *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
	and	eax, -8	# _23,
# kernel.c:28:         *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
	mov	WORD PTR [rdx], ax	# *_22, _23
# kernel.c:29:         break;
	jmp	.L8	#
.L5:
# kernel.c:31:         *(short *)(size_t)(0xb8000 | *((short *)0x7e02)) = ch | 0x0f00;
	movsx	ax, BYTE PTR [rbp-4]	# _24, ch
# kernel.c:31:         *(short *)(size_t)(0xb8000 | *((short *)0x7e02)) = ch | 0x0f00;
	mov	edx, 32258	# _25,
	movzx	edx, WORD PTR [rdx]	# _26, *_25
	movsx	edx, dx	# _27, _26
# kernel.c:31:         *(short *)(size_t)(0xb8000 | *((short *)0x7e02)) = ch | 0x0f00;
	or	edx, 753664	# _28,
# kernel.c:31:         *(short *)(size_t)(0xb8000 | *((short *)0x7e02)) = ch | 0x0f00;
	movsx	rdx, edx	# _29, _28
# kernel.c:31:         *(short *)(size_t)(0xb8000 | *((short *)0x7e02)) = ch | 0x0f00;
	or	ah, 15	# _31,
# kernel.c:31:         *(short *)(size_t)(0xb8000 | *((short *)0x7e02)) = ch | 0x0f00;
	mov	WORD PTR [rdx], ax	# *_30, _31
# kernel.c:32:         *((short *)0x7e02) += 2;
	mov	eax, 32258	# _32,
	movzx	eax, WORD PTR [rax]	# _33, *_32
# kernel.c:32:         *((short *)0x7e02) += 2;
	lea	edx, [rax+2]	# _35,
# kernel.c:32:         *((short *)0x7e02) += 2;
	mov	eax, 32258	# _36,
# kernel.c:32:         *((short *)0x7e02) += 2;
	mov	WORD PTR [rax], dx	# *_36, _37
.L8:
# kernel.c:34:     return;
	nop	
# kernel.c:35: }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1:
	.size	putck, .-putck
	.section	.text.putsk,"ax",@progbits
	.globl	putsk
	.type	putsk, @function
putsk:
.LFB2:
	.cfi_startproc
	endbr64	
	push	rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp	#,
	.cfi_def_cfa_register 6
	sub	rsp, 16	#,
	mov	QWORD PTR [rbp-8], rdi	# str, str
# kernel.c:39:     for (i = 0; str[i]; ++i)
	mov	QWORD PTR i.0[rip], 0	# i,
# kernel.c:39:     for (i = 0; str[i]; ++i)
	jmp	.L11	#
.L12:
# kernel.c:40:         putck(str[i]);
	mov	rdx, QWORD PTR i.0[rip]	# i.0_1, i
	mov	rax, QWORD PTR [rbp-8]	# tmp91, str
	add	rax, rdx	# _2, i.0_1
	movzx	eax, BYTE PTR [rax]	# _3, *_2
# kernel.c:40:         putck(str[i]);
	movsx	eax, al	# _4, _3
	mov	edi, eax	#, _4
	call	putck	#
# kernel.c:39:     for (i = 0; str[i]; ++i)
	mov	rax, QWORD PTR i.0[rip]	# i.1_5, i
	add	rax, 1	# _6,
	mov	QWORD PTR i.0[rip], rax	# i, _6
.L11:
# kernel.c:39:     for (i = 0; str[i]; ++i)
	mov	rdx, QWORD PTR i.0[rip]	# i.2_7, i
	mov	rax, QWORD PTR [rbp-8]	# tmp92, str
	add	rax, rdx	# _8, i.2_7
	movzx	eax, BYTE PTR [rax]	# _9, *_8
# kernel.c:39:     for (i = 0; str[i]; ++i)
	test	al, al	# _9
	jne	.L12	#,
# kernel.c:41:     return;
	nop	
# kernel.c:42: }
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2:
	.size	putsk, .-putsk
	.local	i.0
	.comm	i.0,8,8
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
