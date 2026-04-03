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

#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <openssl/rand.h>

#include "../transport/Abridged.h"
#include "../utils/NonceSave.h"

void print_hex(const std::string& label, const std::vector<uint8_t>& data) {
    std::cout << label << " [" << data.size() << " bytes]: ";
    for (auto b : data) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)b << " ";
    }
    std::cout << std::dec << std::endl;
}

int main() {
    std::cout << "--- Starting GR3mP Handshake Test ---" << std::endl;

    utils::nonce::save::NonceManager manager;

    std::array<uint8_t, 16> test_nonce;
    if (RAND_bytes(test_nonce.data(), 16) != 1) {
        std::cerr << "OpenSSL RAND_bytes failed!" << std::endl;
        return 1;
    }
    
    std::vector<uint8_t> nonce_vec(test_nonce.begin(), test_nonce.end());
    print_hex("Generated Nonce", nonce_vec);

    std::vector<uint8_t> final_packet = transport::abridged::nonce::create_packet(test_nonce, manager);

    std::cout << "\nFinal Packet for Socket:" << std::endl;
    print_hex("PACKET", final_packet);

    std::cout << "\nChecking NonceManager storage..." << std::endl;
    if (manager.verify_and_remove(test_nonce)) {
        std::cout << "[SUCCESS] Nonce was found and verified in memory." << std::endl;
    } else {
        std::cout << "[FAILED] Nonce NOT found in memory!" << std::endl;
    }

    if (!manager.verify_and_remove(test_nonce)) {
        std::cout << "[SUCCESS] Replay protection works (nonce deleted after verify)." << std::endl;
    }

    return 0;
}
