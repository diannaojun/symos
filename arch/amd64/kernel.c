#include <stddef.h>
#include <kernel/asm.h>

int main (void) {
    breakpoint();
    putsk("Loading kernel64...\n\r");
    breakpoint();
    for(; ; )
        breakpoint();
    return 0;
}

void putck(char ch){
    switch(ch){
        case '\t':
            *(short *)(0x7e02) = (7 + *(short *)(0x7e02)) >> 3 << 3;
            break;
        case '\n':
            *(short *)(0x7e02) += 160;
            break;
        case '\r':
            *(short *)(0x7e02) = (*(short *)(0x7e02)) / 160 * 160;
            break;
        default:
            *(char *)(0xb8000 | (*(short *)(0x7e02))++) = ch;
            *(char *)(0xb8000 | (*(short *)(0x7e02))++) = 0x0f;
    }
    return ;
}

void putsk(const char* str){
    static size_t i;
    for(i=0; str[i]; ++i)
        putck(str[i]);
    return ;
}