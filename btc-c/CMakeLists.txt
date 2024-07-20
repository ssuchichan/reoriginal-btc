cmake_minimum_required(VERSION 3.2)
project(btc_c C)
find_package(OpenSSL REQUIRED)

set(CMAKE_C_STANDARD 11)

add_executable(btc main.c
        varint.h)
add_executable(test test.c
        varint.h)
# openssl包含两个库
# libcrypto: 加解密算法库
# libssl：加密模块应用库，实现了ssl及tls
target_link_libraries(btc crypto)
target_link_libraries(test crypto)
