//
// Created by motyaspr on 26.05.18.
//

#ifndef HUFFMAN_COUNTER_H
#define HUFFMAN_COUNTER_H

#include<vector>
#include <cstdint>

class counter {
private:
    std::vector<uint64_t> coun;
public:
    counter() = default;
    void add_block(std::vector<uint8_t> q);
    std::vector<uint64_t> get_coun();
    std::vector<uint64_t> get_coun() const;
};


#endif //HUFFMAN_COUNTER_H
