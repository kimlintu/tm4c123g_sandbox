function(export_target)
    set(oneValueArgs TARGET NAMESPACE LIB_DESTINATION CMAKE_DESTINATION)
    cmake_parse_arguments(EXPORT_TARGET "" "${oneValueArgs}" "" ${ARGN})

    set(EXPORT_TARGET_NAME "${EXPORT_TARGET_TARGET}Targets")

    # Export library target
    log_message("Exporting ${EXPORT_TARGET_NAMESPACE}${EXPORT_TARGET_TARGET} to ${EXPORT_TARGET_LIB_DESTINATION}")
    install(TARGETS "${EXPORT_TARGET_TARGET}"
            EXPORT  "${EXPORT_TARGET_NAME}"
            ARCHIVE DESTINATION "${LIB_DESTINATION}" 
    )

    # Generate and install the target export details (will be placed in will be placed in ${EXPORT_TARGET_NAME}.cmake)
    log_message("Writing export details for ${EXPORT_TARGET_NAMESPACE}${EXPORT_TARGET_TARGET} to ${EXPORT_TARGET_CMAKE_DESTINATION}")

    install(EXPORT      "${EXPORT_TARGET_NAME}" 
            FILE        "${EXPORT_TARGET_NAME}.cmake"
            NAMESPACE   "${EXPORT_TARGET_NAMESPACE}"
            DESTINATION "${EXPORT_TARGET_CMAKE_DESTINATION}"
    )
endfunction()

function(package_release)
    set(oneValueArgs TARGET CMAKE_DESTINATION)
    cmake_parse_arguments(PACKAGE_RELEASE "" "${oneValueArgs}" "" ${ARGN})

    # Check that target is created
    if (NOT TARGET "${PACKAGE_RELEASE_TARGET}")
        log_error_message_and_quit("Trying to release target \"${PACKAGE_RELEASE_TARGET}\", but it doesn't exist")
    endif()
    
    # Used for package creating utilites (configure_package_config_file)
    include(CMakePackageConfigHelpers)

    # Create package config file
    configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/export/packageConfigTemplate.cmake.in"
                                "${CMAKE_BINARY_DIR}/export/${PACKAGE_RELEASE_TARGET}Config.cmake"
                                INSTALL_DESTINATION "${PACKAGE_RELEASE_CMAKE_DESTINATION}"
    )

    # Copy the package config files to installation directory
    install(FILES 
            "${CMAKE_BINARY_DIR}/export/${PACKAGE_RELEASE_TARGET}Config.cmake"
            DESTINATION "${PACKAGE_RELEASE_CMAKE_DESTINATION}"
    )
endfunction()