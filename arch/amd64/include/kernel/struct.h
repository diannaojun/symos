#ifndef __KERNEL_STRUCT_H__
#define __KERNEL_STRUCT_H__

#include <stddef.h>

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t reserved;
    uint8_t type:4;
    uint8_t always0:1;
    uint8_t dpl:2;
    uint8_t present:1;
    uint16_t offset_high;
} idt_element_t;

typedef struct {
    uint16_t size;
    uint32_t addr;
} idt_header_t;

typedef struct virtual_node {
    char name[8];
    uint64_t hash1;
    uint64_t hash2;
    struct virtual_node *son, *nxt;
} virtual_node_t;

#endif // __KERNEL_STRUCT_H__
