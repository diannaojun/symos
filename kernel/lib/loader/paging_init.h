/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-04-29
 */
#ifndef _SYM_KERNEL_PAGING_INIT_H_
#define _SYM_KERNEL_PAGING_INIT_H_

#include <lib/loader/main.h>

#define PAGE_UA 0x000	// 禁用
#define PAGE_AB 0x001	// 启用
#define PAGE_RO 0x000	// 只读
#define PAGE_RW 0x002	// 读写
#define PAGE_SO 0x000	// 系统保护
#define PAGE_US 0x004	// 用户许可
#define PAGE_AC 0x020	// 访问标志
#define PAGE_DE 0x040	// 写入标志
#define PAGE_RL 0x080	// 实际标志
#define PAGE_GT 0x100	// 全局翻译
#define PAGE_PT 0x080	// 内存类型


#pragma pack(1)
struct PAGE_ITEM{
	u64 flag:12,addr:52;
};
void setPageItem(struct PAGE_ITEM*p,u64 base,u16 flag){
	p->addr=(base>>12);
	p->flag=flag&0x0fff;
	return;
}
void buildTempPages(void){
	static int i;
	struct PAGE_ITEM*pml4=(struct PAGE_ITEM*)0x90000;
	struct PAGE_ITEM*pml42=(struct PAGE_ITEM*)0x90800;
	struct PAGE_ITEM*pdpt=(struct PAGE_ITEM*)0x91000;
	struct PAGE_ITEM*pdt=(struct PAGE_ITEM*)0x92000;
	memset((void*)0x90000,0x00,0x3000);
	setPageItem(pml4,(u64)(u32)pdpt,PAGE_US|PAGE_RW|PAGE_AB);
	setPageItem(pml42,(u64)(u32)pdpt,PAGE_US|PAGE_RW|PAGE_AB);
	setPageItem(pdpt,(u64)(u32)pdt,PAGE_US|PAGE_RW|PAGE_AB);
	for(i=0;i<16;i++){
		pdt=(struct PAGE_ITEM*)0x92000+(i<<3);
		setPageItem(pdt,0x0000+(i<<21),PAGE_US|PAGE_RL|PAGE_RW|PAGE_AB);
	}
	return ;
}
// void buildTempPagesLong(void){
// 	static int i;
// 	u32*pml4=(struct PAGE_ITEM*)0x90000;
// 	u32*pml42=(struct PAGE_ITEM*)0x90800;
// 	u32*pdpt=(struct PAGE_ITEM*)0x91000;
// 	u32* pdt;
// 	*pml4=0x91007;
// 	*pml42=0x91007;
// 	*pdpt=0x92007;
// 	for(i=0;i<16;i++){
// 		pdt=(struct PAGE_ITEM*)0x92000+(i<<3);
// 		*pdt=(i<<21)|0x83;
// 	}
// }

#endif //_SYM_KERNEL_PAGING_INIT_H_