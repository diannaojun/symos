/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-07-21
 */
#ifndef _SYM_KERNEL_FILESYS_H_
#define _SYM_KERNEL_FILESYS_H_

#define _SYM_FILESYS_FILEC_ROL 0x01
#define _SYM_FILESYS_FILEC_HID 0x02
#define _SYM_FILESYS_FILEC_SYS 0x04
#define _SYM_FILESYS_FILEC_DIR 0x10

static u8 bufr[512];

#pragma pack(1)
struct SMYFS{
  u16 jmpCode;
  char oemName[8];
  char label[8];
  u32 uuid;
  u16 resSec;
  u64 noS;
  u8 haveSys;
  u64 root_start;
};
#pragma pack(1)
struct SMYFS_FILE{
  char name[15];
  u8 level;
  u64 ptr;
  u64 length;
};

/* 抽象讀取塊緩存 */
struct FIO_BLK{
  u8 SIZE;      // 塊大小 2^size
  u64 LBA;      // 地址
  void* BP;     // 緩存指針
  void* INSP;   // 設備指針
};
/* 抽象目錄入口 */
struct PATH_ENTR{
  u8 SIZE;      // 塊大小 2^size
  u64 LBA;      // 地址
  void* INSP;   // 設備指針
};
  
#endif //_SYM_KERNEL_FILESYS_H_
