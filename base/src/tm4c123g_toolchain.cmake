# System
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# C compiler
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_C_FLAGS "-nostdlib -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wl,--Map=out.map,--gc-sections,-L/home/kimli/projects/tm4c123_test/proj/base/ld,-Tlinker.ld")
set(CMAKE_C_FLAGS_DEBUG "-g -gdwarf-3 -gstrict-dwarf -DDEBUG")

# C++ system (not used)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

# Skip compiler checks (it tries to link with C std lib)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)