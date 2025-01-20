#ifndef __STRING_H__
#define __STRING_H__

#include <stddef.h>

uint64_t hash1(const char *str);
uint64_t hash2(const char *str);
int strcpy(char *dest, const char *src);
int strcat(char *dest, const char *src);
int strcmp(const char *str1, const char *str2);
int strncpy(char *dest, const char *src, size_t count);
int strncat(char *dest, const char *src, size_t count);
int strncmp(const char *str1, const char *str2, size_t count);

#endif // __STRING_H__
