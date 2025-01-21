%define ADDR_SEG_MBR_PROG 0x07c0
%define ADDR_SEG_SET_PROG 0x0800
%define ADDR_SEG_SYS_PROG 0x80000000

%macro gdt_segment 4
    ; gdt_segment (base, limit, attribute, type)
    dw %2 & 0xffff
    dw %1 & 0xffff
    db (%1 >> 16) & 0xff
    db %3 & 0xff
    db (%4 & 0xf0) | ((%2 >> 14) & 0x0f)
    db (%1 >> 24) & 0xff
%endmacro
%macro gdt_null 0
    gdt_segment 0, 0, 0, 0
%endmacro

; program segment
%define sta_prog            0x10    ; 程序段
%define sta_prog_d          0x00    ; 数据段
%define sta_prog_x          0x08    ; 代码段
%define sta_prog_cd         0x04    ; 符合要求的 (代码段)
                                    ; 向下展开, 栈 (数据段)
%define sta_prog_xwr        0x02    ; 可读 (代码段)
                                    ; 可写 (数据段)
%define sta_prog_dt         0x01    ; 已访问 (脏)
; program segment
%define sta_sys_tss16       0x01     ; 可用的16位TSS
%define sta_sys_ldt         0x02     ; 本地描述符表LDT
%define sta_sys_tss16_buzy  0x03     ; 繁忙的16位TSS
%define sta_sys_callgate16  0x04     ; 16位呼叫门
%define sta_sys_taskgate    0x05     ; 任务门/Coum传输
%define sta_sys_intgate16   0x06     ; 16位中断门
%define sta_sys_trapgate16  0x07     ; 16位陷阱门
%define sta_sys_tss32       0x09     ; 可用的32位TSS
%define sta_sys_tss32_buzy  0x0b     ; 繁忙的32位TSS
%define sta_sys_callgate32  0x0c     ; 32位调用门
%define sta_sys_intgate32   0x0e     ; 32位中断门
%define sta_sys_trapgate32  0x0f     ; 32位陷阱门
; other attribute
%define sta_level0          0x00
%define sta_level1          0x20
%define sta_level2          0x40
%define sta_level3          0x60
%define sta_present         0x80
%define sta_non_present     0x00
; other type
%define stt_32def           0x40
%define stt_32c16           0x00
%define stt_64def           0x20
%define stt_avl             0x10
%define stt_limitalign4kb   0x80

; MBR struction
%macro mbr_null 0
    db 0x00, 0x00
    dw 0x02
    db 0x5b, 0xff
    dw 0xffff
    dd 0x00000001
    dd 0xffffffff
%endmacro

%define pag_present         0x001
%define pag_non_present     0x000
%define pag_writable        0x002
%define pag_usermode        0x004
%define pag_caching         0x008
%define pag_discachable     0x010
%define pag_accessed        0x020
%define pag_dirty           0x040
%define pag_huge            0x080
%define pag_global          0x100
%define pag_level           0x0400
%define pag_noexecute       0x8000

%macro paging 3
    ; page (base, attribute, prot)
    db %2 & 0xff
    db ((%2 >> 8) & 0x0f) | ((%1 >> 8) & 0xf0)
    dd (%1 >> 16) & 0xffffffff
    dw ((%1 >> 48) & 0x0f) | (%3)
%endmacro
