#ifndef __KERNEL_MEMORY_MM_H__
#define __KERNEL_MEMORY_MM_H__

#include <stddef.h>

#define MMBLK_ABSENT    0x0 /*內存頁面不存在（大頁面、原子項）*/
#define MMBLK_RESERVED  0x1 /*內存頁面保留（大頁面、原子項）*/
#define MMBLK_PRESENT   0x2 /*內存頁面空閒（大頁面、原子項）*/
#define MMBLK_FULL      0x3 /*內存頁面滿（非原子項）*/
#define MMBLK_USED0     0x4 /*內存頁面被0環佔用（大頁面、原子項）*/
#define MMBLK_USED1     0x5 /*內存頁面被1環佔用（大頁面、原子項）*/
#define MMBLK_USED2     0x6 /*內存頁面被2環佔用（大頁面、原子項）*/
#define MMBLK_USED3     0x7 /*內存頁面被3環佔用（大頁面、原子項）*/

typedef struct mmblk4k {
    // 4KB頁面項（原子項）
    unsigned status:3;  // 狀態
    unsigned _:9;       // 忽略
    uint64_t time:52;   // 分配時間戳
} __attribute__((packed)) mmblk4k_t;

typedef struct mmblk2m {
    unsigned status:3;  // 狀態
    uint16_t avalable:9;// 可用數量
    uint64_t addr:52;   // 下級頁表起始地址 / 分配時間戳（大頁面） 
} __attribute__((packed)) mmblk2m_t;

typedef struct mmblk1g {
    unsigned status:3;  // 狀態
    uint16_t avalable:9;// 可用數量
    uint64_t addr:52;   // 下級頁表起始地址 / 分配時間戳（大頁面）
} __attribute__((packed)) mmblk1g_t;

typedef struct mmblk512g {
    // 大頁面不可用
    unsigned status:3;  // 狀態
    uint16_t avalable:9;// 可用數量
    uint64_t addr:52;   // 下級頁表起始地址 / 分配時間戳（大頁面）
} __attribute__((packed)) mmblk512g_t;

typedef struct mmblk256t {
    // 大頁面不可用
    unsigned status:3;  // 狀態
    uint16_t avalable:9;// 可用數量
    uint64_t addr:52;   // 下級頁表起始地址 / 分配時間戳（大頁面）
} __attribute__((packed)) mmblk256t_t;

typedef struct mmblk128p {
    // 大頁面不可用
    unsigned status:3;  // 狀態
    uint16_t avalable:9;// 可用數量
    uint64_t addr:52;   // 下級頁表起始地址 / 分配時間戳（大頁面）
} __attribute__((packed)) mmblk128p_t;

typedef struct mmblk64e {
    // 大頁面不可用
    unsigned status:3;  // 狀態
    uint16_t avalable:9;// 可用數量
    uint64_t addr:52;   // 下級頁表起始地址 / 分配時間戳（大頁面）
} __attribute__((packed)) mmblk64e_t;

void init_mm(void);

#endif // __KERNEL_MEMORY_MM_H__
