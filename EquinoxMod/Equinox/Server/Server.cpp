module;

#include <Equinox/Macros.hpp>

#include <cstring>

#ifdef __linux__

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

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

export module Equinox.Server;

import Eqx.Stdm;
import Equinox.Misc;
import Equinox.Client;

export namespace eqx
{
    class Server
    {
    public:
        Server() = default;

        explicit inline Server(const stdm::uint16_t port) noexcept;

        Server(Server&& other) = default;
        Server& operator= (Server&& other) = default;
        ~Server() = default;

        Server(const Server& other) = delete;
        Server& operator= (const Server& other) = delete;

        inline void start(const stdm::uint16_t port) noexcept;
        [[nodiscard]] inline eqx::Client getConnection() noexcept;

    private:
        stdm::optional<eqx::Socket> m_Socket;
    };
}

// Implementations

export namespace eqx
{
    inline Server::Server(const stdm::uint16_t port) noexcept
    {
        start(port);
    }

    inline void Server::start(const stdm::uint16_t port) noexcept
    {
        m_Socket.emplace();

        static auto enable = 1;
#ifdef __linux__
        auto error_code = setsockopt(m_Socket->get(), SOL_SOCKET, SO_REUSEADDR,
            reinterpret_cast<void*>(&enable), sizeof(enable));
#endif // __linux__

#ifdef _WIN32
        auto error_code = setsockopt(m_Socket->get(), SOL_SOCKET, SO_REUSEADDR,
            (const char*)&enable, sizeof(enable));
#endif // _WIN32
        eqx::ENSURE_HARD(error_code == 0, "Error Setting Socket Option!"sv);

        auto server_address = sockaddr_in();
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(port);

        error_code = bind(m_Socket->get(),
            reinterpret_cast<sockaddr*>(&server_address),
            sizeof(server_address));
        eqx::ENSURE_HARD(error_code != -1, "Error Binding Socket!"sv);

        error_code = listen(m_Socket->get(), 5);
        eqx::ENSURE_HARD(error_code != -1, "Error Listening On Socket!"sv);
    }

    [[nodiscard]] inline eqx::Client Server::getConnection() noexcept
    {
        auto client_address = sockaddr_in();
        socklen_t client_address_size = sizeof(client_address);
#ifdef __linux__
        auto client_socket = accept4(m_Socket->get(),
            reinterpret_cast<sockaddr*>(&client_address),
            &client_address_size, SOCK_CLOEXEC);
#endif // __linux__

#ifdef _WIN32
        auto client_socket = accept(m_Socket->get(),
            reinterpret_cast<sockaddr*>(&client_address),
            &client_address_size);
#endif // _WIN32
        eqx::ENSURE_HARD(client_socket != -1, "Error Accepting Connection!"sv);

        return Client(eqx::Socket(client_socket));
    }
}
