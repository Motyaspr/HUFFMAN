//
// Created by motyaspr on 23.05.18.
//

#include "compressor.h"
#include "tree.h"


void compressor::compress_block(std::vector<uint8_t> const &block, std::vector<uint8_t> &o_block) {
    for (uint8_t c : block) {
        size_t sz = code[c].size();
        size_t st = 0;
        if (sz >= 8 - not_used){
            for (size_t i = not_used; i < 8; i++)
                if (code[c][i - not_used] > 0)
                    last += (1 << (7 - i));
            o_block.push_back(last);
            st = static_cast<size_t>(8 - not_used);
            last = 0;
            sz -= (8 - not_used);
            not_used = 0;
        }
        while(sz >= 8){
            uint8_t cur = 0;
            for (size_t i = 0; i < 8; i++){
                if (code[c][i + st] > 0){
                    cur += (1 << (7 - i));
                }
            }
            o_block.push_back(cur);
            st += 8;
            sz -= 8;
        }
        if (sz != 0){
            for (size_t i = 0; i < sz; i++){
                if (code[c][i + st] > 0)
                    last += (1 << (7 - i - not_used));
            }
        }
        not_used += sz;
    }
}


std::vector<uint8_t> compressor::get_chars() {
    return chars;
}

std::vector<uint8_t> compressor::get_tr() {
    return tr;
}

size_t compressor::get_not_used(){
    return not_used;
}

uint8_t compressor::get_last() {
    return last;
}


uint64_t compressor::calc_len() {
    length = 0;
    for(size_t i = 0; i <= 255; i++){
        length += (uint64_t)(freq[i] * code[i].size());
    }
    return length;
}



compressor::compressor(builder &cop) : freq(cop.get_coun()), trees(cop.get_trees()), code(cop.get_code()), tr(cop.get_tr()), chars(cop.get_chars()) {

    leaves = static_cast<uint8_t>(chars.size());
    not_used = 0;
    last = 0;
}

compressor::~compressor() {
    delete trees;
}




