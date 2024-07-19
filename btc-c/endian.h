#ifndef ENDIAN_H
#define ENDIAN_H
#include <stdint.h>
#include <string.h>

typedef enum {
    ENDIAN_BIG,
    ENDIAN_LITTLE
} endian_t;

endian_t host_endian() {
    static const union {
        uint16_t i;
        uint8_t c[2];
    }test = {0x1234};

    return test.c[0] == 0x12 ? ENDIAN_BIG : ENDIAN_LITTLE;
}

uint16_t swap16(uint16_t n) {
    return n >> 8 |
           (n & 0xff) << 8;
}

uint32_t swap32(uint32_t n) {
    return n >> 24 |
           (n & 0xff0000) >> 8 |
           (n & 0xff00) << 8 |
           (n & 0xff) << 24;
}

uint64_t swap64(uint64_t n) {
    return n >> 56 |
        (n & 0xff000000000000) >> 40 |
        (n & 0xff0000000000) >> 24 |
        (n & 0xff00000000) >> 8 |
        (n & 0xff000000) << 8 |
        (n & 0xff0000) << 24 |
        (n & 0xff00) << 48 |
        (n & 0xff) << 56;
}

uint16_t endian16(endian_t e, uint16_t n) {
    if (host_endian() == e) {
        return n;
    }
    return swap16(n);
}

uint32_t endian32(endian_t e, uint32_t n) {
    if (host_endian() == e) {
        return n;
    }
    return swap32(n);
}

uint64_t endian64(endian_t e, uint64_t n) {
    if (host_endian() == e) {
        return n;
    }
    return swap64(n);
}

void reverse(uint8_t* dst, size_t len) {
    size_t i;
    const size_t stop = len >> 1;
    for (i = 0; i < stop; ++i) {
        uint8_t* left = dst + i;
        uint8_t* right = dst + len - i - 1;
        const uint8_t tmp = *left;
        *left = *right;
        *right = tmp;
    }
}


#endif //ENDIAN_H
