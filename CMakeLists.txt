cmake_minimum_required(VERSION 4.0.1)

project(nitro)

set(CMAKE_CXX_STANDARD 20)

add_executable(nitro src/main.cpp
        src/tokenization.hpp)