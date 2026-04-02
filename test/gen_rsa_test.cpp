/*
 * Copyright 2026 Gleb Obitotsky (oximif147@gmail.com),
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

#include <iostream>
#include <iomanip>
#include <cassert>
#include "../utils/RSA.h"

void test_rsa_generation() {
    std::cout << "[TEST] Starting RSA generation test..." << std::endl;

    utils::RSAKeyPair keys = utils::RSAGenerator::generate(2048);

    assert(!keys.n.empty() && "Modulus n should not be empty");
    assert(!keys.e.empty() && "Exponent e should not be empty");
    assert(!keys.d.empty() && "Private key d should not be empty");

    std::cout << "[INFO] Modulus size: " << keys.n.size() << " bytes" << std::endl;
    assert(keys.n.size() >= 255 && keys.n.size() <= 256);

    assert(keys.e.size() >= 1);

    std::cout << "[INFO] Fingerprint: 0x" << std::hex << keys.fingerprint << std::dec << std::endl;
    assert(keys.fingerprint != 0 && "Fingerprint should not be zero");

    std::cout << "[SUCCESS] RSA Generation test passed!" << std::endl;
}

int main() {
    try {
        test_rsa_generation();
    } catch (const std::exception& e) {
        std::cerr << "[FAILED] Test crashed with error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

