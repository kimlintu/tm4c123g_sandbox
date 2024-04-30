include(files.cmake)

add_library(BASE STATIC "${C_FILES}")

target_include_directories(BASE PRIVATE "${H_FILE_DIRS}")