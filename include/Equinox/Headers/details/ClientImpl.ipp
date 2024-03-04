/*
 * Copyright (C) 2023 Anthony H. Grasso
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef EQUINOX_DETAILS_CLIENTIMPL_IPP
#define EQUINOX_DETAILS_CLIENTIMPL_IPP

#include "ClientDecl.hpp"

namespace eqx
{
    consteval Client::Client() noexcept
        :
        m_Socket()
    {
    }

    inline Client::Client(std::string_view ip,
        std::uint16_t port) noexcept
        :
        m_Socket()
    {
        connect(ip, port);
    }

    inline Client::Client(int socket) noexcept
        :
        m_Socket()
    {
        assign(socket);
    }

    inline void Client::connect(std::string_view ip,
        std::uint16_t port) noexcept
    {
        m_Socket.init(close, socket, AF_INET, SOCK_STREAM, 0);
        eqx::runtimeAssert(*m_Socket != -1, "Error Creating Socket!"sv);

        auto server_address = sockaddr_in();
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);
        auto error_code = inet_pton(AF_INET, ip.data(),
            &server_address.sin_addr);
        eqx::runtimeAssert(error_code == 1, "Inet Conversion Error!"sv);

        error_code = ::connect(*m_Socket, reinterpret_cast<sockaddr*>(&server_address),
            sizeof(server_address));
        eqx::runtimeAssert(error_code != -1, "Connection Error!"sv);
    }

    inline void Client::assign(int socket) noexcept
    {
        *m_Socket = socket;
    }

    inline void Client::send(std::string_view msg) noexcept
    {
        ::send(*m_Socket,
            std::ranges::data(msg), std::ranges::size(msg), 0);
    }

    [[nodiscard]] inline std::string Client::recv() noexcept
    {
        auto buffer = std::array<char, 1024>();
        auto bytes = ::recv(*m_Socket, buffer.data(), sizeof(buffer), 0);
        eqx::runtimeAssert(bytes != -1, "Error Receiving Message!"sv);
        if (bytes == 0)
        {
            std::strncpy(buffer.data(), "Client Disconnect!", 30);
        }
        else
        {
            buffer.at(static_cast<std::size_t>(bytes)) = '\0';
        }

        return std::string(buffer.data());
    }
}

#endif // EQUINOX_DETAILS_CLIENTIMPL_IPP
