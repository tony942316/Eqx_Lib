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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_LOGTESTERIMPL_IPP
#define PROVINGGROUNDS_TESTS_DETAILS_LOGTESTERIMPL_IPP

#include "LogTesterDecl.hpp"

inline void LogTester::test()
{
    std::cout << "Testing Log..." << std::endl;
    if (!eqx::Log::isInit())
    {
        eqx::Log::init();
    }
    const auto prevLogLevel = eqx::Log::getCurrentLogLevel();
    testLog();
    testSetLevel();
    testSetOutputStream();
    testSetOutputFile();
    testClear();
    testGetFormattedString();
    UnitTester::printStatus();
    UnitTester::clear();
    eqx::Log::setLevel(prevLogLevel);
    auto cleanFile = std::ofstream("Log.txt",
        std::ios::out | std::ios::trunc);
    cleanFile.close();
}

inline void LogTester::testLog()
{
    using namespace std::literals;

    auto ss = std::stringstream();
    auto produced = std::string("");
    const auto loc = std::source_location::current();
    eqx::Log::setOutputStream(&ss);
    eqx::Log::setLevel(eqx::Log::Level::All);

    eqx::Log::log(eqx::Log::Level::Error, "TestLog"sv, eqx::Log::Type::None,
        loc);
    eqx::Log::log(eqx::Log::Level::Warning, "TestLog"sv, eqx::Log::Type::None,
        loc);

    std::getline(ss, produced);
    UnitTester::test(produced,
        eqx::Log::getFormattedString(loc, eqx::Log::Level::Error,
        "TestLog"sv));
    std::getline(ss, produced);
    UnitTester::test(produced,
        eqx::Log::getFormattedString(loc, eqx::Log::Level::Warning,
        "TestLog"sv));

    eqx::Log::log(eqx::Log::Level::Error, "TestLog"sv,
        eqx::Log::Type::RuntimeError);
    UnitTester::test(eqx::Log::getLastLogType(), eqx::Log::Type::RuntimeError);
}

inline void LogTester::testSetLevel()
{
    eqx::Log::setLevel(eqx::Log::Level::All);
    UnitTester::test(eqx::Log::getCurrentLogLevel(), eqx::Log::Level::All);
    eqx::Log::setLevel(eqx::Log::Level::Info);
    UnitTester::test(eqx::Log::getCurrentLogLevel(), eqx::Log::Level::Info);
    eqx::Log::setLevel(eqx::Log::Level::Warning);
    UnitTester::test(eqx::Log::getCurrentLogLevel(), eqx::Log::Level::Warning);
    eqx::Log::setLevel(eqx::Log::Level::Error);
    UnitTester::test(eqx::Log::getCurrentLogLevel(), eqx::Log::Level::Error);
    eqx::Log::setLevel(eqx::Log::Level::None);
    UnitTester::test(eqx::Log::getCurrentLogLevel(), eqx::Log::Level::None);
}

inline void LogTester::testSetOutputStream()
{
    using namespace std::literals;

    auto ss = std::stringstream();
    auto produced = std::string("");
    eqx::Log::setLevel(eqx::Log::Level::All);
    eqx::Log::setOutputStream(&ss);

    eqx::Log::log(eqx::Log::Level::Error, "testOutputStream"sv);
    std::getline(ss, produced);
    UnitTester::test(produced, ""s, UnitTesterFunctions::NE);

    auto ss2 = std::stringstream();
    eqx::Log::setOutputStream(&ss2);

    eqx::Log::log(eqx::Log::Level::Error, "testOutputStream"sv);
    std::getline(ss2, produced);
    UnitTester::test(produced, ""s, UnitTesterFunctions::NE);

    std::getline(ss, produced);
    UnitTester::test(produced, ""s);
}

inline void LogTester::testSetOutputFile()
{
    using namespace std::literals;

    auto ss = std::stringstream();
    auto produced = std::string("");
    const auto loc = std::source_location::current();
    eqx::Log::setLevel(eqx::Log::Level::All);
    eqx::Log::setOutputStream(&ss);
    eqx::Log::setOutputFile("TestOutputFile.txt"sv);

    eqx::Log::log(eqx::Log::Level::Error, "testOutputFile"sv,
        eqx::Log::Type::None, loc);
    eqx::Log::setOutputFile("Log.txt"sv);

    auto file = std::ifstream("TestOutputFile.txt"s, std::ios::in);
    std::getline(file, produced);

    UnitTester::test(produced, eqx::Log::getFormattedString(loc,
        eqx::Log::Level::Error, "testOutputFile"sv));
    file.close();
}

inline void LogTester::testClear()
{
    using namespace std::literals;

    auto ss = std::stringstream();
    eqx::Log::setOutputStream(&ss);
    eqx::Log::setLevel(eqx::Log::Level::All);

    eqx::Log::log(eqx::Log::Level::Error, "testClear"sv,
        eqx::Log::Type::RuntimeError);

    UnitTester::test(eqx::Log::getLastLogType(), eqx::Log::Type::RuntimeError);
    UnitTester::test(eqx::Log::getLastLogMessage(), "testClear"sv);
    eqx::Log::clear();
    UnitTester::test(eqx::Log::getLastLogType(), eqx::Log::Type::None);
    UnitTester::test(eqx::Log::getLastLogMessage(), ""sv);
}

inline void LogTester::testGetFormattedString()
{
    using namespace std::literals;

    const auto loc = std::source_location::current();
    auto lineNumber = std::to_string(loc.line());

    auto produced = eqx::Log::getFormattedString(loc, eqx::Log::Level::Error,
        "testFString"sv);
    auto expected = std::string("../LogTesterImpl.ipp"sv);
    expected += "("sv;
    expected += loc.function_name();
    expected += ","sv;
    expected += lineNumber;
    expected += ") [ERROR]: testFString"sv;

    UnitTester::test(produced, expected);
}

constexpr void LogTester::testGetLoggableLevels() noexcept
{
    constexpr auto produced = eqx::Log::getLoggableLevels();
    constexpr auto expected = std::array<eqx::Log::Level, 3ULL>({
        eqx::Log::Level::Info,
        eqx::Log::Level::Warning,
        eqx::Log::Level::Error });
    static_assert(produced == expected);
}

#endif // PROVINGGROUNDS_TESTS_DETAILS_LOGTESTERIMPL_IPP
