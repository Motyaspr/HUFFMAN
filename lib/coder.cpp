//
// Created by motyaspr on 26.05.18.
//

#include <algorithm>
#include "coder.h"

tree *t;

bool cmp(tree *a, tree *b){
    return a->get_weight() > b->get_weight();
}

coder::coder(counter const &cop) {
    freq = cop.get_coun();
    for (size_t i = 0; i < 256; i++){
        if (freq[i] > 0){
            std::vector<uint8_t> cur;
            cur.push_back((uint8_t)i);
            t = new tree(nullptr, nullptr, cur, freq[i]);
            trees.push_back(t);
        }
    }
    std::sort(trees.begin(), trees.end(), cmp);
    create_tree();
    create_code();
}

void coder::create_tree() {
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
        if (trees.empty()) {
            trees.push_back(r);
            continue;
        }
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

void coder::create_code() {
    code.resize(256);
    std::vector<uint8_t> cur;
    dfs(trees[0], cur, chars, code);
    cod(trees[0], tr);
}

std::vector<uint8_t> coder::get_chars() {
    return chars;
}

std::vector<tree *> coder::get_trees() {
    return trees;
}

std::vector<std::vector<uint8_t>> coder::get_code() {
    return code;
}

std::vector<uint8_t> coder::get_tr() {
    return tr;
}
