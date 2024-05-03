cmake_minimum_required(VERSION 3.22.1)

project(cmakeUtils)

include(CMakePackageConfigHelpers)

# Create package config file
configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/export/packageConfig.cmake.in"
                               "${CMAKE_BINARY_DIR}/export/cmakeUtilsConfig.cmake"
                               INSTALL_DESTINATION "cmake/"
)

# Copy the package config files to installation directory
install(FILES 
        "${CMAKE_BINARY_DIR}/export/cmakeUtilsConfig.cmake"
        DESTINATION "cmake/"
)

install(FILES 
        "${CMAKE_SOURCE_DIR}/scripts/cmakeExporting.cmake"
        "${CMAKE_SOURCE_DIR}/scripts/cmakeLogging.cmake"
        DESTINATION "scripts/"
)