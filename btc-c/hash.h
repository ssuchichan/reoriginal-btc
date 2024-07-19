#ifndef HASH_H
#define HASH_H

#include <openssl/sha.h>
#include <openssl/ripemd.h>

void sha256(uint8_t* digest, const uint8_t* message, size_t len) {
    SHA256(message, len, digest);
}



#endif //HASH_H
