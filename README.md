# Overview: 🌎
This repository features a **bare-metal I2C driver** and application level code written in **C** for the Nucleo-L476RG. It is designed to read temperature and pressure data from a BMP390 sensor. The purpose of this project is to develop and showcase **low-level programming** skills without reliance on HAL or abstraction libraries - with everything being **configured directly from the STM32L4xx Reference Manual** (RM0351). The goal is to demonstrate a solid baseline understanding of embedded systems programming, along with the various tools required to accomplish the task. 

- _YouTube_: Video presentation in progress...


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


## Status: 📈
- **Current**:
  1. Successfully reads pressure data bytes (0x04-0x06) in single-byte read function calls with LED feedback. 
- **Challenges**:
  1. Issues achieving targeted 100kHz communication frequency. Currently oscilloscope verified 85kHz. 
  1. Multi-byte read fails to ACK second-byte transmission, and subsequently hangs/stretches. Debugging in progress.
- **Next Steps**: 
  1. Target 100kHz with clean waveform. ☑️
  2. Implement hardware based delay function for precise, non-blocking delays. ☑️ 
  3. Resolve multi-byte read issue.


## Implementation Notes: 📓
#### ✳️<ins>TIM2 Hardware Delay Implementation</ins> - 10/03/2025: 
To enable precise, non-blocking delays BMP390 reads and LED feedback: 
1. Select clock source to drive System Clock (RCC selection sets SYSCLK).
   - Note: RCC_CFGR can prescale SYSCLK before TIM2 prescaling.
   - SYSCLK feeds AHB bus, which feeds APB1 (TIM2 on APB1).
2. Disable Slave Mode Controller in SCMR register to control relevant CR1 (CEN, DIR) and EGR bits (UG). 
3. Define relevant counter configuration registers with chosen values (PSC, ARR, CNT). 
4. Set UG bit in EGR register to apply configuration settings.
   - Note: ARPE bit in CR1 should be set _**IF**_ ARR register is to dynamically used/changes while TIM2 is operating. 
5. Set CEN bit in CR1 to enable TIM2 counter. 
6. Implement ‘delay_ms’ function leveraging TIM2 hardware timer for precise, non-blocking delays.

#### ✳️100kHz Targeted Communication Frequency - 10/05/2025: 
1. Initial ST provided TIMINGR register suggested value `0x10080803` resulted in 85kHz frequency.
2. Review of TIMINGR register shows SCL high (SCLH) and low (SCLL) periods can be manipulated via bitfields [15:8] and [7:0], respectively. Shortening SCL period should result in increased frequency. IMAGE A presents the register. 
3. Updated TIMINGR register bitfields `0x10080202` results in targeted 100kHz frequency. IMAGE B shows oscilloscope verified 101.29kHz of the `bmp390_setup` function execution.
   - Note: Similar results were observed with I2C clock prescaler removal and increasing SCL high and low period times (i.e. `0x00080F0F`). Further investigation into register configurations and waveform analysis is recommended to optimize performance, though this adjustment highlights the TIMINGR register's flexibility in fine-tuning I2C timing frequencies.

#### IMAGE A:
<img width="792" height="160" alt="image" src="https://github.com/user-attachments/assets/dd68f34c-093d-40df-881d-77424e299123" />

#### IMAGE B:
<img width="698" height="433" alt="image" src="https://github.com/user-attachments/assets/ebcd27da-a846-438e-8e05-11eb927fe716" />


## Contributions: 👤
- **Author:** Michael Fraczek
- Open to feedback!
