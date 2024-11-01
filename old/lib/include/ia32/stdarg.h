/* Symbol DT
 * Sym C Lib
 * DiannaoJun
 * 2024-05-01
 */
#ifndef _STDARG_H_
#define _STDARG_H_

#include <ia32/stddef.h>
typedef void *va_list;

#define __va_rounded_size(TYPE) (((sizeof(TYPE)+sizeof(type)-1)/sizeof(type))*sizeof(type))

#ifndef __sparc__
#define va_start(AP, LASTARG) (AP=((void*)&(LASTARG)+__va_rounded_size(LASTARG)))
#else
#define va_start(AP, LASTARG) (__builtin_saveregs(),AP=((void*)&(LASTARG)+__va_rounded_size(LASTARG)))
#endif

void va_end (va_list);

#define va_end(AP)
#define va_arg(AP, TYPE) (AP+=__va_rounded_size(TYPE),*((TYPE*)(AP-__va_rounded_size(TYPE))))

#endif
