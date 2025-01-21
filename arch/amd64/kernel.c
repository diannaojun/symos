#include <kernel/asm.h>
#include <kernel/init.h>

int main (void) {
    virtual_node_t *root;
    puts_init("Loading kernel64...\n\r");
    root = root_init();
    breakpoint();
    for(; ; );
    return 0;
}
