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

#ifndef EQUINOX_DETAILS_SERVERDECL_HPP
#define EQUINOX_DETAILS_SERVERDECL_HPP

#include "Dependencies.hpp"

#include "../Misc.hpp"
#include "../UniqueResource.hpp"
#include "../Client.hpp"

namespace eqx
{
    /**
     * @brief Server To Listen For Incoming Connections
     */
    class Server
    {
    public:
        /**
         * @brief Default Initialization
         */
        explicit consteval Server() noexcept;

        /**
         * @brief Initialize With Port
         *
         * @param port Port Of The eqx::Server
         */
        explicit inline Server(std::uint16_t port) noexcept;

        /**
         * @brief Initialize With Port
         *
         * @param port Port Of The eqx::Server
         */
        inline void start(std::uint16_t port) noexcept;

        /**
         * @brief Wait For Then Return Client Connection
         *
         * @returns eqx::Client For Communication
         */
        [[nodiscard]] inline Client getConnection() noexcept;

    private:
        eqx::UniqueResource<int, decltype(&close)> m_Socket;
    };
}

#endif // EQUINOX_DETAILS_SERVERDECL_HPP
