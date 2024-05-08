include(files.cmake)

add_library(midw STATIC "${C_FILES}")

target_link_libraries(midw PRIVATE LibBase::base)                

target_include_directories(midw PUBLIC 
    "${H_FILE_DIRS}"
    "$<INSTALL_INTERFACE:include/>"
)