/*#include<bits/stdc++.h>

using namespace std;

int main(){
    string s1 = "/home/motyaspr/CLionProjects/HUFFMAN/tests/big_rand.in";
    ifstream input(s1, ios::binary);
    input.seekg(0, std::ios::end);
    uint64_t len1 = input.tellg();
    input.seekg(0, std::ios::beg);
    std::vector<uint8_t> q;
    q.resize(len1);
    input.read((char *) q.data(), q.size());
    string s2 = "/home/motyaspr/CLionProjects/HUFFMAN/tests/big_rand.huf";
    ifstream input1(s2, ios::binary);
    input1.seekg(0, std::ios::end);
    uint64_t len2 = input1.tellg();
    input1.seekg(0, std::ios::beg);
    std::vector<uint8_t> t;
    t.resize(len2);
    input1.read((char *) t.data(), t.size());
    std::cout << len1 << ' ' << len2 << "\n";
    if (t == q)
        cout << "URA";
    else
        cout << "(((";

}*/