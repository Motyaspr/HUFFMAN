#include <iostream>
#include <cstring>
#include "lib/compressor.h"
#include "lib/decoder.h"
#include<fstream>


const size_t SZ = 1;

void compress(std::string in, std::string out){
    std::ifstream input(in, std::ios::binary);
    if (!input.is_open()){
        std::__throw_runtime_error("wrong name of file");
    }
    size_t sz = 0;
    input.seekg(0, std::ios::end);
    sz = (input.tellg());
    std::ofstream output(out, std::ios::binary);
    if (sz == 0) {
       return;
    }

    input.seekg(0, std::ios::beg);
    compressor c;
    uint64_t cur_read = 0;
    std::vector<uint8_t> q;
    while(sz > cur_read){
        q.resize(std::min(SZ, sz - cur_read));
        input.read((char *) q.data(), q.size());
        c.add_block(q);
        cur_read += SZ;
    }
    c.do_all();
    std::vector<uint8_t> cur = c.get_tr();

    size_t sz1 = cur.size();
    output.write((char *) &sz1, sizeof(uint32_t));
    output.write((char*)cur.data(), sizeof(uint8_t)*c.get_tr().size());

    size_t sz2 = c.get_chars().size();
    output.write((char *) &sz2, sizeof(uint32_t));
    output.write((char*)c.get_chars().data(), sizeof(uint8_t)*c.get_chars().size());

    input.seekg(0, std::ios::beg);
    std::vector<uint8_t> decod;
    cur_read = 0;
    c.make_zero();
    uint64_t sz3 = c.calc_len();
    //sz3 = sz3 / 8 + (sz3 % 8 != 0);
    output.write((char *) &sz3, sizeof(sz3));
    while(sz > cur_read){
        q.resize(std::min(SZ, sz - cur_read));
        input.read((char *) q.data(), q.size());
        c.compress_block(q, decod);
        output.write((char *)decod.data(), sizeof(uint8_t)*decod.size());
        cur_read += SZ;
        decod.clear();
    }
    if (c.get_not_used() != 0) {
        output << c.get_last();
    }
}

void decode(std::string inputFileName, std::string outputFileName)
                                                                                                                                                                                                                                            {
    std::ifstream input(inputFileName, std::ios::binary);
    if (input.is_open() == false){
        std::__throw_runtime_error("wrong name of file");
    }

    uint64_t input_file_length;
    input.seekg(0, std::ios::end);
    input_file_length = input.tellg();
    if (input_file_length == 0)
        return;
    if (input_file_length < 21)
        std::__throw_runtime_error("can't decode this file");
    std::ofstream output(outputFileName, std::ios::binary);

    input.seekg(0, std::ios::beg);
    uint32_t sz1;
    std::vector<uint8_t> struc;

    input.read((char*)&sz1, sizeof(sz1));
    struc.resize(sz1);
    input.read((char*)struc.data(), (struc.size()) * sizeof(uint8_t));
    uint32_t sz2;
    input.read((char*)&sz2, sizeof(sz2));
    std::vector<uint8_t> symbs;
    symbs.resize(sz2);
    input.read((char*)symbs.data(), (symbs.size()) * sizeof(uint8_t));
    uint64_t need_read;
    input.read((char*)&need_read, sizeof(need_read));
    uint64_t was_read = static_cast<uint64_t>(input.tellg());
    std::vector <uint8_t> out;
    std::vector<uint8_t> cur;
    decoder d(symbs, struc);
    d.get_need(need_read);
    d.clear();
    d.make_tree();
    uint64_t readd = 0;
    while(was_read < input_file_length)
    {
        cur.resize(std::min(SZ, input_file_length-was_read));
        input.read((char *) cur.data(), cur.size());

        d.decode_block(cur, out);
        output.write((char*)out.data(), out.size());
        out.clear();
        was_read += cur.size();
        readd += cur.size();
    }
    if (d.get_need() != d.get_decoded())
        std::__throw_runtime_error("wrong text");

}

bool check(std::string s1, std::string s2){
    std::ifstream input(s1, std::ios::binary);
    input.seekg(0, std::ios::end);
    uint64_t len1 = input.tellg();
    input.seekg(0, std::ios::beg);
    std::vector<uint8_t> q;
    q.resize(len1);
    input.read((char *) q.data(), q.size());
    //string s2 = "/home/motyaspr/CLionProjects/HUFFMAN/tests/big_rand.huf";
    std::ifstream input1(s2, std::ios::binary);
    input1.seekg(0, std::ios::end);
    uint64_t len2 = input1.tellg();
    input1.seekg(0, std::ios::beg);
    std::vector<uint8_t> t;
    t.resize(len2);
    input1.read((char *) t.data(), t.size());
    std::cout << len1 << ' ' << len2 << "\n";
    if (t == q)
        std::cout << "URA";
    else
        std::cout << "(((";
}

int main(int argc, char* argv[]) {
    //std::string s1, s2;
    // std::cin >> s1 >> s2;
    //freopen("tests/a.in", "w", stdout);
    if (argc != 4) {
        std::cout << "wrong count of args";
        return 1;
    }
    if (strcmp(argv[1], "compress") != 0 && strcmp(argv[1], "decode") != 0) {
        std::cout << "wrong format of input";
        return 1;
    }
    if (strcmp(argv[1], "compress") == 0) {
        try {
            std::string s = argv[2];
            std::string s1 = argv[3];;
            compress(s, s1);
        } catch (...) {
            std::cout << "FAILED";
        }
    } else {
        try {
            std::string s = argv[2];
            std::string s1 = argv[3];
            decode(s, s1);
        } catch (...) {
            std::cout << "FAILED";
        }
    }
/*
    std::string s = "it1.huf";
    s = "/home/motyaspr/CLionProjects/HUFFMAN/tests/" + s;
    std::string s1 = "it1.in";
    s1 = "/home/motyaspr/CLionProjects/HUFFMAN/tests/" + s1;
    check(s, s1);*/
    return 0;
}