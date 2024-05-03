include(files.cmake)

add_library(midw STATIC "${C_FILES}")

#target_link_libraries(midw LibBase::base)

# target_include_directories(midw PRIVATE
#     "$<TARGET_PROPERTY:LibBase::base,INTERFACE_INCLUDE_DIRECTORIES>"
# )

target_include_directories(midw PUBLIC 
    "${H_FILE_DIRS}"
    "$<INSTALL_INTERFACE:include/>")