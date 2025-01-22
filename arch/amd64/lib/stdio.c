#include <ctype.h>
#include <stdio.h>

uint16_t atoi(const char *str) {
    uint16_t num = 0;
    while (_isdigit(*str))
        num = num * 10 + *str++ - '0';
    return num;
}
int vsprintf(char *buf, const char *fmt, va_list args) {
    char *str;
    int flag;
    for (str = buf; *fmt; fmt++) {
        if (*fmt != '%') {
            *str++ = *fmt;
            continue;
        }
        flag = 0;
    loop:
        switch (*++fmt) {
        case '-':
            flag |= __STDIO_LEFT__;
            goto loop;
        case '+':
            flag |= __STDIO_SIGNED__;
            goto loop;
        case '0':
            flag |= __STDIO_ZERO__;
            goto loop;
        case '*':
            flag |= __STDIO_ASTA__;
            goto loop;
        }
        return -1;
    }
    int printf(const char *fmt, ...) { return -1; }
