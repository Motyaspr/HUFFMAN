//
// Created by motyaspr on 01.06.18.
//

#include <algorithm>
#include "builder.h"
#include "tree.h"


void builder::add_block(std::vector<uint8_t> q) {
    if (coun.empty())
        coun.resize(256);
    for (uint8_t i : q)
        coun[i]++;
}


std::vector<uint64_t> builder::get_coun() const {
    return coun;
}




