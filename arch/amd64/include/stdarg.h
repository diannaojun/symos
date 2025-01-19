#ifndef __STDARG_H__
#define __STDARG_H__

#include <stddef.h>

#ifndef __def_va_list
    #define __def_va_list
    typedef ptr_t va_list;
#endif

#ifndef __va_rounded_size
    #define __va_rounded_size(type) (((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))
#endif

#ifndef va_start
    #define va_start(ap, lastarg) (ap = ((char *) &(lastarg) + __va_rounded_size (lastarg)))
#endif

#ifndef va_arg
    #define va_arg(ap, type) (*((type*)((ap += __va_rounded_size (type)) - __va_rounded_size (type))))
#endif

#ifndef va_end
    #define va_end(ap) (ap = (va_list) NULL)
#endif

#ifndef va_copy
    #define va_copy(d, s) (d = s)
#endif

#endif // __STDARG_H__
