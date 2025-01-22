#ifndef __KERNEL_ASM_H__
#define __KERNEL_ASM_H__

#include <stddef.h>

void jump(void *ptr);
void call(void *ptr);
void lidt(void *ptr);
void breakpoint(void);
void hlt(void);
void sti(void);
void cli(void);
void std(void);
void cld(void);
void nop(void);
void pass(void);
uint64_t in8(uint64_t);
uint64_t in16(uint64_t);
uint64_t in32(uint64_t);
void out8(uint64_t, uint64_t);
void out16(uint64_t, uint64_t);
void out32(uint64_t, uint64_t);
void swap_seg(uint64_t);
void swap_reg(uint64_t);
void int80(void);

#endif // __KERNEL_ASM_H__
