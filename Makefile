#ensures make uses expected shell with appropriate syntax/behavior
SHELL = /bin/sh

#toolchain setup 
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -Wextra -nostdlib -Iinc -g
LDFLAGS = -Tlinker.ld

#default goal of makefiles is the first target of the first rule of the first makefile
all: bin/main.elf bin/main.bin

bin/main.bin: bin/main.elf
	$(OBJCOPY) -O binary bin/main.elf bin/main.bin

bin/main.elf: build/peripherals.o build/bmp390.o build/i2c.o build/main.o build/system_stm32l496.o build/startup_stm32l496xx.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o bin/main.elf build/peripherals.o build/bmp390.o build/i2c.o build/main.o build/system_stm32l496.o build/startup_stm32l496xx.o

build/peripherals.o: src/peripherals.c
	$(CC) $(CFLAGS) -c src/peripherals.c -o build/peripherals.o

build/bmp390.o: src/bmp390.c
	$(CC) $(CFLAGS) -c src/bmp390.c -o build/bmp390.o

build/i2c.o: src/i2c.c
	$(CC) $(CFLAGS) -c src/i2c.c -o build/i2c.o

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/system_stm32l496.o: src/system_stm32l496.c
	$(CC) $(CFLAGS) -c src/system_stm32l496.c -o build/system_stm32l496.o

build/startup_stm32l496xx.o: src/startup_stm32l496xx.s
	$(CC) $(CFLAGS) -x assembler-with-cpp -c src/startup_stm32l496xx.s -o build/startup_stm32l496xx.o

#cleans project directory
.PHONY: clean
clean: 
	rm -f bin/* build/*
