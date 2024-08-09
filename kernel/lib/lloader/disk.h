/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-05
 */
#ifndef _SYM_KERNEL_DISK_H_
#define _SYM_KERNEL_DISK_H_

#include <ia64/stddef.h>
#include <lib/lloader/asm.h>

#define ATA_DATA_REG(port)          (0x00+(port))
#define ATA_ERROR_REG(port)         (0x01+(port))
#define ATA_FEATURES_REG(port)      (0x01+(port))
#define ATA_SECTOR_COUNT_REG(port)  (0x02+(port))
#define ATA_SECTOR_NUM_REG(port)    (0x03+(port))
#define ATA_CYL_LOW_REG(port)       (0x04+(port))
#define ATA_CYL_HIGH_REG(port)      (0x05+(port))
#define ATA_DRV_HEAD_REG(port)      (0x06+(port))
#define ATA_COMMAND_REG(port)       (0x07+(port))
#define ATA_STATUS_REG(port)        (0x07+(port))

struct INS_DISK_ATA_DAT{
    // ATA 硬盘结构
	u16 port;   // ATA 硬盘 I/O 端口
};

struct INS_DISK_OPT{
    // ATA 硬盘方法结构
	void (*read)(void*,void*,u64,u64);  // 读磁盘 $1 (INS_DISK_ATA_DAT) 从 $3 扇区开始长 $4 扇区的数据到 $2 地址
	void (*write)(void*,void*,u64,u64); // 写磁盘 $1 (INS_DISK_ATA_DAT) 从 $2 地址的数据到 $3 扇区开始长 $4 扇区
};

void ins_disk_ata_wait (struct INS_DISK_ATA_DAT *dp){
    // 等待磁盘 $1 (INS_DISK_ATA_DAT) 空闲
	while((_in8(ATA_STATUS_REG(dp->port))&0x88)!=0x08);
}

void ins_disk_ata_read48(struct INS_DISK_ATA_DAT *dp, void *buf, u64 lba, u64 cnt){
    // 读磁盘 $1 (INS_DISK_ATA_DAT) 从 $3 扇区开始长 $4 扇区的数据到 $2 地址
    static u16 i;
    _out8(ATA_DRV_HEAD_REG(dp->port), 0x40);
    _out8(ATA_FEATURES_REG(dp->port), 0x00);
    _out8(ATA_SECTOR_COUNT_REG(dp->port), cnt>>8);
    _out8(ATA_SECTOR_NUM_REG(dp->port), lba>>24);
    _out8(ATA_CYL_LOW_REG(dp->port), lba>>32);
    _out8(ATA_CYL_HIGH_REG(dp->port), lba>>40);
    _out8(ATA_FEATURES_REG(dp->port), 0x00);
    _out8(ATA_SECTOR_COUNT_REG(dp->port), cnt);
    _out8(ATA_SECTOR_NUM_REG(dp->port), lba);
    _out8(ATA_CYL_LOW_REG(dp->port), lba>>8);
    _out8(ATA_CYL_HIGH_REG(dp->port), lba>>16);
    _out8(ATA_COMMAND_REG(dp->port), 0x24);
    while(cnt--){
        ins_disk_ata_wait(dp);
        for(i=0; i<256; ++i)
            ((u16*)buf)[i]=_in16(ATA_DATA_REG(dp->port));
    }
}

void ins_disk_ata_init (struct INS_DISK_ATA_DAT *dp){
    // 初始化磁盘 $1 (INS_DISK_ATA_DAT)
    static u16 i;
    _out8(ATA_DRV_HEAD_REG(dp->port), 0x0a|(1<<4));
    _out8(ATA_COMMAND_REG(dp->port), 0xec);
    for(i=0; i<256;++i)
        _in16(ATA_DATA_REG(dp->port));
}

#endif //_SYM_KERNEL_INSTRUMENT_H_
