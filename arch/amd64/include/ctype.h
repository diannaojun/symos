#ifndef __CTYPE_H__
#define __CTYPE_H__
#include <stddef.h>

#define _isalnum(ch) (_isalpha(ch) | isdigit(ch))
#define _isalpha(ch) (islower(ch) | isupper(ch))
#define _isascii(ch) (ch <= 127)
#define _isdigit(ch) (ch >= '0' && ch <= '9')

int isalnum(wchar_t);
int isalpha(wchar_t);
int isascii(wchar_t);
int iscntrl(wchar_t);
int isdigit(wchar_t);
int isgraph(wchar_t);
int islower(wchar_t);
int isprint(wchar_t);
int ispunct(wchar_t);
int isspace(wchar_t);
int isupper(wchar_t);
int isxdigit(wchar_t);
int toascii(wchar_t);
int tolower(wchar_t);
int toupper(wchar_t);

#endif // __CTYPE_H__
