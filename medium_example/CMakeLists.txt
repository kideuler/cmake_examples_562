cmake_minimum_required(VERSION 3.12)
project(MatrixExample)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

# add the library
add_library(matrix
    ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix.cpp
    )

# Add the executable target
add_executable(main
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    )

# Link the library to the executable
target_link_libraries(main matrix)