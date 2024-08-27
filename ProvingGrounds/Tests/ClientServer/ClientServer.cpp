export module Eqx.Tests.ClientServer;

import <Eqx/std.hpp>;

import Eqx.Lib.Misc;
import Eqx.Lib.Socket;
import Eqx.Lib.Client;
import Eqx.Lib.Server;
import Eqx.UnitTester;

namespace test::clientserver
{
    // NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
    constinit auto client = eqx::Client{};
    constinit auto server = eqx::Server{};
    // NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

    using namespace eqx::literals;
    constexpr auto port = 42'069_u16;

    export inline UnitTester all() noexcept;
    inline void sendReceive(UnitTester& tester) noexcept;
    inline std::string clientLoop() noexcept;
    inline std::string serverLoop() noexcept;
}

// Implementations

namespace test::clientserver
{
    export inline UnitTester all() noexcept
    {
        auto tester = UnitTester{};
        eqx::Socket::init();
        sendReceive(tester);
        return tester;
    }

    inline void sendReceive(UnitTester& tester) noexcept
    {
        auto serverTask = std::async(std::launch::async, serverLoop);
        std::this_thread::sleep_for(1'000ms);
        auto clientTask = std::async(std::launch::async, clientLoop);

        tester.addTest(serverTask.get(), "Hello Server!"s);
        tester.addTest(clientTask.get(), "Hello Client!"s);
    }

    inline std::string clientLoop() noexcept
    {
        client.connect("127.0.0.1", port);
        client.send("Hello Server!"sv);
        return client.recv();
    }

    inline std::string serverLoop() noexcept
    {
        server.start(port);
        auto subClient = server.getConnection();
        subClient.send("Hello Client!"sv);
        return subClient.recv();
    }
}
