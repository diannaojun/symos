#include <kernel/init.h>

static void set_idt(idt_element_t *idt, void *func, uint8_t attr){
    idt->base_low = ((size_t)func) & 0x0000ffff;
    idt->base_mid = (((size_t)func) >> 16) & 0x0000ffff;
    idt->base_high = (((size_t)func) >> 32) & 0xffffffff;
    idt->selector = 0x18;
    idt->attr = attr;
    idt->ist = 0;
    return ;
}

void init_idt(void){
    xdt_header_t *idr_hdr = (xdt_header_t *)0x7ee0;
    idt_element_t *idt_item = (idt_element_t *)0x0000;
    idr_hdr->addr = (size_t)idt_item;
    idr_hdr->size = sizeof(idt_element_t) * 256;
    set_idt(idt_item + 0, devide_error, TRAP_GATE);
    set_idt(idt_item + 1, debug, TRAP_GATE);
    set_idt(idt_item + 2, nmi, INT_GATE);
    set_idt(idt_item + 3, break_point, SYS_GATE);
    set_idt(idt_item + 4, bounds, SYS_GATE);
    set_idt(idt_item + 5, over_flow, SYS_GATE);
    set_idt(idt_item + 6, invalid_opcode, TRAP_GATE);
    set_idt(idt_item + 7, device_not_available, TRAP_GATE);
    set_idt(idt_item + 8, double_fault, TRAP_GATE);
    set_idt(idt_item + 9, coprocessor_segment_overrun, TRAP_GATE);
    set_idt(idt_item + 10, invalid_tss, TRAP_GATE);
    set_idt(idt_item + 11, segment_not_available, TRAP_GATE);
    set_idt(idt_item + 12, stack_segment, TRAP_GATE);
    set_idt(idt_item + 13, general_protection, TRAP_GATE);
    set_idt(idt_item + 14, page_fault, TRAP_GATE);
    // set_idt(idt_item + 15, reserved, TRAP_GATE);
    set_idt(idt_item + 16, coprocessor_error, TRAP_GATE);
    set_idt(idt_item + 0x80, syscall, SYS_GATE);
    lidt(idr_hdr);
    return ;
}



/*
00000   IDT
01000   GDT
02000   PML5
03000   PML4
04000   PDPT
05000   PD
06000   PT
07000   STACK / MBR
08000   LODER
*/

void init_mm(void){
    static mmblk64e_t *m64e = (mmblk64e_t *)0x100000;
    m64e->addr = 0x0000000000000000;
    return ;
}