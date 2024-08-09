/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-01
 */

#include <lib/lloader/main.h>
int main (void){
    size_t itr;
    void *secbuf0 = (void*)0x0202000ull;
    void *secbuf1 = (void*)0x0202200ull;
    void *secbuf2 = (void*)0x0202400ull;
    ins_init();
    *((char*)0xb8000)='0'+((u64)(((struct INS_CONSOLE_OPT*)(ins[2].ins_operation))->clear))&7;
    *((char*)0xb8001)=0x0f;
    *((char*)0xb8002)='0'+((u64)(ins_scrn_txt_clr))&7;
    *((char*)0xb8003)=0x0f;
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
