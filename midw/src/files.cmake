list(APPEND C_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/main.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/comm/comm_uart.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/diom/diom_pwmo.c"
)

list(APPEND H_FILE_DIRS
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/comm>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/diom>"
)