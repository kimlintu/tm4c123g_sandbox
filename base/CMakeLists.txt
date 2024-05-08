cmake_minimum_required(VERSION 3.22.1)

project(base)


# Creates "base" library as lib
add_subdirectory(src)

find_package(cmakeUtils CONFIG REQUIRED)
include(cmakeExporting)

export_target(TARGET            base 
              NAMESPACE         LibBase:: 
              LIB_DESTINATION   "lib"
              INCL_DESTINATION  "include"
)

package_release(TARGET base)

install(FILES "src/tm4c123g_toolchain.cmake" DESTINATION "toolchain")