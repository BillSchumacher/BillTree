cmake_minimum_required(VERSION 3.17)
project(libbilltree C)

set(CMAKE_C_STANDARD 99)

add_library(libbilltree SHARED src/libbilltree/libbilltree.c src/libbilltree/libbilltree.h)