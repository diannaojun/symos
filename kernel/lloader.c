/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-01
 */
#include <lib/lloader/main.h>
void putd(u64 x, void* s){
    const char BASE[]="0123456789ABCDEF";
    u64 i;
    for(i=0;i<16;++i, x<<=4){
        *(((char*)s)+(i+i))=BASE[(u64)((x&0xf000000000000000ull)>>60)];
        *(((char*)s)+(i+i+1))=0x0f;
    }
}
void putdi(i64 x, void* s){
    if(x<0){
        *(((char*)s++))='-';
        *(((char*)s++))=0x0f;
        x=-x;
    }
    putd(x,s);
}
void puts(const char* x, void* s){
    size_t k;
    for(k=0;x[k];++k){
        *((char*)(s+(k<<1)))=x[k];
        *((char*)(s+(k<<1)+1))=0x0f;
    }
}
void clear(void* s,int size){
    memset(s,0,size);
}
struct opt{
    void (*puts) (const char*,void*);
};
//50 80
static struct opt to[1];
static struct Instrument ins[2];

int main (void){
    clear(0xb8000,25*80*2);
    puts("LOADER64 TEST",0xb8000);
    putd((u64)ins,0xb8000+2*80*1);
    putd((u64)&ins[0],0xb8000+2*80*1+2*32);
    ins[0].ins_data=&ins[1];
    putd((u64)(ins->ins_data),0xb8000+2*80*2);
    putd((u64)(ins[0].ins_data),0xb8000+2*80*2+2*32);
    ins->ins_operation=to;
    putd((u64)(ins->ins_operation),0xb8000+3*80*2);
    putd((u64)(ins[0].ins_operation),0xb8000+3*80*2+2*32);
    to->puts=&puts;
    putd((u64)(((struct opt*)ins->ins_operation)->puts),0xb8000+4*80*2);
    putd((u64)(((struct opt*)ins[0].ins_operation)->puts),0xb8000+4*80*2+2*32);
    (*to->puts)("ALRIGHT",0xb8000+2*80*5);
    _fin();
    return 0;
}
