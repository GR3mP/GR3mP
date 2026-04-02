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

#pragma once

#include <openssl/bn.h>
#include <vector>
#include <cstdint>

namespace utils {

struct RSAKeyPair {
    std::vector<uint8_t> n; // Modulus (open)
    std::vector<uint8_t> e; // Pub E
    std::vector<uint8_t> d; // Priv E
    int64_t fingerprint;
};

class RSAGenerator {
public:
    static RSAKeyPair generate(int bits = 2048);
private:
    static int64_t calculate_fingerprint(BIGNUM* n, BIGNUM* e);
    static std::vector<uint8_t> bn_to_bytes(BIGNUM* bn);
};

} // namespace utils
