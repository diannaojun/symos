#include <kernel/asm.h>

/*
void putck(char ch);
void putsk(const char *str);
int main(void);

int main(void) {
    putsk((char *)0x980c7);
    breakpoint();
    putsk("FROM C: Loading Kernel64...\n\r");
    breakpoint();
    for (;;)
        ;
    return 0;
}

void putck(char ch) {
    ch = toascii(ch);
    switch (ch) {
    case '\t':
        *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
        break;
    case '\n':
        *((short *)0x7e02) += 160;
        break;
    case '\r':
        *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
        break;
    default:
        *(short *)(size_t)(0xb8000 | *((short *)0x7e02)) = ch | 0x0f00;
        *((short *)0x7e02) += 2;
    }
    return;
}

void putsk(const char *str) {
    static size_t i;
    for (i = 0; str[i]; ++i)
        putck(str[i]);
    return;
}
*/

int main (void){
    breakpoint();
    init_gdt();
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
