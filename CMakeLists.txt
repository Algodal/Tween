cmake_minimum_required(VERSION 3.14)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE BOOL "Suppress warnings from external projects")

project(TW VERSION 1.0.0 DESCRIPTION "A Tween library written in C" LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_compile_definitions($<$<CONFIG:Debug>:DEBUG>)
add_compile_definitions($<$<CONFIG:Release>:NDEBUG>)

include_directories(Source)

set(TW_TW_FOLDER ${TW_SOURCE_DIR}/Source/Tw)
set(TW_SCRIPT_FOLDER ${TW_SOURCE_DIR}/Scripts)

configure_file(${TW_SCRIPT_FOLDER}/twVersion.h.in ${TW_TW_FOLDER}/twVersion.h)

include(${TW_SCRIPT_FOLDER}/TwCopyFiles.cmake)
TwCopyFiles(${TW_TW_FOLDER} ${TW_BINARY_DIR}/include/Tw "*.h" "--" "TW_BIN_HEADERS")

## Libraries ------------------------------
include(FetchContent)

FetchContent_Declare(
    tinycthread
    GIT_REPOSITORY https://github.com/tinycthread/tinycthread.git
    GIT_TAG master
)

FetchContent_MakeAvailable(tinycthread)

add_library(tinycthread-lib STATIC
    ${tinycthread_SOURCE_DIR}/source/tinycthread.c
)

target_include_directories(tinycthread-lib PUBLIC
    ${tinycthread_SOURCE_DIR}/source
)

add_library(tw SHARED
    Source/Tw/twTypes.h
    Source/Tw/twEasing.c
    Source/Tw/TwTween.c
    Source/Tw/twExport.h
    Source/Tw/twVersion.h
)

target_link_libraries(tw
    PRIVATE m
    PRIVATE tinycthread-lib
)

## Executables ------------------------------

add_executable(run_job
    Source/Samples/run_job.c
)

target_link_libraries(run_job
    PRIVATE tw
)

add_executable(alloc_job
    Source/Samples/alloc_job.c
)

target_link_libraries(alloc_job
    PRIVATE tw
)

add_executable(state
    Source/Samples/state.c
)

target_link_libraries(state
    PRIVATE tw
)

option(ENABLE_SDL_SAMPLES "Build SDL2-based samples" OFF)

if(TARGET build-samples OR ENABLE_SDL_SAMPLES)
    message(STATUS "Configuring SDL2 samples...")

    # Avoid SDL2d.dll, use SDL2.dll in all configurations
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)

    include(FetchContent)

    FetchContent_Declare(
      SDL2
      GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
      GIT_TAG release-2.28.5 # Or latest stable tag
    )

    FetchContent_MakeAvailable(SDL2)

    # Add SDL2-based sample executables
    add_executable(state_sdl
        Source/Samples/state_sdl.c
    )
    target_link_libraries(state_sdl
        PRIVATE tw SDL2::SDL2
    )

    add_executable(job_sdl
        Source/Samples/job_sdl.c
    )
    target_link_libraries(job_sdl
        PRIVATE tw SDL2::SDL2
    )

    # Add these targets to the build-samples custom target
    add_dependencies(build-samples
        state_sdl
        job_sdl
    )

    set_target_properties(state_sdl PROPERTIES EXCLUDE_FROM_ALL TRUE)
    set_target_properties(job_sdl PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif()

## Custom Target: Group All Sample Executables ------------------

add_custom_target(build-samples
    COMMENT "Build all sample executables"
)

# Add all sample executables to this group, but not to ALL
add_dependencies(build-samples
    run_job
    alloc_job
    state
    state_sdl
    job_sdl
)

set_target_properties(run_job PROPERTIES EXCLUDE_FROM_ALL TRUE)
set_target_properties(alloc_job PROPERTIES EXCLUDE_FROM_ALL TRUE)
set_target_properties(state PROPERTIES EXCLUDE_FROM_ALL TRUE)
set_target_properties(state_sdl PROPERTIES EXCLUDE_FROM_ALL TRUE)
set_target_properties(job_sdl PROPERTIES EXCLUDE_FROM_ALL TRUE)



## Generate Export Header -----------------

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
include(GenerateExportHeader)
generate_export_header(tw
    BASE_NAME "tw"
    EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/twExport.h"
)
set(SRC_EXPORT_FILE ${TW_BINARY_DIR}/twExport.h)
set(DST_EXPORT_FILE ${TW_TW_FOLDER}/twExport.h)
include(${TW_SCRIPT_FOLDER}/TwCopyFile.cmake)
TwCopyFile(${SRC_EXPORT_FILE} ${DST_EXPORT_FILE})

## Custom Targets --------------------------------
add_custom_target(custom-copy-headers DEPENDS ${TW_BIN_HEADERS} )
add_dependencies(tw custom-copy-headers)

add_custom_target(custom-copy-export DEPENDS ${DST_EXPORT_FILE} )
add_dependencies(custom-copy-headers custom-copy-export)
