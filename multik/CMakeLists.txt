cmake_minimum_required(VERSION 2.8)


add_compile_definitions(GLEW_STATIC)

file(GLOB multikSrc
    "*/*.hpp"
    "*/*.cpp"
    "main.cpp")

add_executable(multik ${multikSrc})

include_directories(glfw3 ${GLUT_INCLUDE_DIRS})

target_link_libraries(multik glheader)

add_custom_target(copy_shaders)
add_custom_command(TARGET copy_shaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/shaders"
    $<TARGET_FILE_DIR:multik>/shaders)

add_custom_target(build_multik_shaders)
add_dependencies(build_multik_shaders multik copy_shaders)

