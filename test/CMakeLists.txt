function(plepa_test)
    set(options SKIPPED GTEST BENCHMARK)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES ARGS)
    cmake_parse_arguments(plepa_test "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    
    
    add_executable (${plepa_test_NAME} ${plepa_test_SOURCES})
    
    if (NOT ${PLEPA_SRC_EMPTY})
        target_link_libraries(${plepa_test_NAME} PRIVATE plepa)
    else()
        target_include_directories(${plepa_test_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
    endif (NOT ${PLEPA_SRC_EMPTY})

    if (plepa_test_GTEST)
        target_link_gtest(${plepa_test_NAME})
    endif (plepa_test_GTEST)
endfunction(plepa_test)

plepa_test(GTEST NAME tst_all SOURCES tst_all.cpp)
plepa_test(GTEST NAME tst_maybe SOURCES tst_maybe.cpp)
    
    
