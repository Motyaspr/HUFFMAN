//
// Created by motyaspr on 01.06.18.
//

#ifndef HUFFMAN_BUILDER_H
#define HUFFMAN_BUILDER_H


#include <cstdint>
#include <vector>
#include "tree.h"

class builder {
private:
    std::vector<uint64_t> coun;
    std::vector<std::vector<uint8_t>> code;
    std::vector<uint8_t> tr;
    std::vector<tree*> trees;
    void create_tree();
    std::vector<uint8_t> chars;
    void create_code();
public:
    builder() = default;
    void add_block(std::vector<uint8_t> q, bool is_last);
    std::vector<uint8_t> get_chars() const;
    tree* get_trees() const;
    std::vector<std::vector<uint8_t>> get_code() const;
    std::vector<uint8_t> get_tr() const ;
    std::vector<uint64_t> get_coun() const;

};


#endif //HUFFMAN_BUILDER_H
