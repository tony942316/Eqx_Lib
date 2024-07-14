module;

#include <Equinox/Macros.hpp>

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>

#ifdef __linux__

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#endif // __linux__

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#define NOMINMAX

#pragma warning(push)
#pragma warning(disable : 5105)
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma warning(pop)
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

#endif // _WIN32

export module Equinox.Client;

import Eqx.Stdm;
import Equinox.Misc;

export namespace eqx
{
    class Socket
    {
    public:
#ifdef __linux__
        using socket_type = int;
#endif // __linux__

#ifdef _WIN32
        using socket_type = SOCKET;
#endif // _WIN32

        explicit inline Socket() noexcept;
        explicit inline Socket(const socket_type socket) noexcept;

        explicit inline Socket(Socket&& other) noexcept;
        inline Socket& operator= (Socket&& other) noexcept;

        Socket(const Socket& other) = delete;
        Socket& operator= (const Socket& other) = delete;

        inline ~Socket() noexcept;

        [[nodiscard]] inline socket_type get() const noexcept;

        inline void send(const stdm::string_view msg) const noexcept;
        [[nodiscard]] inline stdm::string recv() const noexcept;

        static inline void init() noexcept;
    private:
        socket_type m_Socket;
    };

    class Client
    {
    public:
        Client() = default;

        explicit inline Client(const stdm::string_view ip,
            const stdm::uint16_t port) noexcept;
        explicit inline Client(Socket&& socket) noexcept;

        Client(Client&& other) = default;
        Client& operator= (Client&& other) = default;
        ~Client() = default;

        Client(const Client& other) = delete;
        Client& operator= (const Client& other) = delete;

        inline void connect(const stdm::string_view ip,
            const stdm::uint16_t port) noexcept;
        inline void assign(Socket&& socket) noexcept;

        inline void send(const stdm::string_view msg) const noexcept;
        [[nodiscard]] inline stdm::string recv() const noexcept;

    private:
        stdm::optional<Socket> m_Socket;
    };
}

// Implementations

export namespace eqx
{
    inline Socket::Socket() noexcept
        :
        m_Socket(socket(AF_INET, SOCK_STREAM, 0))
    {
        eqx::ENSURE_HARD(m_Socket != INVALID_SOCKET,
            "Error Creating Socket!"sv);
    }

    inline Socket::Socket(const Socket::socket_type socket) noexcept
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
#ifdef __linux__
            close(m_Socket);
#endif // __linux__

#ifdef _WIN32
            closesocket(m_Socket);
#endif // _WIN32
        }
    }

    [[nodiscard]] inline Socket::socket_type Socket::get() const noexcept
    {
        return m_Socket;
    }

    inline void Socket::send(const stdm::string_view msg) const noexcept
    {
#ifdef __linux__
        const auto bytes = ::send(m_Socket, stdm::ranges::data(msg),
            stdm::ranges::size(msg), 0);
#endif // __linux__

#ifdef _WIN32
        const auto bytes = ::send(m_Socket, stdm::ranges::data(msg),
            static_cast<int>(stdm::ranges::size(msg)), 0);
#endif // _WIN32

        eqx::ENSURE_HARD(bytes != SOCKET_ERROR, "Send Error!!!"sv);
    }

    [[nodiscard]] inline stdm::string Socket::recv() const noexcept
    {
        auto buffer = stdm::array<char, 1024>{};

#ifdef __linux__
        auto bytes = ::recv(m_Socket, buffer.data(), sizeof(buffer), 0);
#endif // __linux__

#ifdef _WIN32
        auto bytes = ::recv(m_Socket, buffer.data(),
            static_cast<int>(sizeof(buffer)), 0);
#endif // _WIN32

        eqx::ENSURE_HARD(bytes != SOCKET_ERROR, "Error Receiving Message!"sv);

        if (bytes == 0)
        {
            std::strncpy(buffer.data(), "Client Disconnect!", 30);
        }
        else
        {
            buffer.at(static_cast<stdm::size_t>(bytes)) = '\0';
        }

        return stdm::string{buffer.data()};
    }

    inline void Socket::init() noexcept
    {
#ifdef _WIN32
        WSADATA wsaData = {0};
        WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif // _WIN32
    }

    inline Client::Client(const stdm::string_view ip,
        const stdm::uint16_t port) noexcept
    {
        connect(ip, port);
    }

    inline Client::Client(Socket&& socket) noexcept
    {
        assign(stdm::move(socket));
    }

    inline void Client::connect(const stdm::string_view ip,
        const stdm::uint16_t port) noexcept
    {
        m_Socket.emplace();
        auto server_address = sockaddr_in{};
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);
        auto error_code = inet_pton(AF_INET, ip.data(),
            &server_address.sin_addr);
        eqx::ENSURE_HARD(error_code != -1, "Inet Conversion Error!"sv);

#ifdef __linux__
        error_code = ::connect(m_Socket->get(),
            reinterpret_cast<sockaddr*>(&server_address),
            sizeof(server_address));
#endif // __linux__

#ifdef _WIN32
        error_code = ::connect(m_Socket->get(), (SOCKADDR*)&server_address,
            sizeof(server_address));
#endif // _WIN32

        eqx::ENSURE_HARD(error_code != SOCKET_ERROR, "Connection Error!"sv);
    }

    inline void Client::assign(Socket&& socket) noexcept
    {
        m_Socket = stdm::move(socket);
    }

    inline void Client::send(const stdm::string_view msg) const noexcept
    {
        m_Socket->send(msg);
    }

    [[nodiscard]] stdm::string Client::recv() const noexcept
    {
        return m_Socket->recv();
    }
}
