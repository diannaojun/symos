#ifndef __STDDEF_H__
#define __STDDEF_H__

#if __SIZEOF_POINTER__ == 8
    #ifndef __CPU_BITS__
	    #define __CPU_BITS__ 64
    #endif
    #ifndef NULL
	    #define NULL ((void*)0ull)
    #endif
    #ifndef __def_ptrdiff_t
        #define __def_ptrdiff_t
	    typedef unsigned long int ptrdiff_t;
    #endif
    #ifndef __def_size_t
        #define __def_size_t
	    typedef unsigned long int size_t;
    #endif
#else
    #error The SymLib cannot run on 32-bits mode.
#endif

#ifndef EMPTY
    #define EMPTY
#endif

#ifndef offsetof
    #define offsetof(type, member) ((ptrdiff_t)&(((type*)NULL)->member))
#endif

#ifndef __def_ptr_t
    #define __def_ptr_t
    typedef char *ptr_t;
#endif

#ifndef __def_wchar_t
    #define __def_wchar_t
    typedef unsigned int wchar_t;
#endif

#ifndef __def_int8_t
    #define __def_int8_t
    typedef signed char int8_t;
#endif
#ifndef __def_uint8_t
    #define __def_uint8_t
    typedef unsigned char uint8_t;
#endif
#ifndef __def_int16_t
    #define __def_int16_t
    typedef signed short int int16_t;
#endif
#ifndef __def_uint16_t
    #define __def_uint16_t
    typedef unsigned short int uint16_t;
#endif
#ifndef __def_int32_t
    #define __def_int32_t
    typedef signed int int32_t;
#endif
#ifndef __def_uint32_t
    #define __def_uint32_t
    typedef unsigned int uint32_t;
#endif
#ifndef __def_int64_t
    #define __def_int64_t
    typedef signed long int int64_t;
#endif
#ifndef __def_uint64_t
    #define __def_uint64_t
    typedef unsigned long int uint64_t;
#endif
#ifndef __def_intptr_t
    #define __def_intptr_t
    typedef int64_t intptr_t;
#endif
#ifndef __def_uintptr_t
    #define __def_uintptr_t
    typedef uint64_t uintptr_t;
#endif
#ifndef __def_float32_t
    #define __def_float32_t
    typedef float float32_t;
#endif
#ifndef __def_float64_t
    #define __def_float64_t
    typedef double float64_t;
#endif
#ifndef __def_float128_t
    #define __def_float128_t
    typedef long double float128_t;
#endif

#endif // __STDDEF_H__
