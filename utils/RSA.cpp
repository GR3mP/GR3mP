/*
 * Copyright 2026 Gleb Obitotsky (oximif174@gmail.com),
 * 2026 GR3mPteam
 *
 * GR3mP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GR3mP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * * You should have received a copy of the GNU General Public License
 * along with GR3mP. If not, see <https://www.gnu.org/licenses/>.
 */

#include "RSA.h"
#include <openssl/evp.h>
#include <openssl/crypto.h>

namespace utils {

RSAKeyPair RSAGenerator::generate(int bits) {

    RSAKeyPair key_pair;

    BN_CTX* ctx = BN_CTX_new();
    BIGNUM* p = BN_new();
    BIGNUM* q = BN_new();
    BIGNUM* n = BN_new();
    BIGNUM* e = BN_new();
    BIGNUM* d = BN_new();
    BIGNUM* phi = BN_new();
    BIGNUM* p_minus_1 = BN_new();
    BIGNUM* q_minus_1 = BN_new();

    BN_set_word(e, 65537);

    if (BN_generate_prime_ex(p, bits / 2, 0, nullptr, nullptr, nullptr) && 
        BN_generate_prime_ex(q, bits / 2, 0, nullptr, nullptr, nullptr)) {

        BN_mul(n, p, q, ctx);

        BN_sub(p_minus_1, p, BN_value_one());
        BN_sub(q_minus_1, q, BN_value_one());
        BN_mul(phi, p_minus_1, q_minus_1, ctx);

        if (BN_mod_inverse(d, e, phi, ctx)) {
            key_pair.n = bn_to_bytes(n);
            key_pair.e = bn_to_bytes(e);
            key_pair.d = bn_to_bytes(d);

            key_pair.fingerprint = calculate_fingerprint(n, e);
        }
    }

    BN_clear_free(p);
    BN_clear_free(q);
    BN_clear_free(d);
    BN_clear_free(phi);
    BN_clear_free(p_minus_1);
    BN_clear_free(q_minus_1); 
    BN_clear_free(n);
    BN_clear_free(e);
    BN_CTX_free(ctx);

    return key_pair;
}

std::vector<uint8_t> RSAGenerator::bn_to_bytes(BIGNUM* bn) {
    int len = BN_num_bytes(bn);
    if (len <= 0) return {};

    std::vector<uint8_t> res(len);
    BN_bn2bin(bn, res.data());
    return res;
}

void update_sha1_with_tl_bytes(EVP_MD_CTX* ctx, const std::vector<uint8_t>& data) {
    uint32_t len = static_cast<uint32_t>(data.size());
    uint8_t header[4];
    int header_len;

    if (len < 254) {
        header[0] = static_cast<uint8_t>(len);
        header_len = 1;
    } else {
        header[0] = 254;
        header[1] = static_cast<uint8_t>(len & 0xFF);
        header[2] = static_cast<uint8_t>((len >> 8) & 0xFF);
        header[3] = static_cast<uint8_t>((len >> 16) & 0xFF);
        header_len = 4;
    }

    EVP_DigestUpdate(ctx, header, header_len);
    EVP_DigestUpdate(ctx, data.data(), data.size());

    int total_len = header_len + static_cast<int>(data.size());
    int padding = (4 - (total_len % 4)) % 4;
    if (padding > 0) {
        uint8_t pad_bytes[3] = {0, 0, 0};
        EVP_DigestUpdate(ctx, pad_bytes, padding);
    }
}

int64_t RSAGenerator::calculate_fingerprint(BIGNUM* n, BIGNUM* e) {
    std::vector<uint8_t> n_bytes = bn_to_bytes(n);
    std::vector<uint8_t> e_bytes = bn_to_bytes(e);

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_get_digestbyname("SHA1");

    EVP_DigestInit_ex(mdctx, md, nullptr);

    update_sha1_with_tl_bytes(mdctx, n_bytes);
    update_sha1_with_tl_bytes(mdctx, e_bytes);

    uint8_t hash[20];
    unsigned int hash_len = 0;
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);
    EVP_MD_CTX_free(mdctx);

    int64_t fingerprint = 0;
    for (int i = 0; i < 8; i++) {
        fingerprint |= static_cast<int64_t>(hash[hash_len - 8 + i]) << (8 * i);
    }
    
    return fingerprint;
}

} // namespace utils
