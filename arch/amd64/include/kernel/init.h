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

#endif // __KERNEL_INIT_H__
