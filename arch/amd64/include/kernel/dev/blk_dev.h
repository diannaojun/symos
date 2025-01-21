#ifndef __KERNEL_BLK_DEV_H__
#define __KERNEL_BLK_DEV_H__

#include <stddef.h>

typedef struct request{
    ;
} request_t;

typedef struct blk_dev {
    void (*request_func)(void);
    request_t *request;
} blk_dev_t;

#endif // __KERNEL_BLK_DEV_H__
