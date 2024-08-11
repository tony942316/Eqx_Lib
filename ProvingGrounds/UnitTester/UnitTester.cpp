export module Eqx.UnitTester;

import Eqx.Stdm;

export class UnitTester
{
public:
    explicit constexpr UnitTester() noexcept;

    template <typename T, typename U,
        typename Cmp = decltype(std::ranges::equal_to{})>
    void addTest(const T& val1, const U& val2,
        const Cmp& cmp = std::ranges::equal_to{},
        const std::string_view info = ""sv,
        const std::source_location& loc = std::source_location::current())
        noexcept;

    template <typename T, typename U,
        typename Cmp = decltype(std::ranges::equal_to{})>
    void addTests(const std::vector<std::pair<T, U>>& expected_actual,
        const Cmp& cmp = std::ranges::equal_to{},
        const std::string_view info = ""sv,
        const std::source_location& loc = std::source_location::current())
        noexcept;

    inline bool passing() noexcept;

    inline std::string toString(
        const std::string_view name = "N.A."sv) noexcept;
    inline void print(const std::string_view name = "N.A."sv) noexcept;

private:
    template <typename T, typename U, typename Cmp>
    static std::string eStr(const T& val1, const U& val2, const Cmp& cmp,
        const std::string_view info,
        const std::source_location& loc) noexcept;

    template <typename T, typename U, typename Cmp>
    static std::string testStr(const T& val1, const U& val2,
        const Cmp& cmp) noexcept;

    template <typename T>
    static std::string fts([[maybe_unused]] const T& cmp) noexcept;

    std::optional<std::vector<std::string>> m_FailedTests;
    std::size_t m_TotalTests;
};

// Implementations

constexpr UnitTester::UnitTester() noexcept
    :
    m_TotalTests(static_cast<std::size_t>(0))
{
}

template <typename T, typename U, typename Cmp>
void UnitTester::addTest(const T& val1, const U& val2, const Cmp& cmp,
    const std::string_view info, const std::source_location& loc) noexcept
{
    ++m_TotalTests;
    if (!m_FailedTests.has_value())
    {
        m_FailedTests.emplace();
    }

    if (!std::invoke(cmp, val1, val2))
    {
        m_FailedTests->emplace_back(
            eStr(val1, val2, cmp, info, loc));
    }
}

template <typename T, typename U, typename Cmp>
void UnitTester::addTests(const std::vector<std::pair<T, U>>& expected_actual,
    const Cmp& cmp, const std::string_view info,
    const std::source_location& loc) noexcept
{
    std::ranges::for_each(expected_actual,
        [&](const std::pair<T, U>& values)
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
    return std::ranges::empty(*m_FailedTests);
}

inline std::string UnitTester::toString(const std::string_view name) noexcept
{
    static constexpr auto limit = 5;

    if (!m_FailedTests.has_value())
    {
        m_FailedTests.emplace();
    }

    auto result = std::string{};

    result += "Testing "sv;
    result += name;
    result += "... "sv;
    result += std::to_string(m_TotalTests
        - std::ranges::size(*m_FailedTests));
    result += '/';
    result += std::to_string(m_TotalTests);
    result += '\n';

    std::ranges::for_each(*m_FailedTests | std::views::take(limit),
        [&result](const std::string_view str)
        {
            result += "======================\n"sv;
            result += str;
            result += '\n';
            result += "======================\n"sv;
        });

    return result;
}

inline void UnitTester::print(const std::string_view name) noexcept
{
    std::cout << toString(name);
}

template <typename T, typename U, typename Cmp>
std::string UnitTester::eStr(const T& val1, const U& val2, const Cmp& cmp,
    const std::string_view info, const std::source_location& loc) noexcept
{
    auto ss = std::stringstream{};
    auto fileName = std::filesystem::path{loc.file_name()}.filename().string();

    ss << "Test Failure! ->\n"
        << "Test: " << testStr(val1, val2, cmp) << '\n'
        << "File: " << fileName << '\n'
        << "Function: " << loc.function_name() << '\n'
        << "Line: " << loc.line();

    if (!std::ranges::empty(info))
    {
        ss << "\nInfo: " << info;
    }

    return ss.str();
}

template <typename T, typename U, typename Cmp>
std::string UnitTester::testStr(const T& val1, const U& val2,
    const Cmp& cmp) noexcept
{
    auto ss = std::stringstream{};
    if constexpr (requires(const T& val) { std::stringstream{} << val; })
    {
        ss << val1;
    }
    else
    {
        ss << "??"sv;
    }

    ss << fts(cmp);

    if constexpr (requires(const U& val) { std::stringstream{} << val; })
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
std::string UnitTester::fts([[maybe_unused]] const T& cmp) noexcept
{
    if constexpr (std::same_as<T, decltype(std::ranges::equal_to{})>)
    {
        return " == "s;
    }
    else if constexpr (std::same_as<T, decltype(std::ranges::not_equal_to{})>)
    {
        return " != "s;
    }
    else if constexpr (std::same_as<T, decltype(std::ranges::less{})>)
    {
        return " < "s;
    }
    else if constexpr (std::same_as<T, decltype(std::ranges::less_equal{})>)
    {
        return " <= "s;
    }
    else if constexpr (std::same_as<T, decltype(std::ranges::greater{})>)
    {
        return " > "s;
    }
    else if constexpr (std::same_as<T,
        decltype(std::ranges::greater_equal{})>)
    {
        return " >= "s;
    }
    else if constexpr (std::same_as<T, decltype(std::compare_three_way{})>)
    {
        return " <=> "s;
    }
    else
    {
        return " ?? "s;
    }
}
