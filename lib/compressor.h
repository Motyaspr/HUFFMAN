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

class compressor {
private:
    std::vector<uint64_t> counter;
    uint64_t length;
    std::vector<tree*> trees;
    std::vector<std::vector<uint8_t>> code;
    std::vector<uint8_t> tr;
    uint8_t leaves;
    std::vector<uint8_t> chars;
    uint8_t last;
    size_t not_used;
public:
    compressor() = default;
    std::vector<uint64_t> get_counter();
    uint64_t calc_len();
    std::vector<uint8_t> get_chars();
    std::vector<uint8_t> get_tr();
    void add_block(std::vector<uint8_t> const &new_block);
    void prepare_trees();
    void create_tree();
    void create_code();
    void do_all();
    size_t get_not_used();
    uint8_t get_last();
    void make_zero();
    uint8_t get_leaves();
    void compress_block(std::vector<uint8_t> const &block, std::vector<uint8_t> &out);
};


#endif //HUFFMAN_COMPRESSOR_H
