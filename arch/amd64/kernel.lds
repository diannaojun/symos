ENTRY (main)

SECTIONS {
    . = 0x08800;
    .text : {
        *(.text.main);
        *(.text*);
    }
    .rodata : {
        *(.rodata*);
    }
    .data : {
        *(.data*);
    }
    __bss_start = .;
    .bss : {
        *(.bss*);
    }
    __bss_end = .;
}
