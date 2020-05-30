cmake_minimum_required(VERSION 2.8)


add_compile_definitions(GLEW_STATIC)

file(GLOB multikSrc
    "*/*.hpp"
    "*/*.cpp"
    "*/*/*.hpp"
    "*/*/*.cpp"
    "entry.?pp")

add_library(multik ${multikSrc})

target_link_libraries(multik glheader)
