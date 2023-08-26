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
    using namespace eqx::literals;

    constexpr Client::Client() noexcept
    {

    }

    inline Client::Client(std::string_view host, std::uint16_t port) noexcept
    {
        init(host, port);
    }

    inline void Client::init(std::string_view host, std::uint16_t port) noexcept
    {
        m_Socket.init(close, socket, AF_INET, SOCK_STREAM, 0);
        eqx::runtimeAssert(m_Socket.get() > -1,
            "Client Socket Error!"sv);

        hostent* servEnt = gethostbyname(host.data());
        eqx::runtimeAssert(servEnt != nullptr,
            "Host Not Found!"sv);

        sockaddr_in serv = {};
        serv.sin_family = AF_INET;
        std::memcpy((char*)servEnt->h_addr,
            (char*)&serv.sin_addr.s_addr,
            static_cast<std::size_t>(servEnt->h_length));
        serv.sin_port = htons(port);
        eqx::runtimeAssert(
            connect(m_Socket.get(), (sockaddr*)&serv, sizeof(serv)) > -1,
            "Client Connect Error!"sv);
    }

    inline void Client::send(std::string_view msg) noexcept
    {
        auto nBytes = write(m_Socket.get(), msg.data(), msg.size());
        eqx::runtimeAssert(nBytes > -1,
            "Client Write Error!"sv);
    }

    inline std::string Client::receive(std::size_t bytes) noexcept
    {
        auto msg = std::string();
        msg.resize(bytes);
        auto nBytes = read(m_Socket.get(), msg.data(), bytes);
        eqx::runtimeAssert(nBytes > -1,
            "Client Read Error!"sv);
        return msg;
    }
}

#endif // EQUINOX_DETAILS_CLIENTIMPL_IPP
