if [ "$1" == "clean" ]; then
    rm -rf out
else
    rm -rf out
    cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=../base/src/tm4c123g_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=../extern -S . -B out/
    cmake --build out/
fi