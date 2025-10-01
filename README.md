# Overview: 🌎
This repository features a **bare-metal I2C driver** and application level code written in **C** for the Nucleo-L476RG. It is designed to read temperature and pressure data from a BMP390 sensor. The purpose of this project is to develop and showcase **low-level programming** skills without reliance on HAL or abstraction libraries - with everything being **configured directly from the STM32L4xx Reference Manual** (RM0351). The goal is to demonstrate a solid baseline understanding of embedded systems programming, along with the various tools required to accomplish the task. 

- _YouTube_: Video presentation in progress...

## Features: ✔️
- I2C Communication at 85kHz with clean, sharp waveform.
- Single-byte read support for BMP390 chip id (0x60), status (0x70, if data is ready), and pressure data (sensor registers: 0x04-0x06)
- User LED feedback: Slow blink for successful program execution, fast blink if error(s) occur.

## Hardware Requirements: 🧰
- **MCU:** Nucleo-L476RG (STM32L476RG).
- **Sensor:** BMP390 Breakout Board - Adafruit or Amazon variants have both been tested and verified to work.
- **Pull-ups:** 2.2kOhm on SCL and SDA. Ideal communication and waveform results may vary dependent on your hardware setup and capacitance characteristics.
- **Power:** PC supplied USB-power to Nucleo board. Nucleo board supplied 3.3V VDD to sensor.
- **Configuration:** SDO tied to GND (slave addr: 0x76). CSB tied to 3.3V (I2C Interface Selection).   

## Build Instructions: 🛠️
- **Install** ARM GCC toolchain: `sudo apt install gcc-arm-none-eabi`
- **Clone** repo: `git clone https://github.com/mwfraczek/baremetalsense.git`
- **Build**: `make`
- **Flash**: `st-flash --reset write bin/main.bin 0x08000000` or use STM32CubeIDE

## Status: 📈
- **Current**:
  1. Successfully reads first 3 data bytes (0x04-0x06) with LED feedback. 
- **Challenges**:
  1. Multi-byte read fails to ACK second-byte transmission, and subsequently hangs/stretches. Debugging in progress.
- **Next Steps**: 
  1. Target 100kHz with clean waveform.
  2. Implement hardware-based delays for precise timing, minimizing CPU cycle waste.
  3. Resolve multi-byte read issue.
 
## Directory Structure: 📂
    .
    ├── bin
    ├── build
    ├── drivers
    │   ├── bmp390.c
    │   ├── i2c.c
    │   └── peripherals.c
    ├── inc
    │   ├── bmp390.h
    │   ├── i2c.h
    │   ├── peripherals.h
    │   └── stm32l476.h
    ├── linker.ld
    ├── Makefile
    ├── README
    └── src
        ├── main.c
        ├── startup.s
        └── system.c

## Contributions: 👤
- **Author:** Michael Fraczek
- Open to feedback!
