cmake_clean() {
    if [ -d "out/" ]; then
        rm -rf out
    fi
}

cmake_build() {
    cmake -DCMAKE_TOOLCHAIN_FILE=./src/tm4c123g_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=../extern -S . -B out/
    cmake --build out
}

cmake_install() {
    cmake --install out --prefix out/release
}

cmake_release() {
    if [ -d "../extern/base" ]; then
        rm -rf ../extern/base
    fi
    
    mkdir ../extern
    mkdir ../extern/base
    cp -r out/release/* ../extern/base
}

if [ "$1" == "clean" ]; then
    cmake_clean
fi

if [ "$1" == "build" ]; then
    cmake_build
fi

if [ "$1" == "release" ]; then
    cmake_clean
    cmake_build
    cmake_install
    cmake_release
fi