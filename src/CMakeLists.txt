aux_source_directory(. SRC_LIST)
file(GLOB_RECURSE INC_LIST ../plepa/*.h)

if (SRC_LIST)
    set(PLEPA_SRC_EMPTY OFF)
    add_library(plepa ${SRC_LIST} ${INC_LIST})
    target_include_directories(plepa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
else()
    set(PLEPA_SRC_EMPTY ON)
    # to add header files to project
    add_custom_target(_headers SOURCES ${INC_LIST})
endif()

