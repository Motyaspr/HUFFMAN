cmake_minimum_required(VERSION 3.10)
project(HUFFMAN)

set(CMAKE_CXX_STANDARD 11)

add_executable(HUFFMAN main.cpp lib/compressor.cpp lib/compressor.h lib/tree.cpp lib/tree.h lib/decoder.cpp lib/decoder.h check_two_files.cpp)