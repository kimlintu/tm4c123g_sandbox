#!/bin/sh

# Build base lib

cd base

./build.sh "install"

cd ..

# Build midw lib

cd midw

./build.sh "release"

cd ..

# Build app

cd appl

./build.sh 

cd out

arm-none-eabi-objcopy -I elf32-littlearm -O binary target target.bin 

cd ..

cd ..

############################
# Create boot binary
BOOTLOADER_SIZE=0x1000
BOOTLOADER_FILE="out/boot.bin"

cd boot 

if [ ! -d "out/" ]; then
    mkdir out
fi

make

python pad_file.py $BOOTLOADER_FILE $BOOTLOADER_SIZE
############################

cd ..

############################
# Create final executable with boot + application
if [ ! -d "out/" ]; then
    mkdir out
fi

echo "Creating target.bin"
cat boot/out/boot.bin appl/out/target.bin > out/target.bin
############################