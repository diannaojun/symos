/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-07
 */
#ifndef _SYM_KERNEL_PRINT_H_
#define _SYM_KERNEL_PRINT_H_

#include <ia64/stddef.h>
#include <lib/lloader/asm.h>
#include <lib/lloader/instrument.h>
#include <lib/lloader/screen_text.h>

static char str_buffer[128]="";
static struct Instrument *StdCon;
static struct Instrument *ErrCon;

#pragma pack(4)
struct INS_CONSOLE_OPT{
    void (*clear)(void*);
    void (*scroll)(void*,u16);
    void (*putstr)(void*,const char*);
    void (*putchar)(void*,char);
};

void printsi(const char*,struct Instrument*);
void printsl(const char*);
void printel(const char*,u16);

void ins_print_init(struct Instrument *Console, 
    struct INS_CONSOLE_OPT *tso,
    struct INS_SCRN_TXT *ts){
    static int i;

    ts->h = 25, ts->w = 80;
    ts->cx = ts->cy = 0;
    ts->vm = (void*)0xb8000;

    tso->clear=ins_scrn_txt_clr;
    tso->scroll=ins_scrn_txt_scr;
    tso->putstr=ins_scrn_txt_puts;
    tso->putchar=ins_scrn_txt_putc;

    Console->ins_class=0x0001;
    Console->ins_type=0x0001;
    Console->ins_data=ts;
    Console->ins_operation=tso;

    StdCon = Console;
    ErrCon = StdCon;
    printsl("\e0");
    return ;
}

void printsi(const char*s, struct Instrument*ins){
    ((struct INS_CONSOLE_OPT*)(ins->ins_operation))->putstr(ins->ins_data, s);
}
void printsl(const char*s){
    printsi(s, StdCon);
}
void printsni(const char*s, u64 n, struct Instrument*ins){
    static u64 i;
    for(i=0; i<n; ++i){
        ((struct INS_CONSOLE_OPT*)(ins->ins_operation))->putchar(ins->ins_data, s[i]);
    }
}
void printsnl(const char*s, u64 n){
    printsni(s, n, StdCon);
}
void printel(const char*description,u16 code){
    static u16 i;
    for(i=0;i<4;++i,code<<=4)
        str_buffer[i+1]=_CONST_NUM_TBL[(code&0xf000)>>12];
    str_buffer[0]='#',str_buffer[5]=0;
    printsi("\es\x07[\es\x0d",ErrCon);
    printsi(str_buffer,ErrCon);
    printsi("\es\x07]\es\x0c",ErrCon);
    printsi(description,ErrCon);
    printsi("\e0",ErrCon);
}
void printdi (u64 num,struct Instrument *ins){
    static u16 i;
    for(i=0;i<8;++i,num<<=4)
        str_buffer[i+2]=_CONST_NUM_TBL[(num&0xf000000000000000)>>60];
    for(i=0;i<8;++i,num<<=4)
        str_buffer[i+11]=_CONST_NUM_TBL[(num&0xf000000000000000)>>60];
    str_buffer[0]='0',str_buffer[1]='x',str_buffer[10]='_',str_buffer[19]=0;
    printsi(str_buffer,ins);
}
void printdl (u64 num){
    printdi(num,StdCon);
}

#endif //_SYM_KERNEL_PRINT_H_
