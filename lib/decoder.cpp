//
// Created by motyaspr on 24.05.18.
//

#include "decoder.h"
#include "tree.h"
#include <utility>
#include <cstddef>

decoder::decoder(std::vector<uint8_t> _chars, std::vector<uint8_t> _struct) : chars(_chars), struct_tree(_struct) {
    decoded = 0;
    is_f = true;
    build(&ntree, chars, struct_tree);
}

void decoder::decode_block(std::vector<uint8_t> &block, std::vector<uint8_t> &out) {
    tree *cur = &ntree;
    bool is_first = true;
    for (unsigned char i : block) {
        int j = 7;
        if (!last.empty()) {
            bool f = false;
            if (is_first) {
                for (auto &&t : last) {
                    if (!t)
                        cur = cur->get_l();
                    else
                        cur = cur->get_r();
                }
            }
            is_first = false;
            while (j >= 0) {
                last.push_back(((bool) ((i >> j) & 1)));
                if (!last.back())
                    cur = cur->get_l();
                else
                    cur = cur->get_r();

                j--;
                if (cur->get_r() == nullptr) {
                    f = true;
                    break;
                }
            }
            if (f) {
                out.push_back(cur->get_symb());
                decoded += last.size();
                last.clear();
                cur = &ntree;
                if (need == decoded){
                    return;
                }
            }
        }
        is_first = false;
        while (j >= 0) {
            last.push_back(static_cast<bool>((i >> j) & 1));
            j--;
            if (!last.back())
                cur = cur->get_l();
            else
                cur = cur->get_r();
            if (cur->get_r() == nullptr) {
                out.push_back(cur->get_symb());
                decoded += last.size();
                last.clear();
                cur = &ntree;
                if (need == decoded){
                    return;
                }
            }
        }
    }

}

void decoder::get_need(uint64_t t) {
    need = t;

}

uint64_t decoder::get_decoded() {
    return decoded;

}

uint64_t decoder::get_need() {
    return need;
}