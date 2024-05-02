list(APPEND C_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/gpio.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/pwmo.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/rbfr.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/syst.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/uart.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/clck.c"
)

list(APPEND H_FILE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)