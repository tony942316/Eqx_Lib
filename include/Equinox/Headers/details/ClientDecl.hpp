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

#ifndef EQUINOX_DETAILS_CLIENTDECL_HPP
#define EQUINOX_DETAILS_CLIENTDECL_HPP

#include "Dependencies.hpp"

#include "../UniqueResource.hpp"

namespace eqx
{
    /*
     * @brief Client To Send And Receive Data From eqx::Server
     */
    class Client
    {
    private:
#ifdef __linux__
        using Socket = UniqueResource<int, decltype(&close)>;
#endif // __linux__
#ifdef _WIN32
        using Socket = UniqueResource<SOCKET, decltype(&closesocket)>;
#endif // _WIN32
    public:
        /*
         * @brief Default Initialization
         */
        explicit constexpr Client() noexcept;

        /*
         * @brief Initialize With Host And Port
         *
         * @param host IP Of The eqx::Server
         * @param port Port Of The eqx::Server
         */
        explicit inline Client(std::string_view host,
            std::uint16_t port) noexcept;

        /*
         * @brief Initialize With Host And Port
         *
         * @param host IP Of The eqx::Server
         * @param port Port Of The eqx::Server
         */
        inline void init(std::string_view host, std::uint16_t port) noexcept;

        /*
         * @brief Send Data To The eqx::Server
         *
         * @param msg Data To Send
         */
        inline void send(std::string_view msg) noexcept;

        /*
         * @brief Receive Data From The eqx::Server
         *
         * @param bytes Number Of Bytes Receiving From The eqx::Server
         *
         * @returns std::string With All The Bytes
         */
        inline std::string receive(std::size_t bytes = 128) noexcept;

    private:
        Socket m_Socket;
    };
}

#endif // EQUINOX_DETAILS_CLIENTDECL_HPP
