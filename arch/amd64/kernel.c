#include <kernel/init.h>

int main (void){
    init_idt();
    asm volatile ("int $3");
    init_mm();
    for(;;);
    return 0;
}
