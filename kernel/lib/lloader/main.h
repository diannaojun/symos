/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-05
 */
#ifndef _SYM_KERNEL_MAIN_H_
#define _SYM_KERNEL_MAIN_H_

#include <ia64/stddef.h>                // 64 位类型定义
#include <lib/lloader/asm.h>            // 汇编函数声明

#include <lib/lloader/instrument.h>     // 設備支持
#include <lib/lloader/file.h>           // 文件支持
#include <lib/lloader/disk.h>           // 硬盤支持
#include <lib/filesys.h>                // SFS文件系統支持
#include <lib/lloader/print.h>

struct Instrument ins[16];
struct INS_DISK_OPT ins_disk_ata_opt[4];
struct INS_DISK_ATA_DAT ins_disk_ata_dat[2];
struct INS_CONSOLE_OPT ins_con_opt[1];
struct INS_SCRN_TXT ins_scrn_txt[1];

void ins_init(void){
    // 0x1f0 0x170 ATA磁盘设备初始化
    ins_disk_ata_opt[2].read=(void*)ins_disk_ata_read48;
    ins_disk_ata_opt[2].write=NULL;
    ins_disk_ata_dat[0].port=0x01f0;
    ins_disk_ata_dat[1].port=0x0170;
	ins[0].ins_operation=&ins_disk_ata_opt[2];
	ins[1].ins_operation=&ins_disk_ata_opt[2];
    ins[0].ins_data=&ins_disk_ata_dat[0];
    ins[1].ins_data=&ins_disk_ata_dat[1];
    ins[0].ins_class=ins[1].ins_class=0x0002;
    ins[0].ins_type=ins[1].ins_type=0x0001;
    ins[0].ins_uuid=0,ins[1].ins_uuid=1;
    ins_disk_ata_init(&ins_disk_ata_dat[0]);
    // 文本荧幕设备初始化
    ins_con_opt.clear=(void*)ins_scrn_txt_clr;
    ins_con_opt.scroll=(void*)ins_scrn_txt_scr;
    ins_con_opt.putstr=(void*)ins_scrn_txt_puts;
    ins_con_opt.putchar=(void*)ins_scrn_txt_putc;
    ins_scrn_txt.h = 25;
    ins_scrn_txt.w = 80;
    ins_scrn_txt.cx = 0;
    ins_scrn_txt.cy = 0;
    ins_scrn_txt.vm = (void*)0xb8000;
    ins[2].ins_class=0x0001;
    ins[2].ins_type=0x0001;
    ins[2].ins_data=(void*)&ins_scrn_txt[0];
    ins[2].ins_operation=(void*)&ins_con_opt[0];
    ins_print_init(&ins[2]);
}

#endif //_SYM_KERNEL_MAIN_H_
