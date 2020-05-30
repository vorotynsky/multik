cmake_minimum_required(VERSION 2.8)

add_executable(sandbox "Sandbox.cpp")
target_link_libraries(sandbox multik)
include_directories(${CMAKE_SOURCE_DIR})
