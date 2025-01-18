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
	    typedef unsigned long long ptrdiff_t;
    #endif
#elif __SIZEOF_POINTER__ == 4
    #ifndef __CPU_BITS__
	    #define __CPU_BITS__ 32
    #endif
    #ifndef NULL
	    #define NULL ((void*)0u)
    #endif
    #ifndef __def_ptrdiff_t
        #define __def_ptrdiff_t
	    typedef unsigned int ptrdiff_t;
    #endif
#endif

#ifndef EMPTY
    #define EMPTY
#endif

#ifndef __def_ulint_t
    #define __def_ulint_t
    typedef unsigned long long ulint_t;
#endif

#ifndef __def_wchar_t
    #define __def_wchar_t
    typedef unsigned int wchar_t;
#endif

#endif // __STDDEF_H__
