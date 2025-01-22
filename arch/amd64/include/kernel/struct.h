#ifndef __KERNEL_STRUCT_H__
#define __KERNEL_STRUCT_H__

#include <stddef.h>

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t attr;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t _high;
} idt_element_t;

typedef struct {
    uint16_t size;
    uint64_t addr;
} idt_header_t;

typedef struct virtual_node {
    char name[8];
    uint64_t hash1;
    uint64_t hash2;
    struct virtual_node *son, *nxt;
} virtual_node_t;

typedef struct boot_info {
    uint16_t init_dev;
    uint16_t screan_pos;
    uint8_t screan_mode;
    uint8_t screan_rows;
    uint8_t screan_mems;
    uint8_t screan_stat;
    uint16_t screan_attr;
    uint16_t loaded_mem;
} boot_info_t;

#endif // __KERNEL_STRUCT_H__
