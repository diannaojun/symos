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
    // SFS 分区头基本结构
    u16 jmpCode;            // 跳转指令，保留位
    char oemName[8];        // 生产厂商
    char label[8];          // 分区名称简写
    u32 uuid;               // 磁盘标识符
    u16 resSec;             // 保留扇区个数
    u64 noS;                // 分区大小（扇区）
    u8 Type;                // 分区类型
    u64 root_start;         // 数据开始地址（强制将此扇区作为根目录的第一个扇区）
};
#pragma pack(1)
struct SMYFS_FILE{
    // SFS 分区文件项结构
    char name[15];          // 文件名
    u8 level;               // 文件标志
    u64 ptr;                // 文件头地址
    u64 length;             // 文件长度
};
struct FIO_BLK{
    // 抽象讀取塊緩存
    u8 SIZE;                // 塊大小 2 ^ size
    u64 LBA;                // 地址
    void* BP;               // 緩存指針
    void* INSP;             // 設備指針
};
struct PATH_ENTR{
    // 抽象目錄入口
    u8 SIZE;                // 塊大小 2 ^ size
    u64 LBA;                // 地址
    void* INSP;             // 設備指針
};
    
#endif //_SYM_KERNEL_FILESYS_H_
