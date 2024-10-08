/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-07
 */
#ifndef _SYM_KERNEL_FILE_H_
#define _SYM_KERNEL_FILE_H_

#include <lib/lloader/disk.h>
#include <lib/filesys.h>
#include <ia64/stddef.h>

#define insp    struct Instrument *dp
#define fsp     struct SMYFS *sp

u64 SMYFS_INS_GET_FAT(insp, fsp, u64 ip, void *buf) {
	static struct FIO_BLK blk;
	blk.SIZE = 9;
	blk.LBA = sp->resSec + (ip >> 6);
	blk.BP = buf;
	(((struct INS_DISK_OPT *) (dp->ins_operation))->read)
	(dp->ins_data, buf, blk.LBA, 1);
	ip &= (1 << 9) - 1;
	return ((u64 *)blk.BP)[ip];
}

void SMYFS_INS_LOAD(insp, fsp, u64 ip, void *buf) {
	while (ip < 0xfffffffffffffff0) {
		(((struct INS_DISK_OPT *) (dp->ins_operation))->read)
		(dp->ins_data, buf, ip, 1);
		buf += 512;
		ip = SMYFS_INS_GET_FAT(dp, sp, ip, buf);
	}
}

#undef insp
#undef fsp

#endif
