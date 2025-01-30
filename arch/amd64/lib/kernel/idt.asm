bits 64

section .text
%macro REG_INT 1
    extern do_%+%1
    global %1
%endmacro

REG_INT devide_error
REG_INT debug
REG_INT nmi
REG_INT break_point
REG_INT over_flow
REG_INT bounds
REG_INT invalid_opcode
REG_INT device_not_available
REG_INT double_fault
REG_INT coprocessor_segment_overrun
REG_INT invalid_tss
REG_INT segment_not_available
REG_INT stack_segment
REG_INT general_protection
REG_INT page_fault
REG_INT reserved
REG_INT coprocessor_error
REG_INT syscall

extern pass

devide_error:
    push qword 0
    push do_devide_error
    jmp errno_handle
debug:
    push qword 1
    push do_debug
    jmp errno_handle
nmi:
    push qword 2
    push do_nmi
    jmp errno_handle
break_point:
    push qword 3
    push do_break_point
    jmp errno_handle
over_flow:
    push qword 4
    push do_over_flow
    jmp errno_handle
bounds:
    push qword 5
    push do_bounds
    jmp errno_handle
invalid_opcode:
    push qword 6
    push do_invalid_opcode
    jmp errno_handle
device_not_available:
    push qword 7
    push do_device_not_available
    jmp errno_handle
double_fault:
    push do_double_fault
    jmp errno_handle
coprocessor_segment_overrun:
    push qword 9
    push do_coprocessor_segment_overrun
    jmp errno_handle
invalid_tss:
    push do_invalid_tss
    jmp errno_handle
segment_not_available:
    push do_segment_not_available
    jmp errno_handle
stack_segment:
    push do_stack_segment
    jmp errno_handle
general_protection:
    push do_general_protection
    jmp errno_handle
page_fault:
    push do_page_fault
    jmp errno_handle
reserved:
    push qword 15
    push do_coprocessor_segment_overrun
    jmp errno_handle
coprocessor_error:
    push qword 16
    push do_coprocessor_error
    jmp errno_handle
irq13:
    push rax
    xor al, al
    out 0x20, al
    mov al, 0x20
    call pass
    out 0xa0, al
    pop rax
    jmp coprocessor_error
syscall:
    push qword 0
    push do_syscall
errno_handle:
    push rax                ; err func rax
    xor rax, rax
    mov ax, es
    push rax                ; err func rax es
    mov ax, ds
    push rax                ; err func rax es ds
    mov ax, gs
    push rax                ; err func rax es ds gs
    push rbp                ; err func rax es ds gs rbp
    push rbx                ; err func rax es ds gs rbp rbx
    mov ax, fs
    push rax                ; err func rax es ds gs rbp rbx fs
    push r15                ; err func rax es ds gs rbp rbx fs r15
    push r14                ; err func rax es ds gs rbp rbx fs r15 r14
    push r13                ; err func rax es ds gs rbp rbx fs r15 r14 r13
    push r12                ; err func rax es ds gs rbp rbx fs r15 r14 r13 r12
    push r11                ; err func rax es ds gs rbp rbx fs r15 r14 r13 r12 r11
    push r10                ; err func rax es ds gs rbp rbx fs r15 r14 r13 r12 r11 r10
    xor rax, rax
    str ax
    xchg rax, [rsp + 72]    ; err func rax es ds tr rbp rbx fs r15 r14 r13 r12 r11 r10
    xchg rax, [rsp + 96]    ; err func gs es ds tr rbp rbx fs r15 r14 r13 r12 r11 r10
    xchg rax, [rsp + 48]    ; err func gs es ds tr rbp rbx rax r15 r14 r13 r12 r11 r10
    xchg rax, [rsp + 96]    ; err func fs es ds tr rbp rbx rax r15 r14 r13 r12 r11 r10
    xchg rax, [rsp + 104]   ; err gs fs es ds tr rbp rbx rax r15 r14 r13 r12 r11 r10
    call rax
    pop r10                 ; err gs fs es ds tr rbp rbx rax r15 r14 r13 r12 r11
    pop r11                 ; err gs fs es ds tr rbp rbx rax r15 r14 r13 r12
    pop r12                 ; err gs fs es ds tr rbp rbx rax r15 r14 r13
    pop r13                 ; err gs fs es ds tr rbp rbx rax r15 r14
    pop r14                 ; err gs fs es ds tr rbp rbx rax r15
    pop r15                 ; err gs fs es ds tr rbp rbx rax
    mov rax, [rsp + 32]     ; err gs fs es - tr rbp rbx rax
    mov ds, ax
    mov rax, [rsp + 40]     ; err gs fs - - tr rbp rbx rax
    mov es, ax
    mov rax, [rsp + 48]     ; err gs - - - tr rbp rbx rax
    mov fs, ax
    mov rax, [rsp + 48]     ; err - - - - tr rbp rbx rax
    mov gs, ax
    pop rax                 ; err - - - - tr rbp rbx
    pop rbx                 ; err - - - - tr rbp
    pop rbp                 ; err - - - - tr
    add rsp, 48             ;
    iretq
