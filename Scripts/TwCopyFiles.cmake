function(TwCopyFiles SRC_FOLDER DST_FOLDER KEEP_PATTERN DISCARD_PATTERN FILES_OUTPUT)
message(STATUS "Copying Files from ${SRC_FOLDER} to ${DST_FOLDER}")
file(GLOB_RECURSE SRC_FOLDER_FILES ${SRC_FOLDER}/${KEEP_PATTERN})
set(SRC_FOLDER_COPIED_FILES)
foreach(_hdr IN LISTS SRC_FOLDER_FILES)
  if(${_hdr} MATCHES "${DISCARD_PATTERN}") #DISCARD_PATTERN as null-string causes undefined behaviour
    list(REMOVE_ITEM SRC_FOLDER_FILES "${_hdr}")
  else()
    cmake_path(RELATIVE_PATH _hdr BASE_DIRECTORY "${SRC_FOLDER}" OUTPUT_VARIABLE _name)
    set(_bin_hdr "${DST_FOLDER}/${_name}")
    list(APPEND SRC_FOLDER_COPIED_FILES "${_bin_hdr}")
    add_custom_command(OUTPUT "${_bin_hdr}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_hdr}" "${_bin_hdr}"
        DEPENDS "${_hdr}")
  endif()
endforeach()
set(${FILES_OUTPUT} ${SRC_FOLDER_COPIED_FILES} PARENT_SCOPE)
endfunction()