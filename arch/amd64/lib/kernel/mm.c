#include <kernel/memory/mm.h>

void init_mm(void){
    mmblk64e_t *m64e = (mmblk64e_t *)0x7ed8;
    mmblk128p_t *m128p = (mmblk128p_t *)0x100000;
    mmblk256t_t *m256t = (mmblk256t_t *)0x101000;
    mmblk512g_t *m512g = (mmblk512g_t *)0x102000;
    mmblk1g_t *m1g = (mmblk1g_t *)0x103000;
    mmblk2m_t *m2m = (mmblk2m_t *)0x104000;
    int i;
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
    m1g->avalable = 1;
    for(i=0; i<8; ++i){
        m2m[i].addr = 0;
        m2m[i].status = MMBLK_RESERVED;
        m2m[i].avalable = 0;
    }
    return ;
}
