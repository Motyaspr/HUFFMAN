//
// Created by motyaspr on 26.05.18.
//

#include "counter.h"

void counter::add_block(std::vector<uint8_t> q) {
    if (coun.size() == 0)
        coun.resize(256);
    for (uint8_t i : q)
        coun[i]++;
}

std::vector<uint64_t> counter::get_coun() {
    return coun;
}

std::vector<uint64_t> counter::get_coun() const {
    return coun;
}
