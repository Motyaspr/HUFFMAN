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
public:
    builder() = default;
    void add_block(std::vector<uint8_t> q);
    std::vector<uint64_t> get_coun() const;

};


#endif //HUFFMAN_BUILDER_H
