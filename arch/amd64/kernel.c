#include <ctype.h>
#include <kernel/asm.h>

void putck(char ch);
void putsk(const char* str);
int main (void);

int main (void) {
    putsk((char *)0x980c7);
    breakpoint();
    for(; ; );
    return 0;
}

void putck(char ch){
    ch = toascii(ch);
    switch(ch){
        case '\t':
            *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
            break;
        case '\n':
            *((short *)0x7e02) += 160;
            break;
        case '\r':
            *((short *)0x7e02) = (*((short *)0x7e02) + 7) & 0xfff8;
            break;
        default:
            *(short*)(size_t)(0xb8000 | *((short *)0x7e02)) = ch | 0x0f00;
            *((short *)0x7e02) += 2;
    }
    return ;
}

void putsk(const char* str){
    static size_t i;
    for(i=0; str[i]; ++i)
        putck(str[i]);
    return ;
}