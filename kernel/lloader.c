/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-01
 */

#include <lib/lloader/main.h>

void testfunc(){
    *(char*)(0xb8000)='K';
    *(char*)(0xb8001)=0x0f;
}

int main (void){
    //ins_init();
    testfunc();
    _fin();
    return 0;
}
