
add_library(Matrixutil MODULE MatrixPyInterface.cpp)
target_link_libraries(Matrixutil PRIVATE matrix Python::Module)
set_target_properties(Matrixutil PROPERTIES PREFIX "")

# Install the Matrixutil library
install(TARGETS Matrixutil
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# Install the Matrix directory, excluding __pycache__
install(DIRECTORY Matrix DESTINATION ${CMAKE_INSTALL_LIBDIR} PATTERN "__pycache__" EXCLUDE)