/* execution after boot process, typically located at reset vector in flash */
ENTRY(Reset_Handler)

/* define memory sections */
MEMORY
{
	FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 1024K
	RAM(rxw)  : ORIGIN = 0x20000000, LENGTH = 320K
}


SECTIONS
{
	.vectors : ALIGN(4)
    	{
        KEEP(*(.vectors))
    	} > FLASH

	/* program executable code (functions and instructions) placed here */
	.text : ALIGN(4)
    	{
        *(.text)
        *(.text.*)
        . = ALIGN(4);
        _etext = .;
    	} > FLASH

	/* initialized variables stored here */
    	.data : ALIGN(4)
    	{
        _sdata = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _edata = .;
    	} > RAM AT > FLASH

	/* memory section that is cleared at startup - uninitialized variables stored here - i.e. 'int x' */
	.bss : ALIGN(4)
    	{
        _sbss = .;
        *(.bss)
        *(.bss.*)
        . = ALIGN(4);
        _ebss = .;
    	} > RAM

    	.stack : ALIGN(4)
    	{
        . = . + 0x1000;  /* 4KB stack */
        _estack = ORIGIN(RAM) + LENGTH(RAM);
    	} > RAM
}
