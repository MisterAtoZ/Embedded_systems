arm-none-eabi-gcc -O0 -DRPIBPLUS -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -g ts.s t.ld t.c -o kernel.elf
arm-none-eabi-objcopy kernel.elf -O binary kernel.img
#https://stackoverflow.com/questions/37566064/why-questionmark-comes-in-the-end-of-filename-when-i-create-txt-file-through-sh