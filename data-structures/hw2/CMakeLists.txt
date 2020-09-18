cmake_minimum_required(VERSION 3.8)
project(hw_wet2)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main2.cpp library2.h library2.cpp
        SplayRankTree.h SplayNode.h
        HashTable.h HashTable.cpp
        Colosseum.h
        Objects.h tests/dstest.h tests/rank_tree_test.cpp
        Exceptions.h tests/hash_table_test.cpp tests/heap_test.cpp
        Heap.h HeapNode.h)
add_executable(hw_wet2 ${SOURCE_FILES})