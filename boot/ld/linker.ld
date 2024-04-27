MEMORY 
{
    FLASH(rx) : ORIGIN = 0x00000000, LENGTH = 0x00001000
    RAM(rwx) : ORIGIN = 0x20000000, LENGTH = 0x00008000
}

ENTRY(boot_main)

SECTIONS
{
    .text : 
    {
		KEEP(*(.boot_isr_vector))
        *(.text)
    } > FLASH

    .data :
    {
        . = ALIGN(4);
        *(.data)
    } > RAM

    .bss :
    {
        . = ALIGN(4);
        *(.bss)
    }

    __StackTop = ORIGIN(RAM) + LENGTH(RAM);
} 