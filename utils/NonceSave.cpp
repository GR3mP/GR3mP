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

#include "NonceSave.h"

namespace utils::nonce::save {

void NonceManager::save_to_memory(const std::array<uint8_t, 16>& nonce) {
    active_nonces[nonce] = {std::chrono::system_clock::now()};
}

bool NonceManager::verify_and_remove(const std::array<uint8_t, 16>& nonce) {
    auto it = active_nonces.find(nonce);
    if (it != active_nonces.end()) {
        auto now = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - it->second.created_at).count();
        
        if (duration <= it->second.expires_in_sec) {
            active_nonces.erase(it);
            return true;
        }
        
        active_nonces.erase(it);
    }
    return false;
}

void NonceManager::cleanup_expired() {
    auto now = std::chrono::system_clock::now();
    for (auto it = active_nonces.begin(); it != active_nonces.end(); ) {
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - it->second.created_at).count();
        if (duration > it->second.expires_in_sec) {
            it = active_nonces.erase(it);
        } else {
            ++it;
        }
    }
}

} // namespace utils::nonce::save
