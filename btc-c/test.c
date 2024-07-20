#include <stdint.h>
#include "common.h"
#include "endian.h"
#include "hash.h"

void test_serilize_integer() {
    printf("\n------------------Test Serialize Integer------------------------\n");
    uint8_t n8 = 0x01;
    uint16_t n16 = 0x4523;
    uint32_t n32 = 0xcdab8967;
    uint64_t n64 = 0xdebc9a78563412ef;
    uint8_t ser[15] = {0};
    const char ser_exp[] = "0123456789abcdef123456789abcde";

    *ser = n8;
    *(uint16_t*)(ser + 1) = endian16(ENDIAN_LITTLE, n16);
    *(uint32_t*)(ser + 3) = endian32(ENDIAN_LITTLE, n32);
    *(uint64_t*)(ser + 7) = endian64(ENDIAN_LITTLE, n64);
    print_hex("ser    ", ser, sizeof(ser));
    printf("ser exp: %s\n", ser_exp);
}

void test_hash() {
    printf("\n------------------Test Hash------------------------\n");
    char message[] = "Hello Bitcoin!";
    uint16_t prefix = 0xd17f;
    uint8_t suffix = 0x8c;
    uint8_t digest[32];
    uint8_t ser[35];

    const char sha256_exp[] = "518ad5a375fa52f84b2b3df7933ad685eb62cf69869a96731561f94d10826b5c";
    const char hash256_exp[] = "90986ea4e28b847cc7f9beba87ea81b221ca6eaf9828a8b04c290c21d891bcda";
    const char ser_exp[] = "7fd190986ea4e28b847cc7f9beba87ea81b221ca6eaf9828a8b04c290c21d891bcda8c";

    sha256(digest, message, strlen(message));
    print_hex("SHA256(message)    ", digest, 32);
    printf("SHA256(message) exp: %s\n", sha256_exp);

    hash256(digest, message, strlen(message));
    print_hex("hash256(message)    ", digest, 32);
    printf("hash256(message) exp: %s\n", hash256_exp);

    *(uint16_t*)ser = endian16(ENDIAN_LITTLE, prefix);
    memcpy(ser+2, digest, 32);
    *(ser+2+32) = suffix;
    print_hex("ser    ", ser, sizeof(ser));
    printf("ser exp: %s\n", ser_exp);
}

int main() {
    test_hash();
    test_serilize_integer();
    return 0;
}
