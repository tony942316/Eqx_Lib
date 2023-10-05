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
    ss << FreeSuperEnum::Free3::v1;
    ss << FreeSuperEnum::Free3::v2;
    ss << FreeSuperEnum::Free3::v3;

    UnitTester::test(ss.str(), "v1v2v3v1v2v3v4v5v1v2v3v4v5v6v7v1v2v3"s);
}

constexpr void SuperEnumTester::testEnumCollection() noexcept
{
    using namespace std::literals;

    constexpr auto expected3 =
        std::array<std::pair<SuperEnumShell::Pub3, std::string_view>, 3ULL>({
            { SuperEnumShell::Pub3::v1, "v1"sv },
            { SuperEnumShell::Pub3::v2, "v2"sv },
            { SuperEnumShell::Pub3::v3, "v3"sv } });
    static_assert(expected3 == SuperEnumShell::p_Pub3Collection);

    constexpr auto expected5 =
        std::array<std::pair<SuperEnumShell::Pub5, std::string_view>, 5ULL>({
            { SuperEnumShell::Pub5::v1, "v1"sv },
            { SuperEnumShell::Pub5::v2, "v2"sv },
            { SuperEnumShell::Pub5::v3, "v3"sv },
            { SuperEnumShell::Pub5::v4, "v4"sv },
            { SuperEnumShell::Pub5::v5, "v5"sv } });
    static_assert(expected5 == SuperEnumShell::p_Pub5Collection);

    constexpr auto expected7 =
        std::array<std::pair<SuperEnumShell::Pub7, std::string_view>, 7ULL>({
            { SuperEnumShell::Pub7::v1, "v1"sv },
            { SuperEnumShell::Pub7::v2, "v2"sv },
            { SuperEnumShell::Pub7::v3, "v3"sv },
            { SuperEnumShell::Pub7::v4, "v4"sv },
            { SuperEnumShell::Pub7::v5, "v5"sv },
            { SuperEnumShell::Pub7::v6, "v6"sv },
            { SuperEnumShell::Pub7::v7, "v7"sv } });
    static_assert(expected7 == SuperEnumShell::p_Pub7Collection);

    constexpr auto fExpected3 =
        std::array<std::pair<FreeSuperEnum::Free3, std::string_view>, 3ULL>({
            { FreeSuperEnum::Free3::v1, "v1"sv },
            { FreeSuperEnum::Free3::v2, "v2"sv },
            { FreeSuperEnum::Free3::v3, "v3"sv } });
    static_assert(fExpected3 == FreeSuperEnum::p_Free3Collection);
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

    constexpr auto fExpected3 =
        std::array<FreeSuperEnum::Free3, 3ULL>({
            FreeSuperEnum::Free3::v1,
            FreeSuperEnum::Free3::v2,
            FreeSuperEnum::Free3::v3 });
    static_assert(fExpected3 == FreeSuperEnum::getFree3Enums());
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

    constexpr auto fExpected3 =
        std::array<std::string_view, 3ULL>({
            "v1"sv,
            "v2"sv,
            "v3"sv });
    static_assert(fExpected3 == FreeSuperEnum::getFree3Strings());
}

constexpr void SuperEnumTester::testToEnum() noexcept
{
    using namespace std::literals;

    constexpr auto expected3 = SuperEnumShell::Pub3::v2;
    static_assert(expected3 == SuperEnumShell::Pub3ToEnum("v2"sv));
    static_assert(expected3 != SuperEnumShell::Pub3ToEnum("v1"sv));

    constexpr auto expected5 = SuperEnumShell::Pub5::v5;
    static_assert(expected5 == SuperEnumShell::Pub5ToEnum("v5"sv));

    constexpr auto expected7 = SuperEnumShell::Pub7::v1;
    static_assert(expected7 == SuperEnumShell::Pub7ToEnum("v1"sv));

    constexpr auto fExpected3 = FreeSuperEnum::Free3::v3;
    static_assert(fExpected3 == FreeSuperEnum::Free3ToEnum("v3"sv));

    constexpr auto expected3All = SuperEnumShell::getPub3Enums();
    constexpr auto actual3All = SuperEnumShell::getPub3Strings() |
        std::views::transform(SuperEnumShell::Pub3ToEnum);
    static_assert(std::ranges::equal(expected3All, actual3All));

    constexpr auto expected5All = SuperEnumShell::getPub5Enums();
    constexpr auto actual5All = SuperEnumShell::getPub5Strings() |
        std::views::transform(SuperEnumShell::Pub5ToEnum);
    static_assert(std::ranges::equal(expected5All, actual5All));

    constexpr auto expected7All = SuperEnumShell::getPub7Enums();
    constexpr auto actual7All = SuperEnumShell::getPub7Strings() |
        std::views::transform(SuperEnumShell::Pub7ToEnum);
    static_assert(std::ranges::equal(expected7All, actual7All));

    constexpr auto fExpected3All = FreeSuperEnum::getFree3Enums();
    constexpr auto fActual3All = FreeSuperEnum::getFree3Strings() |
        std::views::transform(FreeSuperEnum::Free3ToEnum);
    static_assert(std::ranges::equal(fExpected3All, fActual3All));
}

#endif // PROVINGGROUNDS_TESTS_DETAILS_SUPERENUMTESTERIMPL_IPP
