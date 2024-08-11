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

export module Equinox.Client;

import Eqx.Stdm;
import Eqx.OSm;
import Equinox.Misc;

export namespace eqx
{
    class Socket
    {
    public:
        explicit inline Socket() noexcept;
        explicit inline Socket(const osm::socket::socket_t socket) noexcept;

        explicit inline Socket(Socket&& other) noexcept;
        inline Socket& operator= (Socket&& other) noexcept;

        Socket(const Socket& other) = delete;
        Socket& operator= (const Socket& other) = delete;

        inline ~Socket() noexcept;

        [[nodiscard]] inline osm::socket::socket_t get() const noexcept;

        inline void send(const std::string_view msg) const noexcept;
        [[nodiscard]] inline std::string recv() const noexcept;

        static inline void init() noexcept;
    private:
        osm::socket::socket_t m_Socket;
    };

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
    inline Socket::Socket() noexcept
        :
        m_Socket(osm::socket::open(osm::socket::domain::inet,
            osm::socket::type::stream))
    {
        eqx::ENSURE_HARD(m_Socket != osm::socket::error::invalid,
            "Error Creating Socket!"sv);
    }

    inline Socket::Socket(const osm::socket::socket_t socket) noexcept
        :
        m_Socket(socket)
    {
    }

    inline Socket::Socket(Socket&& other) noexcept
        :
        m_Socket(other.m_Socket)
    {
        other.m_Socket = osm::socket::error::invalid;
    }

    inline Socket& Socket::operator= (Socket&& other) noexcept
    {
        eqx::ENSURE_HARD(this != &other, "Moving From Same Object!!!"sv);
        m_Socket = other.m_Socket;
        other.m_Socket = osm::socket::error::invalid;
        return *this;
    }

    inline Socket::~Socket() noexcept
    {
        if (m_Socket != osm::socket::error::invalid)
        {
            [[maybe_unused]] auto error_code = osm::socket::close(m_Socket);
        }
    }

    [[nodiscard]] inline osm::socket::socket_t Socket::get() const noexcept
    {
        return m_Socket;
    }

    inline void Socket::send(const std::string_view msg) const noexcept
    {
        const auto bytes = osm::socket::send(m_Socket, std::ranges::data(msg),
            static_cast<unsigned int>(std::ranges::size(msg)));

        eqx::ENSURE_HARD(bytes != osm::socket::error::socket,
            "Send Error!!!"sv);
    }

    [[nodiscard]] inline std::string Socket::recv() const noexcept
    {
        using namespace eqx::literals;

        constexpr auto bufsize = 1024_uz;
        auto buffer = std::array<char, bufsize>{};

        const auto bytes = osm::socket::recv(m_Socket, buffer.data(),
            buffer.size());

        eqx::ENSURE_HARD(bytes != osm::socket::error::socket,
            "Error Receiving Message!"sv);

        buffer.at(static_cast<std::size_t>(bytes)) = '\0';

        return std::string{buffer.data()};
    }

    inline void Socket::init() noexcept
    {
        osm::socket::wsaInit();
    }

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

        auto error_code = osm::socket::connect(m_Socket->get(), ip.data(),
            port);

        eqx::ENSURE_HARD(error_code != osm::socket::error::socket,
            "Connection Error!"sv);
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
