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

#ifdef __linux__

#ifndef EQUINOX_DETAILS_SERVERIMPL_IPP
#define EQUINOX_DETAILS_SERVERIMPL_IPP

#include "ServerDecl.hpp"

namespace eqx
{
    using namespace eqx::literals;

    constexpr Server::Server() noexcept
        :
        m_ServerSocket(),
        m_ClientSocket()
    {
    }

    inline Server::Server(std::uint16_t port) noexcept
        :
        Server()
    {
        init(port);
    }

    inline void Server::init(std::uint16_t port) noexcept
    {
        m_ServerSocket.init(close, socket, AF_INET, SOCK_STREAM, 0);
        eqx::runtimeAssert(m_ServerSocket.get() > -1,
            "Socket Creation Error!"sv);

        sockaddr_in serv = {};
        serv.sin_family = AF_INET;
        serv.sin_addr.s_addr = INADDR_ANY;
        serv.sin_port = htons(port);

        eqx::runtimeAssert(
            bind(m_ServerSocket.get(), (sockaddr*)&serv, sizeof(serv)) > -1,
            "Server Bind Error!"sv);
        listen(m_ServerSocket.get(), 5);

        sockaddr_in client = {};
        socklen_t clientLen = sizeof(client);
        m_ClientSocket.init(close, accept,
            m_ServerSocket.get(), (sockaddr*)&client, &clientLen);
        eqx::runtimeAssert(m_ClientSocket.get() > -1,
            "Server Accept Error!"sv);
    }

    inline void Server::send(std::string_view msg) noexcept
    {
        auto nBytes = write(m_ClientSocket.get(), msg.data(), msg.size());
        eqx::runtimeAssert(nBytes > -1, "Server Write Error!"sv);
    }

    inline std::string Server::receive(std::size_t bytes) noexcept
    {
        auto msg = std::string();
        msg.resize(bytes);
        auto nBytes = read(m_ClientSocket.get(), msg.data(), bytes);
        eqx::runtimeAssert(nBytes > -1, "Server Read Error!"sv);
        return msg;
    }
}

#endif //EQUINOX_DETAILS_SERVERIMPL_IPP

#endif // __linux__
