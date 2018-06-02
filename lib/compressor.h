//
// Created by motyaspr on 23.05.18.
//

#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H


#include <cstdint>
#include <vector>
#include <cstddef>
#include <algorithm>
#include "tree.h"
#include "builder.h"

class compressor {
private:
    std::vector<uint64_t> freq;
    uint64_t length;
    tree* trees;
    std::vector<std::vector<uint8_t>> code;
    std::vector<uint8_t> tr;
    uint8_t leaves;
    std::vector<uint8_t> chars;
    uint8_t last;
    size_t not_used;
public:
    compressor() = default;
    compressor(builder &cop);
    ~compressor();
    uint64_t calc_len();
    std::vector<uint8_t> get_chars();
    std::vector<uint8_t> get_tr();
    size_t get_not_used();
    uint8_t get_last();
    void compress_block(std::vector<uint8_t> const &block, std::vector<uint8_t> &out);
};


#endif //HUFFMAN_COMPRESSOR_H
