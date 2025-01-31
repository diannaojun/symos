#ifndef __KERNEL_INIT_H__
#define __KERNEL_INIT_H__

#include <stddef.h>

#define DRV_ADDR ((uint16_t *)0x7e00)
#define VPOS_ADDR ((uint16_t *)0x7e02)
#define VMODE_ADDR ((uint8_t *)0x7e04)
#define VROW_ADDR ((uint8_t *)0x7e05)
#define VMEM_ADDR ((uint8_t *)0x7e06)
#define VSTAT_ADDR ((uint8_t *)0x7e07)
#define VATTR_ADDR ((uint16_t *)0x7e08)
#define MEM_ADDR ((uint16_t *)0x7e0a)
#define BAS_ADDR 0xb8000

typedef struct boot_info {
    uint16_t init_dev;
    uint16_t screan_pos;
    uint8_t screan_mode;
    uint8_t screan_rows;
    uint8_t screan_mems;
    uint8_t screan_stat;
    uint16_t screan_attr;
    uint8_t loaded_mem;
} __attribute__((packed)) boot_info_t;

void init_idt(void);
void init_mm(void);

#endif // __KERNEL_INIT_H__
