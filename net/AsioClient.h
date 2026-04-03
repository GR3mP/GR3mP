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

#include <asio.hpp>
#include <vector>
#include <string>
#include <memory>

namespace net {

namespace client {

namespace nonce {

    class Client {
    public:
        Client(const std::string& host, uint16_t port);

        bool connect();

        void send_packet(const std::vector<uint8_t>& data);

        void close();

    private:
        asio::io_context io_context_;
        asio::ip::tcp::socket socket_;
        asio::ip::tcp::endpoint endpoint_;
    };

} // namespace nonce

} // namespace client

} // namespace net
