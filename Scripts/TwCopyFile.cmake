function(TwCopyFile SRC_FILE DST_FILE)
message(STATUS "Copying ${SRC_FILE} to ${DST_FILE}")
add_custom_command(OUTPUT ${DST_FILE}
        COMMAND ${CMAKE_COMMAND} 
        -E copy_if_different ${SRC_FILE} ${DST_FILE}
        DEPENDS ${SRC_FILE})
endfunction()
