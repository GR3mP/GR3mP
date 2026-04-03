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

#include "Abridged.h"
#include <cstring>
#include <algorithm>

namespace transport::abridged::nonce {

    std::vector<uint8_t> create_packet(const std::array<uint8_t, 16>& raw_nonce, 
                                 utils::nonce::save::NonceManager& manager) {
    manager.save_to_memory(raw_nonce);

    packet p;

    std::copy(raw_nonce.begin(), raw_nonce.end(), p.nonce.begin());

    std::vector<uint8_t> out_buffer(sizeof(packet));
    std::memcpy(out_buffer.data(), &p, sizeof(packet));

    return out_buffer;
    }

} // namespace transport
