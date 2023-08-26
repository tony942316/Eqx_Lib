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

#ifndef PROVINGGROUNDS_TESTS_DETAILS_SUPERENUMTESTERIMPL_IPP
#define PROVINGGROUNDS_TESTS_DETAILS_SUPERENUMTESTERIMPL_IPP

#include "SuperEnumTesterDecl.hpp"

inline void SuperEnumTester::test()
{
    std::cout << "Testing Super Enum..." << std::endl;
    testStreaming();
    UnitTester::printStatus();
    UnitTester::clear();
}

void SuperEnumTester::testStreaming()
{
    using namespace std::literals;

    auto ss = std::stringstream();
    ss << SuperEnumShell::Pub3::v1;
    ss << SuperEnumShell::Pub3::v2;
    ss << SuperEnumShell::Pub3::v3;
    ss << SuperEnumShell::Pub5::v1;
    ss << SuperEnumShell::Pub5::v2;
    ss << SuperEnumShell::Pub5::v3;
    ss << SuperEnumShell::Pub5::v4;
    ss << SuperEnumShell::Pub5::v5;
    ss << SuperEnumShell::Pub7::v1;
    ss << SuperEnumShell::Pub7::v2;
    ss << SuperEnumShell::Pub7::v3;
    ss << SuperEnumShell::Pub7::v4;
    ss << SuperEnumShell::Pub7::v5;
    ss << SuperEnumShell::Pub7::v6;
    ss << SuperEnumShell::Pub7::v7;

    UnitTester::test(ss.str(), "v1v2v3v1v2v3v4v5v1v2v3v4v5v6v7"s);
}

constexpr void SuperEnumTester::testEnumCollection() noexcept
{
    using namespace std::literals;

    constexpr auto expected3 =
        std::array<EnumPair<SuperEnumShell::Pub3>, 3ULL>({
            { SuperEnumShell::Pub3::v1, "v1"sv },
            { SuperEnumShell::Pub3::v2, "v2"sv },
            { SuperEnumShell::Pub3::v3, "v3"sv } });
    static_assert(expected3 == SuperEnumShell::Pub3Collection);

    constexpr auto expected5 =
        std::array<EnumPair<SuperEnumShell::Pub5>, 5ULL>({
            { SuperEnumShell::Pub5::v1, "v1"sv },
            { SuperEnumShell::Pub5::v2, "v2"sv },
            { SuperEnumShell::Pub5::v3, "v3"sv },
            { SuperEnumShell::Pub5::v4, "v4"sv },
            { SuperEnumShell::Pub5::v5, "v5"sv } });
    static_assert(expected5 == SuperEnumShell::Pub5Collection);

    constexpr auto expected7 =
        std::array<EnumPair<SuperEnumShell::Pub7>, 7ULL>({
            { SuperEnumShell::Pub7::v1, "v1"sv },
            { SuperEnumShell::Pub7::v2, "v2"sv },
            { SuperEnumShell::Pub7::v3, "v3"sv },
            { SuperEnumShell::Pub7::v4, "v4"sv },
            { SuperEnumShell::Pub7::v5, "v5"sv },
            { SuperEnumShell::Pub7::v6, "v6"sv },
            { SuperEnumShell::Pub7::v7, "v7"sv } });
    static_assert(expected7 == SuperEnumShell::Pub7Collection);
}

constexpr void SuperEnumTester::testGetEnums() noexcept
{
    constexpr auto expected3 =
        std::array<SuperEnumShell::Pub3, 3ULL>({
            SuperEnumShell::Pub3::v1,
            SuperEnumShell::Pub3::v2,
            SuperEnumShell::Pub3::v3 });
    static_assert(expected3 == SuperEnumShell::getPub3Enums());

    constexpr auto expected5 =
        std::array<SuperEnumShell::Pub5, 5ULL>({
            SuperEnumShell::Pub5::v1,
            SuperEnumShell::Pub5::v2,
            SuperEnumShell::Pub5::v3,
            SuperEnumShell::Pub5::v4,
            SuperEnumShell::Pub5::v5 });
    static_assert(expected5 == SuperEnumShell::getPub5Enums());

    constexpr auto expected7 =
        std::array<SuperEnumShell::Pub7, 7ULL>({
            SuperEnumShell::Pub7::v1,
            SuperEnumShell::Pub7::v2,
            SuperEnumShell::Pub7::v3,
            SuperEnumShell::Pub7::v4,
            SuperEnumShell::Pub7::v5,
            SuperEnumShell::Pub7::v6,
            SuperEnumShell::Pub7::v7 });
    static_assert(expected7 == SuperEnumShell::getPub7Enums());
}

constexpr void SuperEnumTester::testGetString() noexcept
{
    using namespace std::literals;

    constexpr auto expected3 =
        std::array<std::string_view, 3ULL>({
            "v1"sv,
            "v2"sv,
            "v3"sv });
    static_assert(expected3 == SuperEnumShell::getPub3Strings());

    constexpr auto expected5 =
        std::array<std::string_view, 5ULL>({
            "v1"sv,
            "v2"sv,
            "v3"sv,
            "v4"sv,
            "v5"sv });
    static_assert(expected5 == SuperEnumShell::getPub5Strings());

    constexpr auto expected7 =
        std::array<std::string_view, 7ULL>({
            "v1"sv,
            "v2"sv,
            "v3"sv,
            "v4"sv,
            "v5"sv,
            "v6"sv,
            "v7"sv });
    static_assert(expected7 == SuperEnumShell::getPub7Strings());
}

#endif // PROVINGGROUNDS_TESTS_DETAILS_SUPERENUMTESTERIMPL_IPP
