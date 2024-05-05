/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-04-29
 */
#ifndef _SYM_KERNEL_MAIN_H_
#define _SYM_KERNEL_MAIN_H_

#include <IA32/stddef.h>

void _hlt(void);
void _sti(void);
void _cli(void);
void _fin(void);
void _nop(void);
u32 _in8(u32);
u32 _in16(u32);
u32 _in32(u32);
void _out8(u32,u32); //p,v
void _out16(u32,u32);
void _out32(u32,u32);
void memcpy(void*dect,void*src,u32 len);
void memset(void*dect,u32 value,u32 len);
void delay(u32 tim);
int chkSupCPUID(void);
int chkSup64(void);
void Enter();

#endif //_SYM_KERNEL_MAIN_H_