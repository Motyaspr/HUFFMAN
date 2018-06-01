//
// Created by motyaspr on 01.06.18.
//

#include <algorithm>
#include "builder.h"
#include "tree.h"

tree *t;

bool cmp(tree *a, tree *b){
    return a->get_weight() > b->get_weight();
}

void builder::add_block(std::vector<uint8_t> q, bool f) {
    if (coun.empty())
        coun.resize(256);
    for (uint8_t i : q)
        coun[i]++;
    if (!f)
        return;
    for (size_t i = 0; i < 256; i++){
        if (coun[i] > 0){
            std::vector<uint8_t> cur;
            cur.push_back((uint8_t)i);
            t = new tree(nullptr, nullptr, cur, coun[i]);
            trees.push_back(t);
        }
    }
    std::sort(trees.begin(), trees.end(), cmp);
    create_tree();
    create_code();
}

void builder::create_tree() {
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

void builder::create_code() {
    code.resize(256);
    std::vector<uint8_t> cur;
    dfs(trees[0], cur, chars, code);
    cod(trees[0], tr);
}

std::vector<uint8_t> builder::get_chars() const{
    return chars;
}

std::vector<tree *> builder::get_trees() const{
    return trees;
}

std::vector<std::vector<uint8_t>> builder::get_code() const{
    return code;
}

std::vector<uint8_t> builder::get_tr() const {
    return tr;
}

std::vector<uint64_t> builder::get_coun() const {
    return coun;
}




