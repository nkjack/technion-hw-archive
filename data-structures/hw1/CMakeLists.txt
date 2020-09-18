cmake_minimum_required(VERSION 3.8)
project(hw_w1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main1.cpp library1.h SplayTree.cpp SplayTree.h list.h Node.h)
add_executable(hw_w1 ${SOURCE_FILES})