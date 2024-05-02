cmake_minimum_required(VERSION 3.22.1)

project(APPL)

add_subdirectory(src)

add_executable(appl_target "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")

find_package(base CONFIG REQUIRED)

target_link_libraries(appl_target PRIVATE appl)
target_link_libraries(appl_target PRIVATE LibBase::base)