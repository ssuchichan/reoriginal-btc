#ifndef HASH_H
#define HASH_H

#include <openssl/sha.h>
#include <openssl/evp.h>

void sha256(uint8_t* digest, const uint8_t* message, size_t len) {
    SHA256(message, len, digest);
}

void ripem160(uint8_t* digest, const uint8_t* message, size_t len) {
    unsigned int digest_len;
    EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(md_ctx, EVP_ripemd160(), NULL);
    EVP_DigestUpdate(md_ctx, message, len);
    EVP_DigestFinal(md_ctx, digest, &digest_len);
    EVP_MD_CTX_free(md_ctx);
}

void hash256(uint8_t* digest, const uint8_t* message, size_t len) {
    uint8_t tmp[SHA256_DIGEST_LENGTH] = {0};
    sha256(tmp, message, len);
    sha256(digest, tmp, SHA256_DIGEST_LENGTH);
}

void hash160(uint8_t* digest, const uint8_t* message, size_t len) {
    uint8_t tmp[SHA256_DIGEST_LENGTH] = {0};
    sha256(tmp, message, len);
    ripem160(digest, tmp, SHA256_DIGEST_LENGTH);
}

#endif //HASH_H
