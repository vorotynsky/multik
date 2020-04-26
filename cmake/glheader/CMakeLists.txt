cmake_minimum_required(VERSION 2.8)


if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_library(glheader INTERFACE)

include_directories(glfw3 ${GLUT_INCLUDE_DIRS})
target_include_directories(glheader INTERFACE .)
target_compile_definitions(glheader INTERFACE LIBRARY_HEADER_ONLY)
target_link_libraries(glheader INTERFACE GLEW OpenGL::GL glfw glm)
