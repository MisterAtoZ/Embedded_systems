/********************************************************************
Copyright 2010-2017 K.C. Wang, <kwang@eecs.wsu.edu>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

NOTE: This header file is modified from its original contents to 
	  facilitate the implementation of an interrupt-driven UART
	  driver.
********************************************************************/

// defines.h file

#ifndef DEFINES_H
#define DEFINES_H

// General type definitions
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// GPIO 
#define GPIO_BASE	0x20200000

#define SYSTEM_TIMER_BASE 0x020003000

#define GPIO_GPFSEL0    0
#define GPIO_GPFSEL1    1
#define GPIO_GPFSEL2    2
#define GPIO_GPFSEL3    3
#define GPIO_GPFSEL4    4
#define GPIO_GPFSEL5    5

#define GPIO_GPSET0     7
#define GPIO_GPSET1     8

#define GPIO_GPCLR0     10
#define GPIO_GPCLR1     11

#define GPIO_GPLEV0     13
#define GPIO_GPLEV1     14

#define GPIO_GPEDS0     16
#define GPIO_GPEDS1     17

#define GPIO_GPREN0     19
#define GPIO_GPREN1     20

#define GPIO_GPFEN0     22
#define GPIO_GPFEN1     23

#define GPIO_GPHEN0     25
#define GPIO_GPHEN1     26

#define GPIO_GPLEN0     28
#define GPIO_GPLEN1     29

#define GPIO_GPAREN0    31
#define GPIO_GPAREN1    32

#define GPIO_GPAFEN0    34
#define GPIO_GPAFEN1    35

#define GPIO_GPPUD      37
#define GPIO_GPPUDCLK0  38
#define GPIO_GPPUDCLK1  39

// Peripheral base address
#define PERIPHERAL_BASE 0x20000000UL

// UART
#define UDR   0x00
#define UDS   0x04
#define RXFE  0x10
#define UFR   0x18
#define TXFF  0x20
#define CNTL  0x2C
#define IMSC  0x38
#define MIS   0x40
#define SBUFSIZE 128

// I2C
#define BSC1_BASE (0x20804000)

#define BSC1_C        0
#define BSC1_S        1
#define BSC1_DLEN     2
#define BSC1_A        3
#define BSC1_FIFO     4
#define CLOCK_DIVIDER 5
#define DATA_DELAY	  6
#define CLOCK_STRETCH_TIMEOUT 7

#define BSC_C_I2CEN   (1 << 15)
#define BSC_C_INTR    (1 << 10)
#define BSC_C_INTT    (1 << 9)
#define BSC_C_INTD    (1 << 8)
#define BSC_C_ST      (1 << 7)
#define BSC_C_CLEAR   (1 << 4)
#define BSC_C_READ    1

#define START_READ    BSC_C_I2CEN|BSC_C_ST|BSC_C_CLEAR|BSC_C_READ
#define START_WRITE    BSC_C_I2CEN|BSC_C_ST

#define BSC_S_CLKT   (1 << 9)
#define BSC_S_ERR    (1 << 8)
#define BSC_S_RXF    (1 << 7)
#define BSC_S_TXE    (1 << 6)
#define BSC_S_RXD    (1 << 5)
#define BSC_S_TXD    (1 << 4)
#define BSC_S_RXR    (1 << 3)
#define BSC_S_TXW    (1 << 2)
#define BSC_S_DONE   (1 << 1)
#define BSC_S_TA     1

#define CLEAR_STATUS    BSC_S_CLKT|BSC_S_ERR|BSC_S_DONE

#endif