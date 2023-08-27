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

#ifndef EQUINOX_DETAILS_SERVERDECL_HPP
#define EQUINOX_DETAILS_SERVERDECL_HPP

#include "Dependencies.hpp"

#include "../Misc.hpp"
#include "../UniqueResource.hpp"

namespace eqx
{
    /*
     * @brief Server To Send And Receive Data From eqx::Client
     */
    class Server
    {
    private:
        using Socket = UniqueResource<int, decltype(&close)>;

    public:
        /*
         * @brief Default Initialization
         */
        explicit constexpr Server() noexcept;

        /*
         * @brief Initialize With Host And Port, Blocks Until Connection!
         *
         * @param host IP Of The eqx::Client
         * @param port Port Of The eqx::Client
         */
        explicit inline Server(std::uint16_t port) noexcept;

        /*
         * @brief Initialize With Host And Port, Blocks Until Connection!
         *
         * @param host IP Of The eqx::Client
         * @param port Port Of The eqx::Client
         */
        inline void init(std::uint16_t port) noexcept;

        /*
         * @brief Send Data To The eqx::Client
         *
         * @param msg Data To Send
         */
        inline void send(std::string_view msg) noexcept;

        /*
         * @brief Receive Data From The eqx::Client
         *
         * @param bytes Number Of Bytes Receiving From The eqx::Client
         *
         * @returns std::string With All The Bytes
         */
        inline std::string receive(std::size_t bytes) noexcept;

    private:
        Socket m_ServerSocket, m_ClientSocket;
    };
}

#endif // EQUINOX_DETAILS_SERVERDECL_HPP

#endif // __linux__
