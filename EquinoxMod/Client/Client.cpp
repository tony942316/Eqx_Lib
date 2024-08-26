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

export module Eqx.Lib.Client;

#include <Eqx/std.hpp>

import Eqx.Lib.Misc;
import Eqx.Lib.Socket;

export namespace eqx
{
    class Client
    {
    public:
        Client() = default;

        explicit inline Client(const std::string_view ip,
            const std::uint16_t port) noexcept;
        explicit inline Client(Socket&& socket) noexcept;

        Client(Client&& other) = default;
        Client& operator= (Client&& other) = default;
        ~Client() = default;

        Client(const Client& other) = delete;
        Client& operator= (const Client& other) = delete;

        inline void connect(const std::string_view ip,
            const std::uint16_t port) noexcept;
        inline void assign(Socket&& socket) noexcept;

        inline void send(const std::string_view msg) const noexcept;
        [[nodiscard]] inline std::string recv() const noexcept;

    private:
        std::optional<Socket> m_Socket;
    };
}

// Implementations

export namespace eqx
{
    inline Client::Client(const std::string_view ip,
        const std::uint16_t port) noexcept
    {
        connect(ip, port);
    }

    inline Client::Client(Socket&& socket) noexcept
    {
        assign(std::move(socket));
    }

    inline void Client::connect(const std::string_view ip,
        const std::uint16_t port) noexcept
    {
        m_Socket.emplace();

        m_Socket->connect(ip, port);
    }

    inline void Client::assign(Socket&& socket) noexcept
    {
        m_Socket = std::move(socket);
    }

    inline void Client::send(const std::string_view msg) const noexcept
    {
        m_Socket->send(msg);
    }

    [[nodiscard]] std::string Client::recv() const noexcept
    {
        return m_Socket->recv();
    }
}
