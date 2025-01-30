#ifndef __KERNEL_MEMORY_IDT_H__
#define __KERNEL_MEMORY_IDT_H__

#include <stddef.h>

#define REG_INT(name) void name(void); void do_##name (uint64_t rdi, uint64_t rsi, \
    uint64_t rdx, uint64_t rcx, uint64_t r8, \
    uint64_t r9, uint64_t r10, uint64_t r11, \
    uint64_t r12, uint64_t r13, uint64_t r14, \
    uint64_t r15, uint64_t rax, uint64_t rbx, \
    uint64_t rbp, uint64_t tr, uint64_t ds, \
    uint64_t es, uint64_t fs, uint64_t gs, \
    uint64_t err, uint64_t rip, uint64_t cs, \
    uint64_t rflags, uint64_t rsp, uint64_t ss);
#define INT_GATE    0x8e
#define TRAP_GATE   0x8f
#define SYS_GATE    0xef

#define ATTR_PRESENT    0x80
#define ATTR_NOT_PRESENT 0x0
#define ATTR_LEVEL0     0x00
#define ATTR_LEVEL1     0x20
#define ATTR_LEVEL2     0x40
#define ATTR_LEVEL3     0x60
#define ATTR_PROGRAM    0x10
#define ATTR_CODE       0x08
#define ATTR_DATA       0x00
#define ATTR_AC         0x04
#define ATTR_WR_XR      0x02
#define ATTR_DIRTY      0x01

#define FLAG_4KB        0x8000
#define FLAG_32D        0x4000
#define FLAG_64D        0x2000

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

typedef struct {
    uint16_t base_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t attr;
    uint16_t base_mid;
    uint32_t base_high;
    uint32_t _high;
} __attribute__((packed)) idt_element_t;

typedef struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t attr;
    uint8_t limit_high:4;
    uint8_t flag:4;
    uint8_t base_high;
    uint32_t _high;
} __attribute__((packed)) gdt_element_t;

typedef struct {
    uint16_t size;
    uint64_t addr;
} __attribute__((packed)) xdt_header_t;

void init_idt(void);

#endif // __KERNEL_MEMORY_IDT_H__
