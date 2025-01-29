#include <stddef.h>
#include <kernel/asm.h>

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
