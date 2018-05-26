//
// Created by motyaspr on 23.05.18.
//

#include "compressor.h"
#include "tree.h"

void compressor::add_block(std::vector<uint8_t> const &new_block) {
    if (counter.empty())
        counter.resize(256);
    for (uint8_t i : new_block)
        counter[i]++;
}

std::vector<uint64_t> compressor::get_counter() {
    return counter;
}

bool cmp(tree *a, tree *b){
    return a->get_weight() > b->get_weight();
}

void compressor::prepare_trees() {
    for (size_t i = 0; i < 256; i++){
        if (counter[i] > 0){
            std::vector<uint8_t> cur;
            cur.push_back((uint8_t)i);
            tree *t = new tree(nullptr, nullptr, cur, counter[i]);
            trees.push_back(t);
        }
    }
    std::sort(trees.begin(), trees.end(), cmp);
    leaves = static_cast<uint8_t>(trees.size());
}

void compressor::create_tree() {
    if (trees.size() == 1){
        tree* cur = trees[0];
        trees.push_back(cur);
    }
    while(trees.size() > 1){
        tree* q = trees.back();
        trees.pop_back();
        tree* w = trees.back();
        trees.pop_back();
        tree* r = new tree();
        r->merge_trees(q, w);
        if ((*trees.begin())->get_weight() < r->get_weight()){
            trees.insert(trees.begin(), r);
            continue;
        }
        auto it = trees.end();
        bool f = false;
        for (it--; it != trees.begin(); it--){
            if ((*it)->get_weight() >= r->get_weight()){
                trees.insert(it, r);
                f = true;
                break;
            }
        }
        if (!f)
        {
            it++;
            trees.insert(it, r);
        }
    }
}

void compressor::create_code() {
    code.resize(256);
    std::vector<uint8_t> cur;
    dfs(trees[0], cur, chars, code);
    cod(trees[0], tr);
}

uint8_t compressor::get_leaves() {
    return leaves;
}

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

void compressor::do_all() {
    prepare_trees();
    create_tree();
    create_code();

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


void compressor::make_zero() {
    this->not_used = 0;
    this->last = 0;
}

uint64_t compressor::calc_len() {
    length = 0;
    for(size_t i = 0; i <= 255; i++){
        length += (uint64_t)(counter[i] * code[i].size());
    }
    return length;
}





