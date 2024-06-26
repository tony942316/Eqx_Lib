export module Eqx.UnitTester;

export import :Decl;

import Eqx.Stdm;

consteval UnitTester::UnitTester() noexcept
    :
    m_TotalTests(static_cast<stdm::size_t>(0))
{
}

template <typename T, typename U, typename Cmp>
void UnitTester::addTest(const T& val1, const U& val2, const Cmp& cmp,
    const stdm::string_view info, const stdm::source_location& loc) noexcept
{
    ++m_TotalTests;
    if (!m_FailedTests.has_value())
    {
        m_FailedTests.emplace();
    }

    if (!stdm::invoke(cmp, val1, val2))
    {
        m_FailedTests->emplace_back(
            eStr(val1, val2, cmp, info, loc));
    }
}

template <typename T, typename U, typename Cmp>
void UnitTester::addTests(const stdm::vector<stdm::pair<T, U>>& expected_actual,
    const Cmp& cmp, const stdm::string_view info,
    const stdm::source_location& loc) noexcept
{
    stdm::ranges::for_each(expected_actual,
        [&](const stdm::pair<T, U>& values)
        {
            addTest(values.first, values.second, cmp, info, loc);
        });
}

bool UnitTester::passing() noexcept
{
    return stdm::ranges::empty(*m_FailedTests);
}

void UnitTester::print() noexcept
{
    if (passing())
    {
        stdm::cout << "All Pass!\n";
    }
    else
    {
        static constexpr auto c_Limit = 5;
        stdm::ranges::for_each(*m_FailedTests | stdm::views::take(c_Limit),
            [](const stdm::string_view str)
            {
                stdm::cout << str << '\n'
                    << "===================\n";
            });
    }
    stdm::cout << "-------------------\n"
        << "Total: " << m_TotalTests - stdm::ranges::size(*m_FailedTests)
        << '/' << m_TotalTests << '\n';
}

template <typename T, typename U, typename Cmp>
stdm::string UnitTester::eStr(const T& val1, const U& val2, const Cmp& cmp,
    const stdm::string_view info, const stdm::source_location& loc) noexcept
{
    auto ss = stdm::stringstream{};
    auto fileName = stdm::filesystem::path{loc.file_name()}.filename().string();

    ss << "Test Failure! ->\n"
        << "Test: " << testStr(val1, val2, cmp) << '\n'
        << "File: " << fileName << '\n'
        << "Function: " << loc.function_name() << '\n'
        << "Line: " << loc.line();

    if (!stdm::ranges::empty(info))
    {
        ss << "\nInfo: " << info;
    }

    return ss.str();
}

template <typename T, typename U, typename Cmp>
stdm::string UnitTester::testStr(const T& val1, const U& val2,
    const Cmp& cmp) noexcept
{
    auto ss = stdm::stringstream{};
    if constexpr (requires(const T& val) { stdm::stringstream{} << val; })
    {
        ss << val1;
    }
    else
    {
        ss << "??"sv;
    }

    ss << fts(cmp);

    if constexpr (requires(const U& val) { stdm::stringstream{} << val; })
    {
        ss << val2;
    }
    else
    {
        ss << "??"sv;
    }
    return ss.str();
}

template <typename T>
stdm::string UnitTester::fts([[maybe_unused]] const T& cmp) noexcept
{
    if constexpr (stdm::same_as<T, decltype(stdm::ranges::equal_to{})>)
    {
        return " == "s;
    }
    else if constexpr (stdm::same_as<T, decltype(stdm::ranges::not_equal_to{})>)
    {
        return " != "s;
    }
    else if constexpr (stdm::same_as<T, decltype(stdm::ranges::less{})>)
    {
        return " < "s;
    }
    else
    {
        return " ?? "s;
    }
}
