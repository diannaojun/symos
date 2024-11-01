/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-04-29
 */
#ifndef _SYM_KERNEL_MAIN_H_
#define _SYM_KERNEL_MAIN_H_

#include <ia32/stddef.h>

void _hlt(void);
void _sti(void);
void _cli(void);
void _fin(void);
void _nop(void);
u32 _in8(u32);
u32 _in16(u32);
u32 _in32(u32);
void _out8(u32, u32); //p,v
void _out16(u32, u32);
void _out32(u32, u32);
void memcpy(void *dect, void *src, u32 len);
void memset(void *dect, u32 value, u32 len);
void delay(u32 tim);

int strcmpn(const char *str1, const char *str2, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		if (str1[i] != str2[i]) {
			return (unsigned char)str1[i] - (unsigned char)str2[i];
		}
		if (str1[i] == '\0' || str2[i] == '\0') {
			return 0;
		}
	}
	return 0;
}
#endif //_SYM_KERNEL_MAIN_H_
