cmake_minimum_required(VERSION 3.1)
project(HUFFMAN)

set(CMAKE_CXX_STANDARD 11)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -pedantic -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif ()

add_library(huflib STATIC lib/builder.h
        lib/decoder.h lib/compressor.h
        lib/tree.h lib/decoder.cpp lib/builder.cpp lib/tree.cpp lib/compressor.cpp)

include_directories(lib)

add_executable(HUFFMAN main.cpp)

target_link_libraries(HUFFMAN huflib -lpthread)