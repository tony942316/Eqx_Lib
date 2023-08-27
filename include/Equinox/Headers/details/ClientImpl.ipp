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
        :
        m_Socket()
    {
    }

    inline Client::Client(std::string_view host, std::uint16_t port) noexcept
    {
        init(host, port);
    }

#ifdef __linux__
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
#endif // __linux__

#ifdef _WIN32
    inline void Client::init(std::string_view host, std::uint16_t port) noexcept
    {
        auto portStr = std::to_string(port);
        WSADATA wsaDATA;
        addrinfo* result = nullptr;
        addrinfo* ptr = nullptr;
        addrinfo hints;
        int iResult;

        eqx::runtimeAssert(WSAStartup(MAKEWORD(2, 2), &wsaDATA) == 0,
            "WSA Failed To Initialize!"sv);
        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        eqx::runtimeAssert(
            getaddrinfo(host.data(), portStr.c_str(), &hints, &result) == 0,
            "Couldn't Find Host!"sv);

        for (ptr = result; ptr != nullptr; ptr = ptr->ai_next)
        {
            m_Socket.init(closesocket, socket, ptr->ai_family, ptr->ai_socktype,
                ptr->ai_protocol);
            eqx::runtimeAssert(m_Socket.get() != INVALID_SOCKET,
                "Socket Creation Error!"sv);

            if (::connect(m_Socket.get(), ptr->ai_addr,
                static_cast<int>(ptr->ai_addrlen)) != SOCKET_ERROR)
            {
                break;
            }
        }

        freeaddrinfo(result);

        eqx::runtimeAssert(m_Socket.get() != INVALID_SOCKET,
            "Unable To Connect!"sv);
    }

    inline void Client::send(std::string_view msg) noexcept
    {
        ::send(m_Socket.get(), msg.data(), static_cast<int>(msg.size()), 0);
    }

    inline std::string Client::receive(std::size_t bytes) noexcept
    {
        static constexpr auto c_MaxBytes = 1024;
        eqx::runtimeAssert(bytes < c_MaxBytes,
            "1024 Bytes Is The Receive Limit!"sv);
        char buf[c_MaxBytes] = {};
        ::recv(m_Socket.get(), buf, static_cast<int>(bytes), 0);
        return std::string(buf);
    }
#endif // _WIN32
}

#endif // EQUINOX_DETAILS_CLIENTIMPL_IPP
