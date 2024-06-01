export module Eqx.UnitTester:Decl;

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

    bool passing() noexcept;

    void print() noexcept;

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
