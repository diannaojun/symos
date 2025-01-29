#ifndef __KERNEL_STRUCT_H__
#define __KERNEL_STRUCT_H__

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

typedef struct virtual_node {
    char name[8];
    uint64_t hash1;
    uint64_t hash2;
    struct virtual_node *son, *nxt;
} __attribute__((packed)) virtual_node_t;

typedef struct boot_info {
    uint16_t init_dev;
    uint16_t screan_pos;
    uint8_t screan_mode;
    uint8_t screan_rows;
    uint8_t screan_mems;
    uint8_t screan_stat;
    uint16_t screan_attr;
    uint16_t loaded_mem;
} __attribute__((packed)) boot_info_t;

typedef struct mmblk4k {
    unsigned present:1;
    unsigned free:1;
    unsigned level:2;
    unsigned _:8;
    uint64_t time:48;
    unsigned __:4;
} __attribute__((packed)) mmblk4k_t;

typedef struct mmblk2m {
    unsigned present:1;
    unsigned free:1;
    unsigned level:2;
    unsigned huge:1;
    uint8_t avilibal:7;
    uint64_t addr:52;
} __attribute__((packed)) mmblk2m_t;

typedef struct mmblk1g {
    unsigned present:1;
    unsigned free:1;
    unsigned level:2;
    unsigned huge:1;
    uint8_t avilibal:7;
    uint64_t addr:52;
} __attribute__((packed)) mmblk1g_t;

typedef struct mmblk512g {
    unsigned present:1;
    unsigned free:1;
    unsigned level:2;
    uint8_t avilibal:8;
    uint64_t addr:52;
} __attribute__((packed)) mmblk512g_t;

typedef struct mmblk256t {
    unsigned present:1;
    unsigned free:1;
    unsigned level:2;
    uint8_t avilibal:8;
    uint64_t addr:52;
} __attribute__((packed)) mmblk256t_t;

typedef struct mmblk128p {
    unsigned present:1;
    unsigned free:1;
    unsigned level:2;
    uint8_t avilibal:8;
    uint64_t addr:52;
} __attribute__((packed)) mmblk128p_t;

typedef struct mmblk64e {
    unsigned present:1;
    unsigned free:1;
    unsigned level:2;
    uint8_t avilibal:8;
    uint64_t addr:52;
} __attribute__((packed)) mmblk64e_t;

#endif // __KERNEL_STRUCT_H__
