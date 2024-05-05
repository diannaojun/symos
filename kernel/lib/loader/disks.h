/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-05-02
 */
#ifndef _SYM_KERNEL_DISKS_H_
#define _SYM_KERNEL_DISKS_H_

#include <IA32/stddef.h>
#include <lib/loader/instrument.h>

struct ATA_DISK{
	u16 port;
	u8 PS:1,IN:1;
};
void ATA_DISKset(struct ATA_DISK*dp,u64 lba,u16 cnt){
	while(_in8(dp->port+0x7)&(1<<7))_nop();
	_out8(dp->port+0x6,0xE0|(dp->PS<<4));
	_out8(dp->port+0x1,0);
	_out8(dp->port+0x2,(cnt>>8)&0xff);
	_out8(dp->port+0x3,(lba>>24)&0xff);
	_out8(dp->port+0x4,(lba>>32)&0xff);
	_out8(dp->port+0x5,(lba>>40)&0xff);
	_out8(dp->port+0x1,0);
	_out8(dp->port+0x2,cnt&0xff);
	_out8(dp->port+0x3,lba&0xff);
	_out8(dp->port+0x4,(lba>>8)&0xff);
	_out8(dp->port+0x5,(lba>>16)&0xff);
}
void ATA_DISKreadsec(struct ATA_DISK*dp,void*buf,u64 lba,u16 cnt){
	static u32 adr,siz;
	if(!dp->IN)return;
	ATA_DISKset(dp,lba,cnt);
	_out8(dp->port+0x7,0x24);
	while(!(_in8(dp->port+0x7)&(1<<6)))_nop();
	for(adr=0,siz=cnt<<8;adr<siz;adr++){
		((u16*)buf)[adr]=_in16(dp->port);
	}
}
void ATA_DISKwritesec(struct ATA_DISK*dp,void*buf,u64 lba,u16 cnt){
	static u32 adr,siz;
	if(!dp->IN)return;
	ATA_DISKset(dp,lba,cnt);
	_out8(dp->port+0x7,0x34);
	while(!(_in8(dp->port+0x7)&(1<<6)))_nop();
	for(adr=0,siz=cnt<<8;adr<siz;adr++){
		_out16(dp->port,((u16*)buf)[adr]);
	}
}

#pragma pack(4)
struct DiskOpt{
	void (*readSec)(void*,void*,u64,u16);
	void (*writeSec)(void*,void*,u64,u16);
};
typedef void (*_SEC_IO_T)(void*,void*,u64,u16);

struct Instrument ATA[4];
static struct ATA_DISK ATA_rel[4];
static struct DiskOpt ATAOpt;

void initDisk(void){
	static u8 i;
	ATAOpt.readSec=(_SEC_IO_T)ATA_DISKreadsec;
	ATAOpt.writeSec=(_SEC_IO_T)ATA_DISKwritesec;
	ATA_rel[0].port=ATA_rel[1].port=0x1f0;
	ATA_rel[2].port=ATA_rel[3].port=0x170;
	ATA_rel[0].PS=ATA_rel[2].PS=0;
	ATA_rel[1].PS=ATA_rel[3].PS=1;
	for(i=0;i<4;i++){
		ATA_rel[i].IN=1;
		ATA[i].it=HD;
		ATA[i].it2=0x01;
		ATA[i].object=ATA_rel+i;
		ATA[i].operation=&ATAOpt;
	}
}
#endif