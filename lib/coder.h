//
// Created by motyaspr on 26.05.18.
//

#ifndef HUFFMAN_CODER_H
#define HUFFMAN_CODER_H
#include "counter.h"
#include <vector>
#include "tree.h"


class coder {
private:
    std::vector<std::vector<uint8_t>> code;
    std::vector<uint8_t> tr;
    uint8_t leaves;
    std::vector<uint8_t> chars;
    std::vector<uint64_t> freq;
    std::vector<tree*> trees;
    void create_tree();
    void create_code();
public:
    coder() = default;
    coder(counter const &cop);
    std::vector<uint8_t> get_chars();
    std::vector<tree*> get_trees();
    std::vector<std::vector<uint8_t>> get_code();
    std::vector<uint8_t> get_tr();
};


#endif //HUFFMAN_CODER_H
