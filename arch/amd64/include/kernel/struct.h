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

#define MMBLK_ABSENT    0x0 /*內存頁面不存在（大頁面、原子項）*/
#define MMBLK_RESERVED  0x1 /*內存頁面保留（大頁面、原子項）*/
#define MMBLK_PRESENT   0x2 /*內存頁面空閒（大頁面、原子項）*/
#define MMBLK_FULL      0x3 /*內存頁面滿（非原子項）*/
#define MMBLK_USED0     0x4 /*內存頁面被0環佔用（大頁面、原子項）*/
#define MMBLK_USED1     0x5 /*內存頁面被1環佔用（大頁面、原子項）*/
#define MMBLK_USED2     0x6 /*內存頁面被2環佔用（大頁面、原子項）*/
#define MMBLK_USED3     0x7 /*內存頁面被3環佔用（大頁面、原子項）*/
typedef struct mmblk4k {
    // 4KB頁面項（原子項）
    unsigned status:3;  // 狀態
    unsigned _:9;       // 忽略
    uint64_t time:52;   // 分配時間戳
} __attribute__((packed)) mmblk4k_t;
// sizeof = 8

typedef struct mmblk2m {
    unsigned status:3;  // 狀態
    uint16_t avalable:9;// 可用數量
    uint64_t addr:52;   // 下級頁表起始地址 / 分配時間戳（大頁面） 
} __attribute__((packed)) mmblk2m_t;
// sizeof = 8

typedef struct mmblk1g {
    unsigned status:3;  // 狀態
    uint16_t avalable:9;// 可用數量
    uint64_t addr:52;   // 下級頁表起始地址 / 分配時間戳（大頁面）
} __attribute__((packed)) mmblk1g_t;
// sizeof = 8

typedef struct mmblk512g {
    // 大頁面不可用
    unsigned status:3;  // 狀態
    uint16_t avalable:9;// 可用數量
    uint64_t addr:52;   // 下級頁表起始地址 / 分配時間戳（大頁面）
} __attribute__((packed)) mmblk512g_t;
// sizeof = 8

typedef struct mmblk256t {
    // 大頁面不可用
    unsigned status:3;  // 狀態
    uint16_t avalable:9;// 可用數量
    uint64_t addr:52;   // 下級頁表起始地址 / 分配時間戳（大頁面）
} __attribute__((packed)) mmblk256t_t;
// sizeof = 8

typedef struct mmblk128p {
    // 大頁面不可用
    unsigned status:3;  // 狀態
    uint16_t avalable:9;// 可用數量
    uint64_t addr:52;   // 下級頁表起始地址 / 分配時間戳（大頁面）
} __attribute__((packed)) mmblk128p_t;
// sizeof = 8

typedef struct mmblk64e {
    // 大頁面不可用
    unsigned status:3;  // 狀態
    uint16_t avalable:9;// 可用數量
    uint64_t addr:52;   // 下級頁表起始地址 / 分配時間戳（大頁面）
} __attribute__((packed)) mmblk64e_t;
// sizeof = 8


#endif // __KERNEL_STRUCT_H__
