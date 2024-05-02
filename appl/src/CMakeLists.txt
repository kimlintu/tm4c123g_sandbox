include(files.cmake)

add_library(appl STATIC "${C_FILES}")

target_include_directories(appl PUBLIC "${H_FILE_DIRS}")