// Forward declarations of linker-provided symbols
extern unsigned long _estack;
extern unsigned long _etext;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;

void Reset_Handler(void);

// Forward declaration for main
extern int main(void);

// Vector table
__attribute__((section(".vectors")))
void (*const vector_table[])(void) = {
	(void (*)(void))((unsigned long)&_estack),  // Initial stack pointer
	Reset_Handler                               // Reset handler
};

// Reset handler implementation
void Reset_Handler(void) {
	// Initialize data and clear BSS
	unsigned long *src = &_etext;
	unsigned long *dst = &_sdata;
	while (dst < &_edata) *dst++ = *src++;
	while (dst < &_ebss) *dst++ = 0;
	main();
	while (1); // Loop here if main returns
}
