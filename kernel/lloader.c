/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-01
 */

#include <lib/lloader/main.h>

void show(u64 x, void* s){
    static char _t[]="0123456789ABCDEF",i;
    for(i=0;i<16;++i,x>>=4){
        *((char*)(s+(i<<1)))=_t[x&15];
        *((char*)(s+(i<<1)+1))=0x0f;
    }
}

int main (void){
    size_t itr;
    void *secbuf0 = (void*)0x0202000ull;
    void *secbuf1 = (void*)0x0202200ull;
    void *secbuf2 = (void*)0x0202400ull;
    ins_init();
    show((u64)(((struct INS_CONSOLE_OPT*)(ins[2].ins_operation))->clear),0xb8000);
    show(ins_scrn_txt_clr,0xb8040);
    // (*(((struct INS_CONSOLE_OPT*)(ins[2].ins_operation))->clear))(ins[2].ins_data);
    // (((struct INS_DISK_OPT*)(ins[0].ins_operation))->read)(ins[0].ins_data, secbuf0, 0, 1);
    // SMYFS_INS_LOAD(&ins[0], secbuf0, ((struct SMYFS*)secbuf0)->root_start, secbuf2);
    // if(TRUE){
    //     printsl("SYMBOL OPERATING SYSTEM LONG-MODE LOADER\n\r");
    //     printsl("SCAN \'/\' :\n\r");
    //     for(itr=0; ; ++itr){
    //         if(((struct SMYFS_FILE*)secbuf2)[itr].name[0]==0)
    //             break;
    //         printsnl(((struct SMYFS_FILE*)secbuf2)[itr].name, 15);
    //         printsl(" | ");
    //         printdl(((struct SMYFS_FILE*)secbuf2)[itr].length);
    //         printsl("Bytes\n\r");
    //     }
    // }
    _fin();
    return 0;
}
