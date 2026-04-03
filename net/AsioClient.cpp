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

#include "AsioClient.h"
#include <iostream>

namespace net {

namespace client {

namespace nonce {

    Client::Client(const std::string& host, uint16_t port) : socket_(io_context_) {
        asio::ip::tcp::resolver resolver(io_context_);
        auto endpoints = resolver.resolve(host, std::to_string(port));
        endpoint_ = *endpoints.begin();
    }

    bool Client::connect() {
        asio::error_code ec;
        socket_.connect(endpoint_, ec);
        if (ec) {
            std::cerr << "Connect ERROR: " << ec.message() << "\n";
            return false;
        }
        return true;
    }

    void Client::send_packet(const std::vector<uint8_t>& data) {
        asio::error_code ec;
        asio::write(socket_, asio::buffer(data), ec);
        if (ec) {
        std::cerr << "[Network] Send error: " << ec.message() << std::endl;
        }
    }

    void Client::close() {
    if (socket_.is_open()) {
        socket_.close();
    }
    }

} // namespace nonce

} // namespace client

} // namespace net
