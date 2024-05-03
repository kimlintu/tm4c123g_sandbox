#!/bin/bash

if [ "$1" == "clean" ]; then
    rm -rf out
fi

if [ "$1" == "build" ]; then
    cmake -S . -B out -DCMAKE_PREFIX_PATH=../extern
    cmake --build out
fi