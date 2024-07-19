#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_hex(const char* label, const uint8_t* v, size_t len) {
    size_t i;
    printf("%s: ", label);
    for (i = 0; i < len; ++i) {
        printf("%02x", v[i]);
    }
    printf("\n");
}

// 十六进制字符转成uint8
uint8_t hex2byte(const char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a';
    }
    return 0;
}

// 把十六进制字符串转成uint8数组
void parse_hex(uint8_t* v, const char* str) {
    const size_t count = strlen(str) / 2;
    size_t i;
    for (i = 0; i < count; ++i) {
        const char hi = hex2byte(str[i * 2]);
        const char lo = hex2byte(str[i * 2 + 1]);
        v[i] = hi * 16 + lo;
    }
}

uint8_t* alloc_hex(const char* str, size_t* len) {
    const size_t count = strlen(str) / 2;
    size_t i;
    uint8_t* v = malloc(count);
    for (i = 0; i < count; ++i) {
        const char hi = hex2byte(str[i * 2]);
        const char lo = hex2byte(str[i * 2 + 1]);
        v[i] = hi * 16 + lo;
    }

    *len = count;

    return v;
}

#endif //COMMON_H
