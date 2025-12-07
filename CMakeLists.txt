cmake_minimum_required(VERSION 3.10)

project(TrieDatabase)

option(USE_ORDERED_MAP "Use std::map instead of std::unordered_map" OFF)

if(USE_ORDERED_MAP)
    add_compile_definitions(TRIE_USE_ORDERED_MAP)
    message(STATUS "Using std::map for Trie nodes")
else()
    message(STATUS "Using std::unordered_map for Trie nodes")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(trie_database src/main.cpp src/trie.cpp)

target_include_directories(trie_database PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
