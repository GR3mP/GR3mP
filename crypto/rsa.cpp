/*
 * Copyright 2026 Gleb Obitotsky,
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

#include "rsa_gen.h"
#include <openssl/evp.h>
#include <openssl/rsa.h>
// #include <openssl/pem.h>

EVP_PKEY* generate_keypair_rsa() {
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if(!ctx) return nullptr;

    EVP_PKEY *pkey = nullptr;
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }

    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }

    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return nullptr;
    }

    EVP_PKEY_CTX_free(ctx);
    return pkey;
}

void free_keypair(EVP_PKEY* pkey) {
    if (pkey) {
        EVP_PKEY_free(pkey);
    }
}
