cmake_minimum_required(VERSION 3.24)
project(MatrixExample VERSION 0.0.1)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
include(CTest)

# RPATH settings
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# Source and header files
file(GLOB MATRIX_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB MATRIX_INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
# Add the library
add_library(matrix SHARED
    ${MATRIX_INC_FILES}
    ${MATRIX_SRC_FILES}
)

# Find OpenMP package
find_package(OpenMP REQUIRED)
find_package(Python REQUIRED COMPONENTS Interpreter Development)
target_link_libraries(matrix PUBLIC OpenMP::OpenMP_CXX)
target_include_directories(matrix PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# Add the tests from tests directory
add_subdirectory(tests)

include(GNUInstallDirs)
add_subdirectory(py)

# Install the library, headers, and CMake package configuration files
install(TARGETS matrix BasicTest LUFactorizationTest LUPFactorizationTest QRFactorizationTest QRCPFactorizationTest LUPFactorizationParallelTest
        EXPORT matrixTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include)

install(FILES ${MATRIX_INC_FILES} DESTINATION include)

# Generate and install the CMake package configuration files
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/matrixConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_file(matrixConfig.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/matrixConfig.cmake" @ONLY)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/matrixConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/matrixConfigVersion.cmake"
    DESTINATION lib/cmake/matrix
)

# Export the targets to a file
install(EXPORT matrixTargets
        FILE matrixTargets.cmake
        NAMESPACE matrix::
        DESTINATION lib/cmake/matrix
)

# Register the package in the user's package registry
export(EXPORT matrixTargets FILE "${CMAKE_CURRENT_BINARY_DIR}/matrixTargets.cmake")
export(PACKAGE matrix)