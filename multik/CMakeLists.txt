cmake_minimum_required(VERSION 2.8)

add_executable(multik "main.cpp")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
include_directories(glfw3  ${GLUT_INCLUDE_DIRS})

target_link_libraries(multik glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
