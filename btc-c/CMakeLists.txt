cmake_minimum_required(VERSION 3.2)
project(btc_c C)

set(CMAKE_C_STANDARD 11)

add_executable(btc main.c
        common.h)
