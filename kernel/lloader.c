/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-01
 */

#include <lib/lloader/main.h>

void show(u64 x, void* s){
    const char KKKSC03[]="0123456789ABCDEF";
    u64 i;
    for(i=0;i<16;++i, x<<=4){
        *(((char*)s)+(i+i))=KKKSC03[(u64)((x&0xf000000000000000ull)>>60)];
        *(((u8*)s)+(i+i+1))=0x0fu;
    }
}

int main (void){
    size_t itr;
    void *secbuf0 = (void*)0x0022000ull;
    void *secbuf1 = (void*)0x0022200ull;
    void *secbuf2 = (void*)0x0022400ull;
    ins_init();
    show((u64)(((struct INS_CONSOLE_OPT*)(ins[2].ins_operation))->clear),(void*)0xb8000ull);
    show((u64)ins_scrn_txt_clr,(void*)0xb80A0ull);
    show((u64)(((struct INS_SCRN_TXT *)ins[2].ins_data)->vm),(void*)0xb8140ull);
    show((u64)(&((struct INS_SCRN_TXT *)ins[2].ins_data)[0].h),(void*)0xb81E0ull);
    show((u64)(&(ins_scrn_txt[0].h)),(void*)0xb8280ull);

    show((u64)(((struct INS_CONSOLE_OPT *)ins[2].ins_operation)[0].clear),(void*)0xb82D0ull);
    show((u64)(&(ins_con_opt[0].clear)),(void*)0xb8320ull);
    show((u64)(ins_scrn_txt_clr),(void*)0xb8370ull);
    // ins_scrn_txt_clr(ins[2].ins_data);
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
