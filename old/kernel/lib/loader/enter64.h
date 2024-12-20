/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-04-05
 */
#ifndef _SYM_KERNEL_ENTER64_H_
#define _SYM_KERNEL_ENTER64_H_

#include <lib/loader/main.h>
#include <lib/loader/paging_init.h>
#include <lib/loader/loader.h>
#include <ia32/stddef.h>

int support_long_mode(void);
int support_CPUID(void);
void enter_long_mode(void);

void enter64(void) {
	buildTempPages();
	printsl("[Loader32] Temporary page successfully built\n\r");
	enter_long_mode();
	return ;
}
#endif
