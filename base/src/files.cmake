list(APPEND C_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/clck/clck_sysc.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/coms/coms_uart.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/diio/diio_pwmd.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/gnio/gnio_gpio.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/data/data_rbfr.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/strt/strt_main.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/strt/strt_vect.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/time/time_syst.c"
)

list(APPEND H_FILE_DIRS
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/clck/>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/coms/>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/diio/>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/gnio/>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/data/>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/strt/>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/tm4c/>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/time/>"
)