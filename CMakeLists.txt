cmake_minimum_required(VERSION 3.1)
project(HUFFMAN)

set(CMAKE_CXX_STANDARD 11)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif ()


add_executable(HUFFMAN main.cpp lib/compressor.cpp lib/compressor.h lib/tree.cpp lib/tree.h lib/decoder.cpp lib/decoder.h lib/builder.cpp lib/builder.h)