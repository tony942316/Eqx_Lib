/*
 * Copyright (C) 2024 Anthony H. Grasso
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

module;

#include <Equinox/Macros.hpp>

export module Eqx.Lib.Server;

#include <Eqx/std.hpp>

import Eqx.Lib.Misc;
import Eqx.Lib.Socket;
import Eqx.Lib.Client;

export namespace eqx
{
    class Server
    {
    public:
        Server() = default;

        explicit inline Server(const std::uint16_t port) noexcept;

        Server(Server&& other) = default;
        Server& operator= (Server&& other) = default;
        ~Server() = default;

        Server(const Server& other) = delete;
        Server& operator= (const Server& other) = delete;

        inline void start(const std::uint16_t port) noexcept;
        [[nodiscard]] inline eqx::Client getConnection() noexcept;

    private:
        std::optional<eqx::Socket> m_Socket;
    };
}

// Implementations

export namespace eqx
{
    inline Server::Server(const std::uint16_t port) noexcept
    {
        start(port);
    }

    inline void Server::start(const std::uint16_t port) noexcept
    {
        m_Socket.emplace();

        m_Socket->makeListener(port);
    }

    [[nodiscard]] inline eqx::Client Server::getConnection() noexcept
    {
        return Client{m_Socket->accept()};
    }
}
