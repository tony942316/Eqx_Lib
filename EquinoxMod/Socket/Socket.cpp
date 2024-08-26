module;

#include "Equinox/Macros.hpp"

#if EQX_LINUX

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#endif // EQX_LINUX

export module Eqx.Lib.Socket;

#include <Eqx/std.hpp>
#include <Eqx/os.hpp>

import Eqx.Lib.Misc;

using namespace std::literals;

export namespace eqx
{
#if EQX_LINUX
    using socket_t = int;
#elif EQX_WINDOWS
    using socket_t = SOCKET;
#endif

    class Socket
    {
    public:
        explicit inline Socket() noexcept;
        explicit inline Socket(const socket_t socket) noexcept;

        explicit inline Socket(Socket&& other) noexcept;
        inline Socket& operator= (Socket&& other) noexcept;

        Socket(const Socket& other) = delete;
        Socket& operator= (const Socket& other) = delete;

        inline ~Socket() noexcept;

        [[nodiscard]] inline socket_t get() const noexcept;

        inline void send(const std::string_view msg) const noexcept;
        [[nodiscard]] inline std::string recv() const noexcept;

        inline void connect(const std::string_view ip,
            const std::uint16_t port) noexcept;

        inline void makeListener(const std::uint16_t port) noexcept;
        inline Socket accept() noexcept;

        static inline void init() noexcept;
    private:
        socket_t m_Socket;
    };
}

namespace eqx
{
    inline Socket::Socket() noexcept
        :
        m_Socket(::socket(AF_INET, SOCK_STREAM, 0))
    {
        eqx::ENSURE_HARD(m_Socket != INVALID_SOCKET,
            "Error Creating Socket!"sv);
    }

    inline Socket::Socket(const socket_t socket) noexcept
        :
        m_Socket(socket)
    {
    }

    inline Socket::Socket(Socket&& other) noexcept
        :
        m_Socket(other.m_Socket)
    {
        other.m_Socket = INVALID_SOCKET;
    }

    inline Socket& Socket::operator= (Socket&& other) noexcept
    {
        eqx::ENSURE_HARD(this != &other, "Moving From Same Object!!!"sv);
        m_Socket = other.m_Socket;
        other.m_Socket = INVALID_SOCKET;
        return *this;
    }

    inline Socket::~Socket() noexcept
    {
        if (m_Socket != INVALID_SOCKET)
        {
#if EQX_LINUX
            [[maybe_unused]] auto error_code = ::close(m_Socket);
#elif EQX_WINDOWS
            [[maybe_unused]] auto error_code = ::closesocket(m_Socket);
#endif
        }
    }

    [[nodiscard]] inline socket_t Socket::get() const noexcept
    {
        return m_Socket;
    }

    inline void Socket::send(const std::string_view msg) const noexcept
    {
        const auto bytes = ::send(m_Socket, std::ranges::data(msg),
            static_cast<unsigned int>(std::ranges::size(msg)), 0);

        eqx::ENSURE_HARD(bytes != SOCKET_ERROR,
            "Send Error!!!"sv);
    }

    [[nodiscard]] inline std::string Socket::recv() const noexcept
    {
        using namespace eqx::literals;

        constexpr auto bufsize = 1024_uz;
        auto buffer = std::array<char, bufsize>{};

#if EQX_LINUX
        const auto bytes = ::recv(m_Socket, std::ranges::data(buffer),
            std::ranges::size(buffer), 0);
#elif EQX_WINDOWS
        const auto bytes = ::recv(m_Socket, std::ranges::data(buffer),
            static_cast<int>(std::ranges::size(buffer)), 0);
#endif

        eqx::ENSURE_HARD(bytes != SOCKET_ERROR,
            "Error Receiving Message!"sv);

        buffer.at(static_cast<std::size_t>(bytes)) = '\0';

        return std::string{buffer.data()};
    }

    inline void Socket::connect(const std::string_view ip,
        const std::uint16_t port) noexcept
    {

        auto server_address = sockaddr_in{};
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);

        inet_pton(AF_INET, std::ranges::data(ip), &server_address.sin_addr);

        auto error_code = ::connect(m_Socket,
            reinterpret_cast<sockaddr*>(&server_address),
            sizeof(server_address));

        eqx::ENSURE_HARD(error_code != SOCKET_ERROR,
            "Connection Error!"sv);
    }

    inline void Socket::makeListener(const std::uint16_t port) noexcept
    {
        static auto enable = 1;
#if EQX_LINUX
        auto error_code = ::setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR,
            reinterpret_cast<void*>(&enable), sizeof(enable));
#elif EQX_WINDOWS
        auto error_code = ::setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR,
            reinterpret_cast<const char*>(&enable), sizeof(enable));
#endif
        eqx::ENSURE_HARD(error_code == 0, "Error Setting Socket Option!"sv);

        auto server_address = sockaddr_in();
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(port);
        error_code = ::bind(m_Socket,
            reinterpret_cast<sockaddr*>(&server_address),
            sizeof(server_address));
        eqx::ENSURE_HARD(error_code != -1, "Error Binding Socket!"sv);

        error_code = ::listen(m_Socket, 5);
        eqx::ENSURE_HARD(error_code != -1, "Error Listening On Socket!"sv);
    }

    inline Socket Socket::accept() noexcept
    {
        auto client_address = sockaddr_in();
        socklen_t client_address_size = sizeof(client_address);
        auto client_socket = ::accept(m_Socket,
            reinterpret_cast<sockaddr*>(&client_address), &client_address_size);
        eqx::ENSURE_HARD(client_socket != -1, "Error Accepting Connection!"sv);

        return Socket{client_socket};
    }

    inline void Socket::init() noexcept
    {
#if EQX_WINDOWS
        WSADATA wsaData = {0};
        WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    }
}
