cmake_minimum_required(VERSION 3.0)
enable_testing()

project(plepa CXX)

set(CMAKE_CXX_STANDARD 14)


function(target_link_gtest target)
    target_link_libraries(${target} PUBLIC gtest)
endfunction(target_link_gtest)


if (NOT GTEST_SRC)
    message(WARNING "Please set gtest source path to GTEST_SRC variable!")
else()
    add_library(gtest ${GTEST_SRC}/src/gtest-all.cc ${GTEST_SRC}/src/gtest_main.cc)
    find_package(Threads)
    target_link_libraries(gtest Threads::Threads)
    target_include_directories(gtest PRIVATE ${GTEST_SRC} PUBLIC ${GTEST_SRC}/include)
endif()

add_subdirectory(src)
add_subdirectory(test)

