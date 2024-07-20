#ifndef VARINT_H
#define VARINT_H

#include <stdint.h>
#include <stddef.h>
#include "endian.h"

typedef enum {
    VARINT16 = 0xfd,
    VARINT32 = 0xfe,
    VARINT64 = 0xff,
} varint_t;

// varint转整数
uint64_t varint_get(uint8_t* bytes, size_t *len) {
    uint8_t prefix = *bytes;
    uint64_t value = 0;
    *len = sizeof(uint8_t);
    if (prefix < VARINT16) {
        value = prefix;
    }
    else {
        uint8_t* ptr = bytes + *len;
        switch (prefix) {
            case VARINT16:
                value = endian16(ENDIAN_LITTLE, *(uint16_t*)ptr);
                *len += sizeof(uint16_t);
                break;
            case VARINT32:
                value = endian32(ENDIAN_LITTLE, *(uint32_t*)ptr);
                *len += sizeof(uint32_t);
                break;
            case VARINT64:
                value = endian64(ENDIAN_LITTLE, *(uint64_t*)ptr);
                break;
        }
    }

    return value;
}

// 整数转varint
void varint_set(uint8_t* bytes, uint64_t n, size_t* len) {
    *len = sizeof(uint8_t);
    if (n < VARINT16) {
        *bytes = n;
    }
    else {
        uint8_t prefix;
        if (n <= UINT16_MAX) {
            prefix = VARINT16;
            *(uint16_t*)(bytes+1) = endian16(ENDIAN_LITTLE, n);
            *len += sizeof(uint16_t);
        }
        else if (n <= UINT32_MAX) {
            prefix = VARINT32;
            *(uint32_t*)(bytes+1) = endian32(ENDIAN_LITTLE, n);
            *len += sizeof(uint32_t);
        }
        else {
            prefix = VARINT64;
            *(uint32_t*)(bytes+1) = endian64(ENDIAN_LITTLE, n);
            *len += sizeof(uint64_t);
        }
        *bytes = prefix;
    }
}

size_t varint_size(uint64_t n) {
    if (n < VARINT16) {
        return 1;
    }
    else if (n <= UINT16_MAX) {
        return 1 + sizeof(uint16_t);
    }
    else if (n <= UINT32_MAX) {
        return 1 + sizeof(uint32_t);
    }
    else {
        return 1 + sizeof(uint64_t);
    }
}

#endif //VARINT_H
