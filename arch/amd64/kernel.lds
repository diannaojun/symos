ENTRY (main)

SECTIONS {
    . = 0x98800;
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
