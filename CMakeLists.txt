cmake_minimum_required(VERSION 3.10)

project(TrieDatabase)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/trie.cpp
)

add_executable(TrieDatabase ${SOURCES})
