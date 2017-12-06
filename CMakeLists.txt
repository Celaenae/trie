cmake_minimum_required(VERSION 3.9)
project(trie)

set(CMAKE_CXX_STANDARD 17)

add_executable(trie main.cpp trie.h trieNode.h)