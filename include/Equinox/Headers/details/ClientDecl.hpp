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

    /**
     * @brief Client To Send And Receive Data From Socket
     */
    class Client
    {
    public:
        /**
         * @brief Default Initialization
         */
        explicit consteval Client() noexcept;

        /**
         * @brief Initialize With Host And Port
         *
         * @param ip IP Of The eqx::Server
         * @param port Port Of The eqx::Server
         */
        explicit inline Client(std::string_view ip,
            std::uint16_t port) noexcept;

        /**
         * @brief Initialize With Active Socket
         *
         * @param socket Active Socket
         */
        explicit inline Client(int socket) noexcept;

        /**
         * @brief Initialize With Host And Port
         *
         * @param ip IP Of The eqx::Server
         * @param port Port Of The eqx::Server
         */
        inline void connect(std::string_view ip, std::uint16_t port) noexcept;

        /**
         * @brief Initialize With Active Socket
         *
         * @param socket Active Socket
         */
        inline void assign(int socket) noexcept;

        /**
         * @brief Send Data To The Socket
         *
         * @param msg Data To Send
         */
        inline void send(std::string_view msg) noexcept;

        /**
         * @brief Receive All Sent Data From The Socket
         *
         * @returns std::string With All The Data
         */
        [[nodiscard]] inline std::string recv() noexcept;

    private:
        eqx::UniqueResource<int, decltype(&close)> m_Socket;
    };
}

#endif // EQUINOX_DETAILS_CLIENTDECL_HPP
