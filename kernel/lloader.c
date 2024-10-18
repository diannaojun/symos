/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-01
 */
void putllx();

#include <lib/lloader/main.h>
void putllx(int pos, u64 v){
    static const char tbl[]="0123456789ABCDEF";
    static int i;
    for(i=0;i<16;++i,v>>=4){
        *(char*)(0xb801eull+(pos<<6)-(i<<1))=tbl[v&0x0f];
        *(char*)(0xb801full+(pos<<6)-(i<<1))=0x0f;
        *(char*)(0xb803eull+(pos<<6)-(i<<1))=' ';
        *(char*)(0xb803full+(pos<<6))=0x0f;
    }
}

int main (void){
    k_build_page();
    _fin();
    return 0;
}
