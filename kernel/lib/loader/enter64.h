/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-04-05
 */
#ifndef _SYM_KERNEL_ENTER64_H_
#define _SYM_KERNEL_ENTER64_H_

#include <lib/loader/main.h>
#include <lib/loader/paging_init.h>
#include <lib/loader/segment_init.h>
#include <lib/loader/print.h>


u8 checkSupport64(){
    if(!chkSupCPUID()){
        return 0x02;
    }
    return 0x00;
}
void enter64(void){
	if(checkSupport64())
		_fin();
    buildTempPages();
    // struct PAGE_ITEM*p=0x90000;
    // printsl("\n\rPageBase: ");
    // printdl(p->addr);
    // printsl("\n\rACS: ");
    // printdl(p->flag);
    // printsl("\n\rK: ");
    // printdl(*(u64*)p);
    // p=0x91000;
    // printsl("\n\rPageBase: ");
    // printdl(p->addr);
    // printsl("\n\rACS: ");
    // printdl(p->flag);
    // printsl("\n\rK: ");
    // printdl(*(u64*)p);
    // p=0x92000;
    // printsl("\n\rPageBase: ");
    // printdl(p->addr);
    // printsl("\n\rACS: ");
    // printdl(p->flag);
    // printsl("\n\rK: ");
    // printdl(*(u64*)p);
    // p=0x92000+8*8;
    // printsl("\n\rPageBase: ");
    // printdl(p->addr);
    // printsl("\n\rACS: ");
    // printdl(p->flag);
    // printsl("\n\rK: ");
    // printdl(*(u64*)p);
    Enter();
    return ;
}
#endif