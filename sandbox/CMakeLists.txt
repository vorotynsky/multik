cmake_minimum_required(VERSION 2.8)

file(GLOB sandboxSrc "*.cpp")

add_executable(sandbox ${sandboxSrc})
target_link_libraries(sandbox multik)
include_directories(${CMAKE_SOURCE_DIR})
