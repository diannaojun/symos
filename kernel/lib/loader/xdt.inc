; Symbol DT
; SymOS
; DiannaoJun
; 2024-05-01

%macro SEG_NULL 0
    dw 0, 0
    db 0, 0, 0, 0
%endmacro
%macro SEG 4    ; SEG(type,base,lim,prio)
    dw (((%3) >> 12) & 0xffff), ((%2) & 0xffff)
    db (((%2) >> 16) & 0xff),(0x90 | (%1)),((%4) | (((%3) >> 28) & 0xf)),(((%2) >> 24) & 0xff)
%endmacro
; 程序段类型
%define STA_X       0x8     ; 可执行段
%define STA_E       0x4     ; 向下展开(不可执行的段)
%define STA_C       0x4     ; 符合要求的代码段(仅可执行)
%define STA_W       0x2     ; 可写(不可执行段)
%define STA_R       0x2     ; 可读(可执行段)
%define STA_A       0x1     ; 已访问
; 系统段类型
%define STS_T16A    0x1     ; 可用的16位TSS
%define STS_LDT     0x2     ; 本地描述符表LDT
%define STS_T16B    0x3     ; 繁忙的16位TSS
%define STS_CG16    0x4     ; 16位呼叫门
%define STS_TG      0x5     ; 任务门/Coum传输
%define STS_IG16    0x6     ; 16位中断门
%define STS_TG16    0x7     ; 16位陷阱门
%define STS_T32A    0x9     ; 可用的32位TSS
%define STS_T32B    0xB     ; 繁忙的32位TSS
%define STS_CG32    0xC     ; 32位调用门
%define STS_IG32    0xE     ; 32位中断门
%define STS_TG32    0xF     ; 32位陷阱门
; 类型
%define GDT32       0xC0    ; 默认格式32位
%define GDT64       0x20    ; 默认格式64位