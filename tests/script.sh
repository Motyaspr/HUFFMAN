#!/usr/bin/env bash

echo -e "\n\nTesting correctness: big file"
../cmake-build-release/HUFFMAN compress big_test.in big_test.huf
../cmake-build-release/HUFFMAN decode big_test.huf big_test.out
if cmp big_test.in big_test.out ;
then
        echo Test passed
else
        echo Test failed
        exit
fi

echo -e "\nTesting correctness: empty_test"
../cmake-build-release/HUFFMAN compress empty_test.in empty_test.huf
../cmake-build-release/HUFFMAN decode empty_test.huf empty_test.out
if cmp empty_test.in empty_test.out ;
then
        echo Test passed 
else
        echo Test failed
        exit
fi

echo -e "\nTesting correctness: small file"
../cmake-build-release/HUFFMAN compress small_test.in small_test.huf
../cmake-build-release/HUFFMAN decode small_test.huf small_test.out
if cmp small_test.in small_test.out ;
then
        echo Test passed 
else
        echo Test failed
        exit
fi

echo -e "\nTesting correctness: one_a_test"
../cmake-build-release/HUFFMAN compress one_a_test.in one_a_test.huf
../cmake-build-release/HUFFMAN decode one_a_test.huf one_a_test.out
if cmp one_a_test.in one_a_test.out ;
then
        echo Test passed
else
        echo Test failed
        exit
fi


echo -e "\nTesting correctness: corrupted file"
../cmake-build-release/HUFFMAN compress small_file.in small_file.huf
echo "kek" >> small_file.huf
../cmake-build-release/HUFFMAN decode small_file.huf small_file.out
echo -e "\nTest passed"

echo -e "\nTesting correctness: wrong argments number"
../cmake-build-release/HUFFMAN small_file.in small_file.huf
echo -e "\nTest passed"

echo -e "\nTesting correctness: wrong arguments"
../cmake-build-release/HUFFMAN 950541 small_file.in small_file.huf
echo -e "\nTest passed"
