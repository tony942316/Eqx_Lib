module;

#include <Equinox/Macros.hpp>

export module Equinox.Math.Trig;

export import :Decl;

import Eqx.Stdm;
import Equinox.Misc;
import Equinox.Math.Core;

export namespace eqx
{
    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T degreesToRadians(const T degrees) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return degrees * (stdm::numbers::pi_v<T> / static_cast<T>(180.0));
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T radiansToDegrees(const T radians) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return radians * (static_cast<T>(180.0) / stdm::numbers::pi_v<T>);
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T angAbs(const T radians) noexcept
    {
        eqx::ENSURE_HARD(radians < eqx::c_Zero<T>,
            "Only Defined For Negative Numbers!!!"sv);
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return (static_cast<T>(2.0) * stdm::numbers::pi_v<T>) + radians;
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T sin(const T radians) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            constexpr auto terms = 7;
            constexpr auto taylordeg = (terms * 4) + 1;
            auto mod = eqx::abs(eqx::fmod(radians, 2 * stdm::numbers::pi_v<T>));
            auto result = eqx::c_Zero<T>;

            for (auto i = 1; i < taylordeg; i += 4)
            {
                result -= eqx::pow(mod - stdm::numbers::pi_v<T>,
                    static_cast<T>(i)) / static_cast<T>(eqx::factorial(i));
                result += eqx::pow(mod - stdm::numbers::pi_v<T>,
                    static_cast<T>(i + 2))
                    / static_cast<T>(eqx::factorial(i + 2));
            }

            return radians < eqx::c_Zero<T> ? -result : result;
        }
        else
        {
            return stdm::sin(radians);
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T cos(const T radians) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            return eqx::sin(radians
                + (stdm::numbers::pi_v<T> / static_cast<T>(2)));
        }
        else
        {
            return stdm::cos(radians);
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T asin(const T val) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
            return -eqx::acos(val)
                + (stdm::numbers::pi_v<T> / static_cast<T>(2.0));
            // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        }
        else
        {
            return stdm::asin(val);
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr T acos(const T val) noexcept
    {
        if (stdm::is_constant_evaluated())
        {
            eqx::ENSURE_HARD(val >= static_cast<T>(-1.0)
                && val <= static_cast<T>(1.0),
                "Domain Error!"sv);
            // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
            //auto vax = (static_cast<T>(-1.3) * val)
                //+ (stdm::numbers::pi_v<T> / static_cast<T>(2.0));
            auto vax = (static_cast<T>(-0.95) * (eqx::sin(val) / eqx::cos(val)))
                + (stdm::numbers::pi_v<T> / static_cast<T>(2.0));
            for (auto i = 0; i < 10; i++)
            {
                vax = vax - ((eqx::cos(vax) - val) / (-eqx::sin(vax)));
            }
            return vax;
            // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        }
        else
        {
            eqx::ENSURE_HARD(val >= static_cast<T>(-1.0)
                && val <= static_cast<T>(1.0),
                "Domain Error!"sv);
            return stdm::acos(val);
        }
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr stdm::pair<T, T> arcsin(const T val) noexcept
    {
        constexpr auto pi2 = stdm::numbers::pi_v<T> / static_cast<T>(2.0);
        auto result = arccos(val);
        return stdm::make_pair(-result.first + pi2 < 0 ?
                eqx::angAbs(-result.first + pi2) : -result.first + pi2,
            eqx::angAbs(-result.second + pi2));
    }

    template <typename T>
        requires stdm::floating_point<T>
    [[nodiscard]] constexpr stdm::pair<T, T> arccos(const T val) noexcept
    {
        auto result = acos(val);
        return stdm::make_pair(result, eqx::angAbs(-result));
    }
}
