/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-04-29
 */
#ifndef _SYM_KERNEL_SCREEN_TEXT_H_
#define _SYM_KERNEL_SCREEN_TEXT_H_

#include <lib/lloader/asm.h>
#include <ia64/stddef.h>

#pragma pack(4)
struct INS_SCRN_TXT{
    u16 h,w;
    u16 cx,cy;
    u8 style;
    u8 opt:4,seting:1;
    void*vm;
};

static void ins_scrn_txt_mov_cur(struct INS_SCRN_TXT* ts) {
    static u16 cl;
    cl=ts->cy*80+ts->cx;
    _out8(0x03d4,0x0e);
    _out8(0x03d5,cl>>8);
    _out8(0x03d4,0x0f);
    _out8(0x03d5,cl);
    return ;
}
inline static char* ins_scrn_txt_get_chr_addr(struct INS_SCRN_TXT* ts,u16 x,u16 y) {
    x%=ts->w,y%=ts->h;
    return (char*)(ts->vm+((y*ts->w+x)<<1));
}
inline static u8* ins_scrn_txt_get_sty_addr(struct INS_SCRN_TXT* ts,u16 x,u16 y) {
    return (u8*)(ins_scrn_txt_get_chr_addr(ts,x,y)+1);
}
void ins_scrn_txt_swp(u8 id) {
    return ;
}
void ins_scrn_txt_clr(struct INS_SCRN_TXT* ts) {
    memset(ts->vm,0,(u32)(ts->h*ts->w)<<1);
    return ;
}
void ins_scrn_txt_scr(struct INS_SCRN_TXT* ts,u16 lines) {
    static u32 i,e,s,k;
    s=(u32)ts->w<<1,k=s*lines;
    e=(u32)ts->vm+(ts->h-1)*k;
    for(i=(u32)ts->vm; i<e; i+=s)
        memcpy((void*)i,(void*)i+k,s);
    memset((void*)e,0,k);
    return ;
}
void ins_scrn_txt_putc(struct INS_SCRN_TXT* ts,char c) {
    if(ts->seting) {
        switch(ts->opt) {
        case 0:
            switch(c){
            case 's':
                ts->opt=1;break;
            case '0':
                ts->seting=ts->opt=0;
                ts->style=0x0f;break;
            default:
                ts->seting=0;
            }break;
        case 1:ts->seting=0;
            ts->style=c;break;
        default:
            ts->seting=0;
        }
        return ;
    }
    switch(c) {
    case '\n':ts->cy++;break;
    case '\r':ts->cx=0;break;
    case '\t':ts->cx=((ts->cx>>2)+1)<<2;break;
    case '\e':ts->seting=1,ts->opt=0;break;
    default:
        *ins_scrn_txt_get_chr_addr(ts,ts->cx,ts->cy)=c;
        *ins_scrn_txt_get_sty_addr(ts,ts->cx,ts->cy)=ts->style;
        ts->cx++;break;
    }
    if(ts->cx>=ts->w) {
        ts->cx%=ts->w;
        ts->cy++;
    }
    if(ts->cy>=ts->h) {
        ins_scrn_txt_scr(ts,ts->cy-ts->h+1);
        ts->cy=ts->h-1;
    }
    ins_scrn_txt_mov_cur(ts);
    return ;
}
void ins_scrn_txt_puts(struct INS_SCRN_TXT* ts,const char* s) {
    while(*s)
        ins_scrn_txt_putc(ts,*(s++));
    return ;
}

#endif //_SYM_KERNEL_TEXT_SCREEN_H_
