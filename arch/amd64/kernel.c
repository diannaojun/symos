#include <kernel/init.h>

int main (void){
    breakpoint();
    init_idt();
    breakpoint();
    // init_pic();
    // breakpoint();
    // init_timer();
    // breakpoint();
    // init_keyboard();
    // breakpoint();
    // init_mm();
    // breakpoint();
    // init_pmm();
    // breakpoint();
    // init_vmm();
    // breakpoint();
    // init_heap();
    // breakpoint();
    // init_tss();
    // breakpoint();
    // init_console();
    // breakpoint();
    // init_shell();
    // breakpoint();
    // init_fs();
    // breakpoint();
    // init_proc();
    // breakpoint();
    // init_irq();
    // breakpoint();
    // init_syscall();
    // breakpoint();
    // init_bootinfo();
    // breakpoint();
    for(;;);
    return 0;
}
