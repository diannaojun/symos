ENTRY (main)

SECTIONS {
    . = 0x00098800;
    . = ALIGN(4);
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
