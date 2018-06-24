cmake_minimum_required(VERSION 3.10)
project(assembler)

set(CMAKE_CXX_STANDARD 17)

add_executable(assembler main.cpp Assembler.cpp Assembler.h)