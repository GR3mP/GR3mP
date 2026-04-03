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

#include <map>
#include <array>
#include <vector>
#include <chrono>
#include <cstdint>

namespace utils::nonce::save {

struct NonceContext {
    std::chrono::system_clock::time_point created_at;
    uint32_t expires_in_sec = 60;
};

class NonceManager {
private:
    std::map<std::array<uint8_t, 16>, NonceContext> active_nonces;

public:
    void save_to_memory(const std::array<uint8_t, 16>& nonce);
    bool verify_and_remove(const std::array<uint8_t, 16>& nonce);
    
    void cleanup_expired();
};

} // namespace utils::nonce::save
