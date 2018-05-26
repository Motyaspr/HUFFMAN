//
// Created by motyaspr on 23.05.18.
//

#include <cstddef>
#include <utility>
#include "tree.h"
#include <cstdint>

tree::tree() {
    l = nullptr;
    r = nullptr;
}

void tree::merge_trees(tree *a, tree *b) {
    std::vector<uint8_t> cur = a->symbs;
    for (uint8_t symb : b->symbs)
        cur.push_back(symb);
    a->p = this;
    b->p = this;
    l = a;
    r = b;
    weight = l->weight + r->weight;
    symbs = cur;
}

tree::tree(tree *_l, tree *_r, std::vector<uint8_t> _symbs, uint64_t _w) : l(_l), r(_r), symbs(std::move(_symbs)), weight(_w){}

//bool operator<(tree const &a, tree const &b) {
//    return a.weight > b.weight;
//}

uint64_t tree::get_weight() {
    return weight;
}

void dfs(tree *v, std::vector<uint8_t> &cur, std::vector<uint8_t> &a, std::vector<std::vector<uint8_t>> &codde) {
    if (v->l != nullptr){
        cur.push_back(0);
        dfs(v->l, cur, a, codde);
        cur.pop_back();
        cur.push_back(1);
        dfs(v->r, cur, a,codde);
        cur.pop_back();
    }
    else if (v->r == nullptr){
        codde[v->symbs[0]] = cur;
        a.push_back(v->symbs[0]);
        return;
    }
}

void cod(tree *v, std::vector<uint8_t> &cur) {
    if (v->l != nullptr){
        cur.push_back(1);
        cod(v->l, cur);
        cur.push_back(0);
        cod(v->r, cur);
    }
}


void build(tree *ntree, std::vector<uint8_t> &symbs, std::vector<uint8_t> &struc) {
    size_t curind1 = 0;
    for (bool q : struc) {
        if (q){
            ntree->l = new tree();
            ntree->l->p = ntree;
            ntree = ntree->l;
        }
        else{
            if (curind1 == symbs.size())
                std::__throw_runtime_error("wrong tree");
            ntree->symbs.push_back(symbs[curind1++]);

            if (ntree->p == nullptr)
                std::__throw_runtime_error("wrong tree");
            ntree = ntree->p;
            while(ntree->r != nullptr && ntree->p != nullptr)
                ntree = ntree->p;
            ntree->r = new tree();
            ntree->r->p = ntree;
            ntree = ntree->r;
        }
    }
    ntree->symbs.push_back(symbs[curind1]);
    if (curind1 != symbs.size() - 1)
        std::__throw_runtime_error("Wrong tree");
}

tree *tree::get_l() {
    return this->l;
}

tree *tree::get_r() {
    return this->r;
}

uint8_t tree::get_symb() {
    return this->symbs[0];
}


