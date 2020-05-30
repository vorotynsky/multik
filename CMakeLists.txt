cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)

project(multik)

set(CMAKE_EXECUTABLE_SUFFIX ".exe")

add_subdirectory(cmake/glheader)
add_subdirectory(multik)
add_subdirectory(sandbox)

set (SHADER_TARGET sandbox)

add_custom_target(copy_shaders)
add_custom_command(TARGET copy_shaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/shaders"
    $<TARGET_FILE_DIR:${SHADER_TARGET}>/shaders)
