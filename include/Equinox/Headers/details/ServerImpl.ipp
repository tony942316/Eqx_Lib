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

#ifndef EQUINOX_DETAILS_SERVERIMPL_IPP
#define EQUINOX_DETAILS_SERVERIMPL_IPP

#include "ServerDecl.hpp"

namespace eqx
{
    consteval Server::Server() noexcept
        :
        m_Socket()
    {
    }

    inline Server::Server(std::uint16_t port) noexcept
        :
        m_Socket()
    {
        start(port);
    }

    inline void Server::start(std::uint16_t port) noexcept
    {
        m_Socket.init(close, socket, AF_INET, SOCK_STREAM, 0);
        eqx::runtimeAssert(*m_Socket != -1, "Error Creating Socket!"sv);

        static auto enable = 1;
        auto error_code = setsockopt(*m_Socket, SOL_SOCKET, SO_REUSEADDR,
            (void*)&enable, sizeof(enable));
        eqx::runtimeAssert(error_code == 0, "Error Setting Socket Option!"sv);

        sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(port);

        error_code = bind(*m_Socket,
            (sockaddr*)(&server_address), sizeof(server_address));
        eqx::runtimeAssert(error_code != -1, "Error Binding Socket!"sv);

        error_code = listen(*m_Socket, 5);
        eqx::runtimeAssert(error_code != -1, "Error Listening On Socket!"sv);
    }

    [[nodiscard]] inline Client Server::getConnection() noexcept
    {
        sockaddr_in client_address;
        socklen_t client_address_size = sizeof(client_address);
        int client_socket = accept(*m_Socket, (sockaddr*)&client_address,
            &client_address_size);
        eqx::runtimeAssert(client_socket != -1,
            "Error Accepting Connection!"sv);

        return Client(client_socket);
    }
}

#endif //EQUINOX_DETAILS_SERVERIMPL_IPP
