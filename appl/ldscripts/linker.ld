MEMORY 
{
    FLASH(rx) : ORIGIN = 0x00001000, LENGTH = 0x0003F000 /* 256K - 1K boot = 255K */
    RAM(rwx) : ORIGIN = 0x20000000, LENGTH = 0x00008000  /* 32K*/
}

ENTRY(startup)

SECTIONS
{
    .text :
    {
        KEEP(*(.appl_isr_vector))
        *(.text)
    } > FLASH

    _lnk_textSectionEnd_U32 = ALIGN (4);

    /* .data section */

    _lnk_romDataSectionStart_U32 = _lnk_textSectionEnd_U32;
    .data : AT(_lnk_romDataSectionStart_U32) 
    {
        _lnk_ramDataSectionStart_U32 = .;

        *(.data)

        . = ALIGN(4);

        _lnk_ramDataSectionEnd_U32 = .;
    } > RAM

    _lnk_dataSectionSize_U32 = _lnk_ramDataSectionEnd_U32 - _lnk_ramDataSectionStart_U32;

    /* .bss section */

    .bss :
    {
        . = ALIGN(4);

        _lnk_ramBssSectionStart_U32 = .;

        *(.bss)

        . = ALIGN(4);

        _lnk_ramBssSectionEnd_U32 = .;
    } > RAM

    _lnk_bssSectionSize_U32 = _lnk_ramBssSectionEnd_U32 - _lnk_ramBssSectionStart_U32;

    /* Stack */

    _lnk_stackTop = ORIGIN(RAM) + LENGTH(RAM);
}