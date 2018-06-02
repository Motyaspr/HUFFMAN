//
// Created by motyaspr on 23.05.18.
//

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H


#include <stdint-gcc.h>
#include<vector>


class tree {
private:
    tree *l, *r, *p;
    std::vector<uint8_t> symbs;
    uint64_t weight;

    friend void dfs(tree *v, std::vector<uint8_t> &cur, std::vector<uint8_t> &a, std::vector<std::vector<uint8_t>> &codde);
    friend void cod(tree *v, std::vector<uint8_t > &cur);
    friend void build(tree *ntree, std::vector<uint8_t> &symbs, std::vector<uint8_t> &struc);
public:
    tree();
    tree(tree *l, tree *r, std::vector<uint8_t> _symbs, uint64_t _w);
    void merge_trees(tree *a, tree *b);
    uint64_t get_weight();
    tree* get_l();
    tree* get_r();
    uint8_t get_symb();
    std::vector<uint8_t> get_symbs();
    void clear();

};


#endif //HUFFMAN_TREE_H
