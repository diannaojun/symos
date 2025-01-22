#include <kernel/asm.h>
#include <kernel/init.h>
#include <kernel/struct.h>

int main (void) {
    init_gdt();
    init_idt();
    breakpoint();
    for(; ; );
    return 0;
}
