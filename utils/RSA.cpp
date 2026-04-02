/*
 * Copyright 2026 Gleb Obitotsky (oximif174@gmail.com),
 *           2026 GR3mPteam
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
 *  
 * You should have received a copy of the GNU General Public License
 * along with GR3mP. If not, see <https://www.gnu.org/licenses/>.
 */

#include "RSA.h"
#include <openssl/sha.h>
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

} // namespace utils
