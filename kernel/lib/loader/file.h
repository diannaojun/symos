/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-07-28
 */
#ifndef _SYM_KERNEL_FILE_H_
#define _SYM_KERNEL_FILE_H_

#include <lib/loader/disks.h>
#include <lib/filesys.h>
#include <ia32/stddef.h>

#define insp    struct Instrument *dp
#define fsp     struct SMYFS *sp

u64 SMYFS_INS_GET_FAT(insp, fsp, u64 ip, void* buf){
    static struct FIO_BLK blk;
    printsl("GET FAT "),printdl(ip),printsl(" -> ");
    blk.SIZE = 9;
    blk.LBA = sp->resSec+(ip>>6);
    blk.BP = buf;
    (((struct DiskOpt*) (dp->operation))->readSec)
        (dp->object, buf, blk.LBA, 1);
    ip &= (1<<9)-1;
    ip=((u64*)blk.BP)[ip];
    printdl(ip),printsl("\n\r");
    return ip;
}

void SMYFS_INS_LOAD(insp, fsp, u64 ip, void* buf){
    while(ip<0xfffffffffffffff0){
        (((struct DiskOpt*) (dp->operation))->readSec)
            (dp->object, buf, ip, 1);
        buf += 512;
        ip = SMYFS_INS_GET_FAT(dp, sp, ip, buf);
    }
}

#undef insp
#undef fsp

#endif
