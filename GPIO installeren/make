arm-none-eabi-gcc -O0 -mcpu=cortex-a53 -mfloat-abi=hard -mfpu=neon-fp-armv8 -nostartfiles -g ts.s t.ld blinking_LED.c -o kernel.elf # saai
arm-none-eabi-objcopy kernel.elf -O binary kernel.img