#include <kernel/init.h>

int main (void){
    init_idt();
    init_mm();
    for(;;);
    return 0;
}
