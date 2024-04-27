#!/bin/sh

if [ "$1" = "clean" ]; then
    cd appl 
    make clean

    cd ..

    cd boot 
    make clean

    cd ..

    rm -rf out

    exit
fi

############################
# Create application binary
cd appl 

if [ ! -d "out/" ]; then
    mkdir out
fi

make 
############################

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
cat boot/out/boot.bin appl/out/appl.bin > out/target.bin
############################