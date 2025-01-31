#include <kernel/init.h>

int main (void){
    boot_info_t *boot_info = (boot_info_t *)0x7e00;
    if(boot_info->loaded_mem == 0x88)
        *(char*)0xb8000 = '8';
    else if(boot_info->loaded_mem == 1)
        *(char*)0xb8000 = '1';
    else if(boot_info->loaded_mem == 20)
        *(char*)0xb8000 = '2';
    else if(boot_info->loaded_mem == 24)
        *(char*)0xb8000 = 'X';
    else
        *(char*)0xb8000 = '?';
    init_idt();
    init_mm();
    for(;;);
    return 0;
}
