//
// Created by motyaspr on 24.05.18.
//

#ifndef HUFFMAN_DECODER_H
#define HUFFMAN_DECODER_H


#include <cstdint>
#include <vector>
#include "tree.h"
#include <unordered_map>

class decoder {
private:
    std::vector<uint8_t> chars;
    std::vector<uint8_t> struct_tree;
    std::vector<std::vector<uint8_t>> cod;
    uint64_t decoded, need;
    std::vector<bool> last;
    tree *ntree;
    bool is_f;
public:
    decoder() = default;
    decoder(std::vector<uint8_t> _chars, std::vector<uint8_t> _struct);
    ~decoder();
    void decode_block(std::vector<uint8_t> &block, std::vector<uint8_t> &out);

    void get_need(uint64_t t);

    uint64_t get_decoded();
    uint64_t get_need();

};


#endif //HUFFMAN_DECODER_H