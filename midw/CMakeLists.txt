cmake_minimum_required(VERSION 3.22.1)

project(midw)

find_package(base CONFIG REQUIRED)       # Base library
find_package(cmakeUtils CONFIG REQUIRED) # Commands for exporting and creating release package

include(cmakeExporting)

# Create midw library target
add_subdirectory(src)

export_target(TARGET            midw 
              NAMESPACE         LibMidw:: 
              LIB_DESTINATION   "lib"
              INCL_DESTINATION  "include"
)

package_release(TARGET midw)