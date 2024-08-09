/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-05-02
 */
#ifndef _SYM_KERNEL_DISKS_H_
#define _SYM_KERNEL_DISKS_H_

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

#include <ia32/stddef.h>
#include <lib/loader/instrument.h>

#pragma pack(4)
struct ATA_DISK{
    u16 port;
    u8 PS:1,IN:1;
};

#pragma pack(1)
struct DiskInfo{
    u16 secSiz;
    u64 secCnt;
};

#pragma pack(4)
struct DiskOpt{
    void (*readSec)(void*,void*,u64,u16);
    void (*writeSec)(void*,void*,u64,u16);
};

typedef void (*_SEC_IO_T)(void*,void*,u64,u16);

void ATA_WAIT(struct ATA_DISK *dp){
    while(_in8(ATA_STATUS_REG(dp->port))&0x80);
}

void ATA_WAIT2(struct ATA_DISK *dp){
    while(!(_in8(ATA_STATUS_REG(dp->port))&0x80) || (_in8(ATA_STATUS_REG(dp->port))&0x01));
    //!(inb(ATA_PORT_STATUS(base_port)) & 0x80) || inb(ATA_PORT_STATUS(base_port)) & 0x01
}

void ATA_READ_48(struct ATA_DISK *dp, void *buf, u64 lba, u8 cnt){
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
        while((_in8(ATA_STATUS_REG(dp->port))&0x88)!=0x08);
        for(i=0; i<256; ++i)
            ((u16*)buf)[i]=_in16(ATA_DATA_REG(dp->port));
    }
}

void ATA_INIT (struct ATA_DISK *dp){
    static int i;
    _out8(ATA_DRV_HEAD_REG(dp->port), 0x0a|(1<<4));
    _out8(ATA_COMMAND_REG(dp->port), 0xec);
    for(i=0; i<256;++i)
      _in16(ATA_DATA_REG(dp->port));
}

struct Instrument ATA[4];
static struct ATA_DISK ATA_rel[4];
static struct DiskOpt ATAOpt;

void DISK_INIT(){
    static int i;
    ATAOpt.readSec = (void*)ATA_READ_48;
    for(i=0;i<4;++i){
        ATA[i].it=HD,ATA[i].it2=0;
        ATA[i].object=ATA_rel+i;
        ATA[i].operation=&ATAOpt;
        ATA_rel[i].port=0x1f0-0x40*(i&2);
        ATA_rel[i].PS=(i&1);
    }
    ATA_INIT(ATA_rel);
}
#endif
