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
#include <lib/lloader/print.h>          // 屏幕輸出支持

static struct Instrument ins[16];
static struct INS_DISK_OPT ins_disk_ata_opt[4];
static struct INS_DISK_ATA_DAT ins_disk_ata_dat[2];
static struct INS_CONSOLE_OPT ins_console_opt;
static struct INS_SCRN_TXT ins_scrn_txt;

void ins_init(void){
    /*/ 0x1f0 0x170 ATA磁盘设备初始化
    ins_disk_ata_opt[2].read=ins_disk_ata_read48;
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
    ins_disk_ata_init(ins_disk_ata_dat+0);
    ins_disk_ata_init(ins_disk_ata_dat+1);*/
    // 顯示器初始化
    ins_print_init(ins+2, &ins_console_opt, &ins_scrn_txt);
    return ;
}

#endif //_SYM_KERNEL_MAIN_H_
