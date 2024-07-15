export module Eqx.Tests.Math;

import :Core;
import :Modulator;
import :Range;
import :Trig;

import Eqx.Stdm;
import Equinox.Math;
import Eqx.UnitTester;

namespace test::math
{
    export inline UnitTester all() noexcept;
    /*
    void sin() noexcept;
    void cos() noexcept;
    void asin() noexcept;
    void acos() noexcept;
    */
}

// Implementations

namespace test::math
{
    export inline UnitTester all() noexcept
    {
        auto tester = UnitTester{};
        /*
        sin();
        cos();
        asin();
        acos();
        */
        return tester;
    }

    /*
    void sin() noexcept
    {
        static constexpr auto val = (8.0 * stdm::numbers::pi);
        static constexpr auto inc = 0.01;
        static constexpr auto cnt =
            static_cast<stdm::size_t>(eqx::ceil((2 * val / inc)) + 1);
        static constexpr auto myValues = stdm::invoke([]() consteval
            {
                auto result = stdm::array<double, cnt>{};
                auto i = 0ULL;
                for (auto v = -val; v < val; v += inc)
                {
                    result.at(i) = eqx::sin(v);
                    i++;
                }
                return result;
            });
        auto result = stdm::array<double, cnt>{};
        auto i = 0ULL;
        for (auto v = -val; v < val; v += inc)
        {
            result.at(i) = stdm::abs(stdm::sin(v) - myValues.at(i));
            i++;
        }

        stdm::ranges::sort(result);

        tester.addTest(eqx::average(result), 0.00001, stdm::ranges::less{},
            "Average Error"sv);
        tester.addTest(eqx::median(result), 0.00001, stdm::ranges::less{},
            "Median Error"sv);
        tester.addTest(stdm::ranges::max(result), 0.00001, stdm::ranges::less{},
            "Max Error"sv);
        tester.addTest(stdm::ranges::min(result), 0.00001, stdm::ranges::less{},
            "Min Error"sv);
    }

    void cos() noexcept
    {
        static constexpr auto val = (8.0 * stdm::numbers::pi);
        static constexpr auto inc = 0.01;
        static constexpr auto cnt =
            static_cast<stdm::size_t>(eqx::ceil((2 * val / inc)) + 1);
        static constexpr auto myValues = stdm::invoke([]() consteval
            {
                auto result = stdm::array<double, cnt>{};
                auto i = 0ULL;
                for (auto v = -val; v < val; v += inc)
                {
                    result.at(i) = eqx::cos(v);
                    i++;
                }
                return result;
            });
        auto result = stdm::array<double, cnt>{};
        auto i = 0ULL;
        for (auto v = -val; v < val; v += inc)
        {
            result.at(i) = stdm::abs(stdm::cos(v) - myValues.at(i));
            i++;
        }

        stdm::ranges::sort(result);

        tester.addTest(eqx::average(result), 0.00001, stdm::ranges::less{},
            "Average Error"sv);
        tester.addTest(eqx::median(result), 0.00001, stdm::ranges::less{},
            "Median Error"sv);
        tester.addTest(stdm::ranges::max(result), 0.00001, stdm::ranges::less{},
            "Max Error"sv);
        tester.addTest(stdm::ranges::min(result), 0.00001, stdm::ranges::less{},
            "Min Error"sv);
    }

    void asin() noexcept
    {
        static constexpr auto val = 1.0;
        static constexpr auto inc = 0.01;
        static constexpr auto cnt =
            static_cast<stdm::size_t>(eqx::ceil((2 * val / inc)) + 1);
        static constexpr auto myValues = stdm::invoke([]() consteval
            {
                auto result = stdm::array<double, cnt>{};
                auto i = static_cast<stdm::size_t>(0ULL);
                for (auto v = -val; v < val; v += inc)
                {
                    result.at(i) = eqx::asin(v);
                    i++;
                }
                return result;
            });

        auto result = stdm::array<double, cnt>{};
        auto i = static_cast<stdm::size_t>(0ULL);
        for (auto v = -val; v < val; v += inc)
        {
            result.at(i) = stdm::abs(stdm::asin(v) - myValues.at(i));
            i++;
        }

        stdm::ranges::sort(result);

        tester.addTest(eqx::average(result), 0.00001, stdm::ranges::less{},
            "Average Error"sv);
        tester.addTest(eqx::median(result), 0.00001, stdm::ranges::less{},
            "Median Error"sv);
        tester.addTest(stdm::ranges::max(result), 0.00001, stdm::ranges::less{},
            "Max Error"sv);
        tester.addTest(stdm::ranges::min(result), 0.00001, stdm::ranges::less{},
            "Min Error"sv);
    }

    void acos() noexcept
    {
        static constexpr auto val = 1.0;
        static constexpr auto inc = 0.01;
        static constexpr auto cnt =
            static_cast<stdm::size_t>(eqx::ceil((2 * val / inc)) + 1);
        static constexpr auto myValues = stdm::invoke([]() consteval
            {
                auto result = stdm::array<double, cnt>{};
                auto i = static_cast<stdm::size_t>(0ULL);
                for (auto v = -val; v < val; v += inc)
                {
                    result.at(i) = eqx::acos(v);
                    i++;
                }
                return result;
            });

        auto result = stdm::array<double, cnt>{};
        auto i = static_cast<stdm::size_t>(0ULL);
        for (auto v = -val; v < val; v += inc)
        {
            result.at(i) = stdm::abs(stdm::acos(v) - myValues.at(i));
            i++;
        }

        stdm::ranges::sort(result);

        tester.addTest(eqx::average(result), 0.00001, stdm::ranges::less{},
            "Average Error"sv);
        tester.addTest(eqx::median(result), 0.00001, stdm::ranges::less{},
            "Median Error"sv);
        tester.addTest(stdm::ranges::max(result), 0.00001, stdm::ranges::less{},
            "Max Error"sv);
        tester.addTest(stdm::ranges::min(result), 0.00001, stdm::ranges::less{},
            "Min Error"sv);
    }
    */
}
