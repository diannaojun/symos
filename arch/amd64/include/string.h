#ifndef __STRING_H__
#define __STRING_H__

#ifndef def_ulint_t
#define def_ulint_t
typedef unsigned long long ulint_t;
#endif

ulint_t hash1(const char *str);
ulint_t hash2(const char *str);

#endif // __STRING_H__
