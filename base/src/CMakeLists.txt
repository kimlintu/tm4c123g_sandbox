include(files.cmake)

add_library(base STATIC "${C_FILES}")

target_include_directories(base PRIVATE "${H_FILE_DIRS}")