cmake_minimum_required(VERSION 3.14)

project(TW VERSION 0.1.0 DESCRIPTION "A Tween library written in C" LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_compile_definitions($<$<CONFIG:Debug>:DEBUG>)
add_compile_definitions($<$<CONFIG:Release>:NDEBUG>)

include_directories(Source)

set(TW_TW_FOLDER ${TW_SOURCE_DIR}/Source/Tw)
set(TW_SCRIPT_FOLDER ${TW_SOURCE_DIR}/Scripts)

include(${TW_SCRIPT_FOLDER}/TwCopyFiles.cmake)
TwCopyFiles(${TW_TW_FOLDER} ${TW_BINARY_DIR}/include/Tw "*.h" "--" "TW_BIN_HEADERS")

## Libraries ------------------------------

add_library(tw SHARED
    Source/Tw/tw-types.h
    Source/Tw/tw-functions.c
    Source/Tw/tw-instance.c
    Source/Tw/tw-easing.c
    Source/Tw/tw-thread.c
    Source/tinycthread/tinycthread.c
)

target_link_libraries(tw
    PRIVATE m
)

## Executables ------------------------------

add_executable(tw-sample-loop
    Source/Samples/simple-loop.c
)

target_link_libraries(tw-sample-loop
    PRIVATE tw
)

add_executable(tw-sample-thread
    Source/Samples/simple-thread.c
)

target_link_libraries(tw-sample-thread
    PRIVATE tw
)

## Generate Export Header -----------------

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
include(GenerateExportHeader)
generate_export_header(tw)
set(SRC_EXPORT_FILE ${TW_BINARY_DIR}/tw_export.h)
set(DST_EXPORT_FILE ${TW_TW_FOLDER}/tw_export.h)
include(${TW_SCRIPT_FOLDER}/TwCopyFile.cmake)
TwCopyFile(${SRC_EXPORT_FILE} ${DST_EXPORT_FILE})

## Custom Targets --------------------------------
add_custom_target(custom-copy-headers DEPENDS ${TW_BIN_HEADERS} )
add_dependencies(tw custom-copy-headers)

add_custom_target(custom-copy-export DEPENDS ${DST_EXPORT_FILE} )
add_dependencies(custom-copy-headers custom-copy-export)
