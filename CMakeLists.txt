cmake_minimum_required(VERSION 3.14)

project(TW VERSION 0.1.0 DESCRIPTION "A Tween library written in C" LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_compile_definitions($<$<CONFIG:Debug>:DEBUG>)
add_compile_definitions($<$<CONFIG:Release>:NDEBUG>)

include_directories(Source)
