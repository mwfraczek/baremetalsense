#ensures make uses expected shell with appropriate syntax/behavior
SHELL = /bin/sh 

#toolchain setup 
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -Wextra -nostdlib -Iinc -g
ASFLAGS = -mcpu=cortex-m4 -mthumb -g
LDFLAGS = -Tlinker.ld

#default goal of makefiles is the first target of the first rule of the first makefile
all: bin/main.elf bin/main.bin

bin/main.bin: bin/main.elf
	$(OBJCOPY) -O binary bin/main.elf bin/main.bin

bin/main.elf: build/utils.o build/peripherals.o build/bmp390.o build/i2c.o build/main.o build/startup.o build/system.o 
	$(CC) $(CFLAGS) $(LDFLAGS) -o bin/main.elf build/utils.o build/peripherals.o build/bmp390.o build/i2c.o build/main.o build/startup.o build/system.o

build/utils.o: drivers/utils.c
	$(CC) $(CFLAGS) -c drivers/utils.c -o build/utils.o

build/peripherals.o: drivers/peripherals.c
	$(CC) $(CFLAGS) -c drivers/peripherals.c -o build/peripherals.o

build/bmp390.o: drivers/bmp390.c
	$(CC) $(CFLAGS) -c drivers/bmp390.c -o build/bmp390.o

build/i2c.o: drivers/i2c.c
	$(CC) $(CFLAGS) -c drivers/i2c.c -o build/i2c.o

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/startup.o: src/startup.s
	$(AS) $(ASFLAGS) -c src/startup.s -o build/startup.o

build/system.o: src/system.c
	$(CC) $(CFLAGS) -c src/system.c -o build/system.o

#cleans project directory
.PHONY: clean
clean: 
	rm -f bin/* build/*
