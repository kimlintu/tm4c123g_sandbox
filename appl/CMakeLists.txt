cmake_minimum_required(VERSION 3.24)

project(APPL)

find_package(midw CONFIG REQUIRED)

add_executable(target "${CMAKE_CURRENT_SOURCE_DIR}/src/dummy.c")

target_link_libraries(target PRIVATE LibMidw::midw)