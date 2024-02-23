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
    testSendReceive();
    UnitTester::printStatus();
    UnitTester::clear();
}

inline void ClientServerTester::testSendReceive()
{
    using namespace std::literals;
    auto serverTask = std::async(std::launch::async, serverLoop);
    std::this_thread::sleep_for(1'000ms);
    auto clientTask = std::async(std::launch::async, clientLoop);

    UnitTester::test(serverTask.get(), "Hello Server!"s);
    UnitTester::test(clientTask.get(), "Hello Client!"s);
}

inline std::string ClientServerTester::clientLoop()
{
    using namespace eqx::literals;
    auto client = eqx::Client("127.0.0.1"sv, 42'069_u16);
    client.send("Hello Server!"sv);
    return client.recv();
}

inline std::string ClientServerTester::serverLoop()
{
    using namespace eqx::literals;
    auto server = eqx::Server(42'069_u16);
    auto client = server.getConnection();
    client.send("Hello Client!"sv);
    return client.recv();
}

#endif // PROVINGGROUNDS_TESTS_CLIENTSERVERTESTERIMPL_IPP
