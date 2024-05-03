include(files.cmake)

add_library(base STATIC "${C_FILES}")

target_include_directories(base PUBLIC 
    "${H_FILE_DIRS}"
    "$<INSTALL_INTERFACE:include/>"
)