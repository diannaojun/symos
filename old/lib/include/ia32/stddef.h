/* Symbol DT
 * Sym C Lib
 * DiannaoJun
 * 2024-04-30
 */
#ifndef _STDDEF_H_
#define _STDDEF_H_

#ifndef _TYPEFLAGES_
#define _TYPEFLAGES_
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;
typedef u32 type;
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef u32 ptrdiff_t;
typedef u32 uintptr_t;
typedef i32 intptr_t;
typedef void *pointer;
#endif

#ifndef BOOL
#define BOOL unsigned char
#define TRUE 0x01
#define FALSE 0x00
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef u32 size_t;
#endif

#ifndef NULL
#define NULL ((void*)0)
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#endif