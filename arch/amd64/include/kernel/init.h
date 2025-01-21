#ifndef __KERNEL_INIT_H__
#define __KERNEL_INIT_H__

#include <ctype.h>
#include <kernel/struct.h>

#define POS_ADDR ((short *)0x7e02)
#define BAS_ADDR 0xb8000
#define DRV_ADDR ((short *)0x7e00)

void init_paging(void);
void putc_init(char ch);
void puts_init(const char* str);
virtual_node_t *root_init(void);

#endif // __KERNEL_INIT_H__
