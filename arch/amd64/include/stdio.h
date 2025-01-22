#ifndef __STDIO_H__
#define __STDIO_H__

#include <stdarg.h>
#include <string.h>

#define __STDIO_LEFT__   1
#define __STDIO_SIGNED__ 2
#define __STDIO_ZERO__   4
#define __STDIO_ASTA__   8

int atoi(const char *str);
int vsprintf(char *buf, const char *fmt, va_list args);
int printf(const char *fmt, ...);

#endif
