//
// Created by motyaspr on 24.05.18.
//

#include "decoder.h"
#include "tree.h"
#include <utility>
#include <cstddef>


decoder::decoder(std::vector<uint8_t> _chars, std::vector<uint8_t> _struct) : chars(std::move(_chars)), struct_tree(
        std::move(_struct)) {
}

void decoder::make_code() {
    cod.resize(256);
    size_t cur_ind = 0;
    std::vector<uint8_t> cur;
    size_t ind2 = 0;
    while(cur_ind < struct_tree.size()){
        if (struct_tree[cur_ind] == 1){
            cur.push_back(1);
            cur_ind++;
        }
        else{
            cod[chars[ind2++]] = cur;
            //mp[cur] = chars[ind2 - 1];
            while(!cur.empty() && cur.back() == 0)
                cur.pop_back();
            cur.pop_back();
            cur.push_back(0);
            cur_ind++;
        }
    }
    //mp[cur] = chars[ind2];
}

void decoder::make_tree() {
    ntree = new tree();
    build(ntree, chars, struct_tree);
}

void decoder::decode_block(std::vector<uint8_t> const &block, std::vector<uint8_t> &out) {
    while(ntree->get_p() != nullptr)
        ntree = ntree->get_p();
    tree *cur = ntree;
    bool is_first = true;
    for (size_t q = 0; q < block.size(); q++) {
        uint8_t i = block[q];
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
                cur = ntree;
                if (need == decoded){
                    return;
                }
            }
        }
        is_first = false;
        bool f = false;
        while (j >= 0) {
            last.push_back((bool) ((i >> j) & 1));
            j--;
            if (!last.back())
                cur = cur->get_l();
            else
                cur = cur->get_r();
            if (cur->get_r() == nullptr) {
                out.push_back(cur->get_symb());
                decoded += last.size();
                last.clear();
                cur = ntree;
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

void decoder::clear() {
    decoded = 0;

}

uint64_t decoder::get_decoded() {
    return decoded;

}

uint64_t decoder::get_need() {
    return need;
}
