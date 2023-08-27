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

#ifndef PROVINGGROUNDS_TESTS_CLIENTSERVERTESTERIMPL_IPP
#define PROVINGGROUNDS_TESTS_CLIENTSERVERTESTERIMPL_IPP

#include "ClientServerTesterDecl.hpp"

inline void ClientServerTester::test()
{
    std::cout << "Testing Client And Server..." << std::endl;
#ifdef __linux__
    testSendReceive();
#endif // __linux__
    UnitTester::printStatus();
    UnitTester::clear();
}

inline void ClientServerTester::testSendReceive()
{
    using namespace std::literals;
    auto serverTask = std::async(std::launch::async, serverLoop);
    auto clientTask = std::async(std::launch::async, clientLoop);

    //auto serverData = serverTask.get();
    //auto clientData = clientTask.get();

    UnitTester::test(serverTask.get(), "Hello Server!"s);
    UnitTester::test(clientTask.get(), "Hello Client!"s);
}

inline std::string ClientServerTester::clientLoop()
{
    auto client = eqx::Client("127.0.0.1", 4'000);
    client.send("Hello Server!");
    return client.receive();
}

inline std::string ClientServerTester::serverLoop()
{
    auto server = eqx::Server(4'000);
    server.send("Hello Client!");
    return server.receive();
}

#endif // PROVINGGROUNDS_TESTS_CLIENTSERVERTESTERIMPL_IPP

