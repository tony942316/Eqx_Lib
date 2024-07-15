export module Eqx.UnitTester;

import Eqx.Stdm;

export class UnitTester
{
public:
    explicit consteval UnitTester() noexcept;

    template <typename T, typename U,
        typename Cmp = decltype(stdm::ranges::equal_to{})>
    void addTest(const T& val1, const U& val2,
        const Cmp& cmp = stdm::ranges::equal_to{},
        const stdm::string_view info = ""sv,
        const stdm::source_location& loc = stdm::source_location::current())
        noexcept;

    template <typename T, typename U,
        typename Cmp = decltype(stdm::ranges::equal_to{})>
    void addTests(const stdm::vector<stdm::pair<T, U>>& expected_actual,
        const Cmp& cmp = stdm::ranges::equal_to{},
        const stdm::string_view info = ""sv,
        const stdm::source_location& loc = stdm::source_location::current())
        noexcept;

    inline bool passing() noexcept;

    inline stdm::string toString(
        const stdm::string_view name = "N.A."sv) noexcept;
    inline void print(const stdm::string_view name = "N.A."sv) noexcept;

private:
    template <typename T, typename U, typename Cmp>
    static stdm::string eStr(const T& val1, const U& val2, const Cmp& cmp,
        const stdm::string_view info,
        const stdm::source_location& loc) noexcept;

    template <typename T, typename U, typename Cmp>
    static stdm::string testStr(const T& val1, const U& val2,
        const Cmp& cmp) noexcept;

    template <typename T>
    static stdm::string fts([[maybe_unused]] const T& cmp) noexcept;

    stdm::optional<stdm::vector<stdm::string>> m_FailedTests;
    stdm::size_t m_TotalTests;
};

// Implementations

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

inline bool UnitTester::passing() noexcept
{
    if (!m_FailedTests.has_value())
    {
        m_FailedTests.emplace();
    }
    return stdm::ranges::empty(*m_FailedTests);
}

inline stdm::string UnitTester::toString(const stdm::string_view name) noexcept
{
    static constexpr auto limit = 5;

    if (!m_FailedTests.has_value())
    {
        m_FailedTests.emplace();
    }

    auto result = stdm::string{};

    result += "Testing "sv;
    result += name;
    result += "... "sv;
    result += stdm::to_string(m_TotalTests
        - stdm::ranges::size(*m_FailedTests));
    result += '/';
    result += stdm::to_string(m_TotalTests);
    result += '\n';

    stdm::ranges::for_each(*m_FailedTests | stdm::views::take(limit),
        [&result](const stdm::string_view str)
        {
            result += "======================\n"sv;
            result += str;
            result += '\n';
            result += "======================\n"sv;
        });

    return result;
}

inline void UnitTester::print(const stdm::string_view name) noexcept
{
    stdm::cout << toString(name);
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
    else if constexpr (stdm::same_as<T, decltype(stdm::ranges::less_equal{})>)
    {
        return " <= "s;
    }
    else if constexpr (stdm::same_as<T, decltype(stdm::ranges::greater{})>)
    {
        return " > "s;
    }
    else if constexpr (stdm::same_as<T,
        decltype(stdm::ranges::greater_equal{})>)
    {
        return " >= "s;
    }
    else if constexpr (stdm::same_as<T, decltype(stdm::compare_three_way{})>)
    {
        return " <=> "s;
    }
    else
    {
        return " ?? "s;
    }
}
