/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-05-02
 */
ENTRY (main)

SECTIONS {
    . = 0x00020000;
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
