/* execution after boot process, typically located at reset vector in flash */
ENTRY(Reset_Handler)

/* define memory sections */
MEMORY
{
FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 320K
}

SECTIONS
{
.isr_vector :
{
. = ALIGN(4);
KEEP(*(.isr_vector)) /* Use .isr_vector to match template startup.s */
. = ALIGN(4);
} > FLASH
.text :
{
. = ALIGN(4);
*(.text)
*(.text.*)
. = ALIGN(4);
_etext = .;
} > FLASH
.data : ALIGN(4)
{
_sidata = LOADADDR(.data); /* Load address in FLASH */
_sdata = .; /* Runtime address in RAM */
*(.data)
*(.data.*)
. = ALIGN(4);
_edata = .;
} > RAM AT > FLASH
.bss :
{
. = ALIGN(4);
_sbss = .;
*(.bss)
*(.bss.*)
. = ALIGN(4);
_ebss = .;
} > RAM
._user_heap_stack :
{
. = ALIGN(8);
. = . + 0x400; /* Heap size */
. = ALIGN(8);
. = . + 0x400; /* Stack size */
. = ALIGN(8);
_estack = .;
} > RAM
}
