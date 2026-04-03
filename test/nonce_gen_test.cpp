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

#include "../net/handshake/nonce.h"

#include <iostream>

void test_nonce_generation() {
    std::vector<unsigned char> nonce = handshake::nonce::generate_nonce(16);

    std::cout << "TEST: generate nonce ";
    for (unsigned char b: nonce) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)b << "";
    }
    std::cout << "\n";
}

int main() {
    try {
        test_nonce_generation();
    } catch (const std::exception& e) {
        std::cerr << "[FAILED] Test crashed with error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
