#!/bin/bash

cmd_clean() {
    rm -rf out
}

cmd_build() {
    cmake -S . -B out
}

cmd_install() {
    cmake --install out --prefix out/release
}

cmd_release() {
    if [ -d "../extern/cmakeUtils" ]; then
        rm -rf ../extern/cmakeUtils
    fi
    
    mkdir ../extern
    mkdir ../extern/cmakeUtils
    cp -r out/release/* ../extern/cmakeUtils
}

if [ "$1" == "clean" ]; then
    cmd_clean
fi

if [ "$1" == "release" ]; then
    cmd_clean    
    cmd_build
    cmd_install
    cmd_release
fi