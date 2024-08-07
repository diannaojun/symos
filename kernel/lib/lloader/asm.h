/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-05
 */
#ifndef _SYM_KERNEL_ASM_H_
#define _SYM_KERNEL_ASM_H_

#include <ia64/stddef.h>

extern void _hlt (void);                    // 闲置 CPU 直到中断发生
extern void _sti (void);                    // 启用中断
extern void _cli (void);                    // 禁用中断
extern void _nop (void);                    // 空指令
extern void _fin (void);                    // 死循环

extern u64 _in8 (u64);                      // 从端口 $1 读入 1 字节
extern u64 _in16 (u64);                     // 从端口 $1 读入 2 字节
extern u64 _in32 (u64);                     // 从端口 $1 读入 4 字节
extern void _out8 (u64,u64);                 // 向端口 $1 写出 1 字节
extern void _out16 (u64,u64);               // 向端口 $1 写出 2 字节
extern void _out32 (u64,u64);               // 向端口 $1 写出 4 字节

extern void memset (void*,u64,size_t);      // 将从 $1 开始的 $3 长度的内存全部置为 $2 的低 8 位
extern void memcpy (void*,void*,size_t);    // 将 $2 复制到 $1，长度是 $3
extern void strset (void*,u64);             // 将从 $1 开始的字符串全部置为 $2 的低 8 位
extern size_t strlen (void*);               // 获取 $1 的字符串长度

#endif //_SYM_KERNEL_ASM_H_
