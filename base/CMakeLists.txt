cmake_minimum_required(VERSION 3.22.1)

project(base)

include(cmakeExporting)
include(cmakeLogging)

# Creates "base" library as lib
add_subdirectory(src)

export_target(TARGET            base 
              NAMESPACE         LibBase:: 
              LIB_DESTINATION   "lib/"
              CMAKE_DESTINATION "cmake/"
)

package_release(TARGET base
                CMAKE_DESTINATION "cmake/"
)