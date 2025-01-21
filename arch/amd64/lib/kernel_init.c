#include <kernel/init.h>
#include <string.h>

void putc_init(char ch){
    ch = toascii(ch);
    switch(ch){
        case '\t':
            *POS_ADDR = (*POS_ADDR + 7) & 0xfff8;
            break;
        case '\n':
            *POS_ADDR += 160;
            break;
        case '\r':
            *POS_ADDR = (*POS_ADDR + 7) & 0xfff8;
            break;
        default:
            *(short*)(size_t)(BAS_ADDR | *POS_ADDR) = ch | 0x0f00;
            *POS_ADDR += 2;
    }
    return ;
}

void puts_init(const char* str){
    static size_t i;
    for(i=0; str[i]; ++i)
        putc_init(str[i]);
    return ;
}

virtual_node_t *root_init(void){
    virtual_node_t *root = (virtual_node_t *)(0x0c + 8*5);
    strncpy(root->name, "", 8);
    root->hash1 = hash1(root->name);
    root->hash2 = hash2(root->name);
    root->nxt = root->son = NULL;
    return root;
}
