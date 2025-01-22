#ifndef __KERNEL_INIT_H__
#define __KERNEL_INIT_H__

#include <stddef.h>
#include <kernel/asm.h>
#include <kernel/struct.h>
#include <ctype.h>

#define DRV_ADDR ((uint16_t *)0x7e00)
#define VPOS_ADDR ((uint16_t *)0x7e02)
#define VMODE_ADDR ((uint8_t *)0x7e04)
#define VROW_ADDR ((uint8_t *)0x7e05)
#define VMEM_ADDR ((uint8_t *)0x7e06)
#define VSTAT_ADDR ((uint8_t *)0x7e07)
#define VATTR_ADDR ((uint16_t *)0x7e08)
#define MEM_ADDR ((uint16_t *)0x7e0a)
#define BAS_ADDR 0xb8000

#define REG_INT(name) void name(void); void do_##name (uint64_t rdi, uint64_t rsi, \
    uint64_t rdx, uint64_t rcx, uint64_t r8, \
    uint64_t r9, uint64_t r10, uint64_t r11, \
    uint64_t r12, uint64_t r13, uint64_t r14, \
    uint64_t r15, uint64_t rax, uint64_t rbx, \
    uint64_t rbp, uint64_t tr, uint64_t ds, \
    uint64_t es, uint64_t fs, uint64_t gs, \
    uint64_t err, uint64_t rip, uint64_t cs, \
    uint64_t rflags, uint64_t rsp, uint64_t ss);
#define INT_GATE 0x8e
#define TRAP_GATE 0x8f

REG_INT(devide_error)
REG_INT(debug)
REG_INT(nmi)
REG_INT(break_point)
REG_INT(over_flow)
REG_INT(bounds)
REG_INT(invalid_opcode)
REG_INT(device_not_available)
REG_INT(double_fault)
REG_INT(coprocessor_segment_overrun)
REG_INT(invalid_tss)
REG_INT(segment_not_available)
REG_INT(stack_segment)
REG_INT(general_protection)
REG_INT(page_fault)
REG_INT(reserved)
REG_INT(coprocessor_error)
REG_INT(syscall)

#undef REG_INT


void init_gdt(void);
void init_idt(void);

#endif // __KERNEL_INIT_H__
