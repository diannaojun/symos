ENTRY (main)

SECTIONS {
    . = 0x098800;
    .text : {
        *(.text.main);
        *(.text);
    }
    .rodata : {
        *(.rodata);
    }
    .data : {
        *(.data);
    }
    .bss : {
        *(.bss);
    }
}
