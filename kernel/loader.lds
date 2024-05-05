/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-04-05
 */
ENTRY (main)

SECTIONS {
    . = 0x00008000;
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
