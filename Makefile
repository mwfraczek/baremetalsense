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

bin/main.elf: build/peripherals.o build/bmp390.o build/i2c.o build/main.o build/startup.o 
	$(CC) $(CFLAGS) $(LDFLAGS) -o bin/main.elf build/peripherals.o build/bmp390.o build/i2c.o build/main.o build/startup.o

build/peripherals.o: src/peripherals.c
	$(CC) $(CFLAGS) -c src/peripherals.c -o build/peripherals.o

build/bmp390.o: src/bmp390.c
	$(CC) $(CFLAGS) -c src/bmp390.c -o build/bmp390.o

build/i2c.o: src/i2c.c
	$(CC) $(CFLAGS) -c src/i2c.c -o build/i2c.o

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/startup.o: src/startup.c
	$(CC) $(CFLAGS) -c src/startup.c -o build/startup.o

#cleans project directory
.PHONY: clean
clean: 
	rm -f bin/* build/*
