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

#include "nonce.h"
#include <system_error>

namespace handshake {

namespace nonce {

    std::vector<unsigned char> generate_nonce(size_t count) {
        std::vector<unsigned char> buffer(count);
        if (RAND_bytes(buffer.data(), count) != 1) {
            std::cerr << "[!] ERROR: Field generate nonce" << "\n";
        }
        return buffer;
    }
} // namespace nonce

} // namespace handshake
