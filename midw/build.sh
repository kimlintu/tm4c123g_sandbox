#!/bin/bash

cmd_clean() {
    rm -rf out
}

cmd_build() {
    cmake -DCMAKE_TOOLCHAIN_FILE=../extern/base/toolchain/tm4c123g_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=../extern -S . -B out
    cmake --build out
}

cmd_install() {
    cmake --install out --prefix out/release
}

cmd_release() {
    if [ -d "../extern/midw" ]; then
        rm -rf ../extern/midw
    fi
    
    mkdir ../extern
    mkdir ../extern/midw
    cp -r out/release/* ../extern/midw
}

if [ "$1" == "clean" ]; then
    cmd_clean
fi

if [ "$1" == "build" ]; then
    cmd_clean
    cmd_build
fi

if [ "$1" == "install" ]; then
    cmd_clean
    cmd_build
    cmd_install
fi

if [ "$1" == "release" ]; then
    cmd_clean    
    cmd_build
    cmd_install
    cmd_release
fi