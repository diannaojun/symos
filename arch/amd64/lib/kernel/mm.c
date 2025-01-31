#include <kernel/memory/mm.h>
#include <kernel/init.h>

void init_mm(void){
    mmblk64e_t *m64e = (mmblk64e_t *)0x7ed8;
    mmblk128p_t *m128p = (mmblk128p_t *)0x106000;
    mmblk256t_t *m256t = (mmblk256t_t *)0x107000;
    mmblk512g_t *m512g = (mmblk512g_t *)0x108000;
    mmblk1g_t *m1g = (mmblk1g_t *)0x109000;
    mmblk2m_t *m2m = (mmblk2m_t *)0x10a000;
    boot_info_t *bootinfo = (boot_info_t *)0x7e00;
    uint16_t i;
    m64e->addr = (uint64_t)m128p >> 12;
    m64e->status = MMBLK_PRESENT;
    m64e->avalable = 1;
    m128p->addr = (uint64_t)m256t >> 12;
    m128p->status = MMBLK_PRESENT;
    m128p->avalable = 1;
    m256t->addr = (uint64_t)m512g >> 12;
    m256t->status = MMBLK_PRESENT;
    m256t->avalable = 1;
    m512g->addr = (uint64_t)m1g >> 12;
    m512g->status = MMBLK_PRESENT;
    m512g->avalable = 1;
    m1g->addr = (uint64_t)m2m >> 12;
    m1g->status = MMBLK_PRESENT;
    m1g->avalable = (bootinfo->loaded_mem + 2047) >> 11;
    for(i=0; i<8; ++i){
        m2m[i].addr = 0;
        m2m[i].status = MMBLK_RESERVED;
        m2m[i].avalable = 0;
    }
    for(; i < m1g->avalable; ++i){
        m2m[i].addr = 0;
        m2m[i].status = MMBLK_PRESENT;
        m2m[i].avalable = 0x200;
    }
    m2m[i - 1].avalable = (bootinfo->loaded_mem & 0x7ff) >> 2;
    return ;
}

void *request_page(void){
    mmblk64e_t *m64e = (mmblk64e_t *)0x7ed8;
    mmblk128p_t *m128p;
    mmblk256t_t *m256t;
    mmblk512g_t *m512g;
    mmblk1g_t *m1g;
    mmblk2m_t *m2m;
    mmblk4k_t *m4k;
    uint16_t p0, p1, p2, p3, p4;
    uint64_t ptr;
    if(m64e->status != MMBLK_PRESENT)
        return NULL;
    m128p = (mmblk128p_t *)((uint64_t)m64e->addr << 12);
    p1 = 0;
    for(p0 = 0; p0 < 0x200; ++p0){
        if(m128p[p0].status == MMBLK_PRESENT){
            if(m128p[p0].addr){
                p1 = p0;
                goto findp1;
            } else if(m128p[p0].avalable != 0x200){
                p1 = p0;
                goto newp1;
            } else if(!p1)
                p1 = p0;
        }
    }
    if(!p1)
        return NULL;
    newp1:
        ptr = p1;
        m256t = (mmblk256t_t *)(ptr <<= 9 * 5 + 12);
        m128p[p1].addr = ptr >> 12;
        for(p0 = 0; p0 < m128p[p0].avalable; ++p0){
            m256t[p0].addr = 0;
            m256t[p0].avalable = 0x200;
            m256t[p0].status = MMBLK_PRESENT;
        }
        m256t->addr = (ptr >> 12) + 1;
        for(p0 = 0; p0 < m128p[p0].avalable; ++p0)
    findp1:
        ;
}
