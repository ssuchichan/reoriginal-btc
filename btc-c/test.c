#include <stdint.h>
#include "common.h"
#include "endian.h"
#include "hash.h"
#include "varint.h"

void test_varint() {
    typedef struct {
        uint16_t fixed1;
        uint64_t var2;
        uint32_t fixed3;
        uint8_t fixed4;
    }foo_t;

    uint8_t bytes[] = {0x13, 0x9c, 0xfd, 0x7d, 0x80, 0x44, 0x6b, 0xa2, 0x20, 0xcc};
    foo_t decoded;
    size_t varlen;

    const foo_t exp = {0x9c13, 0x807d, 0x20a26b44, 0xcc};

    decoded.fixed1 = endian16(ENDIAN_LITTLE, *(uint16_t*)bytes);
    decoded.var2 = varint_get(bytes + 2, &varlen);
    decoded.fixed3 = endian32(ENDIAN_LITTLE, *(uint32_t*)(bytes + 2 + varlen));
    decoded.fixed4 = *(bytes + 2 + varlen + 4);

    printf("fixed1      : %x\n", decoded.fixed1);
    printf("fixed1 (exp): %x\n", exp.fixed1);
    printf("var2      : %llx\n", decoded.var2);
    printf("var2 (exp): %llx\n", exp.var2);
    printf("fixed3      : %x\n", decoded.fixed3);
    printf("fixed3 (exp): %x\n", exp.fixed3);
    printf("fixed4      : %x\n", decoded.fixed4);
    printf("fixed4 (exp): %x\n", exp.fixed4);
}

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
    test_varint();
    test_hash();
    test_serilize_integer();
    return 0;
}
