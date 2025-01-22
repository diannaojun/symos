#ifndef __STDIO_H__
#define __STDIO_H__

#include <stdarg.h>
#include <string.h>

int vsprintf(char *buf, const char *fmt, va_list args);
int printf(const char *fmt, ...);

#endif
