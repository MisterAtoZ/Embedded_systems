#   Part of the Raspberry-Pi Bare Metal Tutorials
#   Copyright (c) 2013, Brian Sidebotham
#   All rights reserved.

#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are met:

#   1. Redistributions of source code must retain the above copyright notice,
#       this list of conditions and the following disclaimer.

#   2. Redistributions in binary form must reproduce the above copyright notice,
#       this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.

#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
#   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
#   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
#   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
#   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
#   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
#   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#   POSSIBILITY OF SUCH DAMAGE.

# CMake build environment based on the Valvers Raspberry-Pi bare metal tutorials
# and modified for an UART interrupt driven device driver

# CMake 2.8.10 Documentation: http://www.cmake.org/cmake/help/v2.8.10/cmake.html

cmake_minimum_required( VERSION 2.8 )

# Set the tutorial number so it's easier to re-use the CMakeLists.txt
set( NAME uart )

# Mark the language as C so that CMake doesn't try to test the C++
# cross-compiler's ability to compile a simple program because that will fail
project( ${NAME}-driver C ASM )

# Add any C compiler flags here. The C flags concerned with processor tuning
# are in the toolchain files toolchain-arm-none-eabi-bcm2835.cmake, etc.
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O1" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostartfiles" )

# Set the linker flags so that we use our "custom" linker script
set( CMAKE_EXE_LINKER_FLAGS "-Wl,-T,${PROJECT_SOURCE_DIR}/rpi.x" )

add_executable( ${NAME}
    ${NAME}.c
    ${NAME}-cstartup.c
    ${NAME}-start.s
    defines.h
    rpi-gpio.c
    rpi-gpio.h
    rpi-interrupts.c
    rpi-interrupts.h
    rpi-uart.c )

add_custom_command(
    TARGET ${NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ./${NAME} -O binary ./kernel.img
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Convert the ELF output file to a binary image" )
