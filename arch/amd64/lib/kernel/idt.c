#include <stddef.h>
#include <kernel/memory/idt.h>
#include <kernel/asm.h>

static void set_idt(idt_element_t *idt, void *func, uint8_t attr){
    idt->base_low = ((size_t)func) & 0x0000ffff;
    idt->base_mid = (((size_t)func) >> 16) & 0x0000ffff;
    idt->base_high = (((size_t)func) >> 32) & 0xffffffff;
    idt->selector = 0x18;
    idt->attr = attr;
    idt->ist = 0;
    return ;
}

void init_idt(void){
    xdt_header_t *idr_hdr = (xdt_header_t *)0x7ee0;
    idt_element_t *idt_item = (idt_element_t *)0x1000;
    idr_hdr->addr = (size_t)idt_item;
    idr_hdr->size = sizeof(idt_element_t) * 256;
    set_idt(idt_item + 0, devide_error, TRAP_GATE);
    set_idt(idt_item + 1, debug, TRAP_GATE);
    set_idt(idt_item + 2, nmi, INT_GATE);
    set_idt(idt_item + 3, break_point, SYS_GATE);
    set_idt(idt_item + 4, bounds, SYS_GATE);
    set_idt(idt_item + 5, over_flow, SYS_GATE);
    set_idt(idt_item + 6, invalid_opcode, TRAP_GATE);
    set_idt(idt_item + 7, device_not_available, TRAP_GATE);
    set_idt(idt_item + 8, double_fault, TRAP_GATE);
    set_idt(idt_item + 9, coprocessor_segment_overrun, TRAP_GATE);
    set_idt(idt_item + 10, invalid_tss, TRAP_GATE);
    set_idt(idt_item + 11, segment_not_available, TRAP_GATE);
    set_idt(idt_item + 12, stack_segment, TRAP_GATE);
    set_idt(idt_item + 13, general_protection, TRAP_GATE);
    set_idt(idt_item + 14, page_fault, TRAP_GATE);
    set_idt(idt_item + 15, reserved, TRAP_GATE);
    set_idt(idt_item + 16, coprocessor_error, TRAP_GATE);
    set_idt(idt_item + 0x80, syscall, SYS_GATE);
    lidt(idr_hdr);
    return ;
}

void do_devide_error(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcxA, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_debug(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_nmi(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_break_point(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
        breakpoint();
    return ;
}
void do_bounds(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_over_flow(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_invalid_opcode(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_device_not_available(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_double_fault(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_coprocessor_segment_overrun(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_invalid_tss(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_segment_not_available(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_stack_segment(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_general_protection(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_page_fault(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_coprocessor_error(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    return ;
}
void do_syscall(uint64_t rdi, uint64_t rsi,
    uint64_t rdx, uint64_t rcx, uint64_t r8,
    uint64_t r9, uint64_t r10, uint64_t r11,
    uint64_t r12, uint64_t r13, uint64_t r14,
    uint64_t r15, uint64_t rax, uint64_t rbx,
    uint64_t rbp, uint64_t tr, uint64_t ds,
    uint64_t es, uint64_t fs, uint64_t gs,
    uint64_t err, uint64_t rip, uint64_t cs,
    uint64_t rflags, uint64_t rsp, uint64_t ss){
    if(err)
        return ;
    switch(rax){
        case 0:
            break;
        default:
            ;
    }
    return ;
}
