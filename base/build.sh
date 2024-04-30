if [ $1 == "clean" ]; then
    rm -rf out
else
    cmake -DCMAKE_TOOLCHAIN_FILE=./src/tm4c123g_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -S . -B out/
    cmake --build out
fi