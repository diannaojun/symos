/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-05
 */
#ifndef _SYM_KERNEL_ASM_H_
#define _SYM_KERNEL_ASM_H_

#include <IA64/stddef.h>

extern void _hlt(void);
extern void _sti(void);
extern void _cli(void);
extern void _nop(void);
extern void _fin(void);

extern u64 _in8(u64);
extern u64 _in16(u64);
extern u64 _in32(u64);
extern void out8(u64,u64);
extern void _out16(u64,u64);
extern void _out32(u64,u64);

extern void memset(void*,u64,size_t);
extern void memcpy(void*,void*,size_t);
extern void strset(void*,u64);
extern size_t strlen(void*);

#endif //_SYM_KERNEL_ASM_H_
