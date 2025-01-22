#ifndef __STDIO_H__
#define __STDIO_H__

#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define __STDIO_LEFT__   0x01
#define __STDIO_SIGNED__ 0x02
#define __STDIO_SIGNAL__ 0x04
#define __STDIO_EXT__    0x08
#define __STDIO_UPPER__  0x10
#define __STDIO_NUMBER__ 0x20

int vsprintf(char *buf, const char *fmt, va_list args);
int printf(const char *fmt, ...);

#endif
