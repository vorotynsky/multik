cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()

add_compile_definitions(GLEW_STATIC)


file(GLOB multikSrc
        "*/*.hpp"
        "*/*.cpp"
        "main.cpp")

add_executable(multik ${multikSrc})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(glfw3  ${GLUT_INCLUDE_DIRS})

target_link_libraries(multik GLEW OpenGL::GL glfw)

add_custom_target(copy_shaders)
add_custom_command(TARGET copy_shaders POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/shaders"
        $<TARGET_FILE_DIR:multik>/shaders)

add_custom_target(build_multik_shaders)
add_dependencies(build_multik_shaders multik copy_shaders)

