cmake_minimum_required(VERSION 3.22.1)

project(base)


# Creates "base" library as lib
add_subdirectory(src)

find_package(cmakeUtils CONFIG REQUIRED)
include(cmakeExporting)
include(cmakeLogging)

export_target(TARGET            base 
              NAMESPACE         LibBase:: 
              LIB_DESTINATION   "lib/"
              CMAKE_DESTINATION "cmake/"
)

get_target_property(BASE_INCLUDE_DIRECTORIES base INCLUDE_DIRECTORIES)
install(DIRECTORY ${BASE_INCLUDE_DIRECTORIES} DESTINATION "include/" )

package_release(TARGET base
                CMAKE_DESTINATION "cmake/"
)