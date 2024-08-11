



#ifndef EQX_Math_Trig_123
#define EQX_Math_Trig_123


#include <stdh.hpp>
#include <Equinox/Misc/Misc.hpp>
#include <Equinox/Math/Core.hpp>
#include <Equinox/Math/Modulator.hpp>

namespace eqx
{
    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> degreesToRadians(
        const eqx::Degrees<T> degrees) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr eqx::Degrees<T> radiansToDegrees(
        const eqx::Radians<T> radians) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr T sin(const eqx::Radians<T> radians) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr T cos(const eqx::Radians<T> radians) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr T tan(const eqx::Radians<T> radians) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> asin(const T val) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> acos(const T val) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> atan(const T val) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> atan2(const T val) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr std::pair<eqx::Radians<T>, eqx::Radians<T>> arcsin(
        const T val) noexcept;

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr std::pair<eqx::Radians<T>, eqx::Radians<T>> arccos(
        const T val) noexcept;
}

// Implementations

namespace eqx
{
    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr
        eqx::Radians<T> degreesToRadians(const eqx::Degrees<T> degrees) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return eqx::Radians<T>{
            degrees.get()
            * (std::numbers::pi_v<T> / static_cast<T>(180.0))};
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr
        eqx::Degrees<T> radiansToDegrees(const eqx::Radians<T> radians) noexcept
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        return eqx::Degrees<T>{
            radians.get()
            * (static_cast<T>(180.0) / std::numbers::pi_v<T>)};
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr T sin(const eqx::Radians<T> radians) noexcept
    {
        if (std::is_constant_evaluated())
        {
            constexpr auto terms = 7;
            constexpr auto taylordeg = (terms * 4) + 1;
            auto result = eqx::c_Zero<T>;

            for (auto i = 1; i < taylordeg; i += 4)
            {
                result -= eqx::pow(radians.get() - std::numbers::pi_v<T>,
                    static_cast<T>(i)) / static_cast<T>(eqx::factorial(i));
                result += eqx::pow(radians.get() - std::numbers::pi_v<T>,
                    static_cast<T>(i + 2))
                    / static_cast<T>(eqx::factorial(i + 2));
            }

            return result;
        }
        else
        {
            return std::sin(radians.get());
        }
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr T cos(const eqx::Radians<T> radians) noexcept
    {
        if (std::is_constant_evaluated())
        {
            return eqx::sin(eqx::Radians<T>{radians.get()
                + (std::numbers::pi_v<T> / static_cast<T>(2))});
        }
        else
        {
            return std::cos(radians.get());
        }
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr T tan(const eqx::Radians<T> radians) noexcept
    {
        if (std::is_constant_evaluated())
        {
            return eqx::sin(radians) / eqx::cos(radians);
        }
        else
        {
            return std::tan(radians.get());
        }
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> asin(const T val) noexcept
    {
        if (std::is_constant_evaluated())
        {
            // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
            return eqx::Radians<T>{-eqx::acos(val).get()
                + (std::numbers::pi_v<T> / static_cast<T>(2.0))};
            // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        }
        else
        {
            eqx::ENSURE_HARD(val >= static_cast<T>(-1.0)
                && val <= static_cast<T>(1.0),
                "Domain Error!"sv);
            return eqx::Radians<T>{std::asin(val)};
        }
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> acos(const T val) noexcept
    {
        using namespace eqx::literals;
        if (std::is_constant_evaluated())
        {
            eqx::ENSURE_HARD(val >= static_cast<T>(-1.0)
                && val <= static_cast<T>(1.0),
                "Domain Error!"sv);

            // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
            return eqx::Radians<T>{eqx::newtonsMethod(
                static_cast<T>(-0.95) * eqx::tan(eqx::Radians<T>{val})
                    + (std::numbers::pi_v<T> / static_cast<T>(2.0)),
                14_uz,
                [val](const T x)
                    { return x - ((eqx::cos(eqx::Radians<T>{x}) - val)
                        / -eqx::sin(eqx::Radians<T>{x})); })};
            // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        }
        else
        {
            eqx::ENSURE_HARD(val >= static_cast<T>(-1.0)
                && val <= static_cast<T>(1.0),
                "Domain Error!"sv);
            return eqx::Radians<T>{std::acos(val)};
        }
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> atan(const T val) noexcept
    {
        using namespace eqx::literals;
        if (std::is_constant_evaluated())
        {
            const auto comp = static_cast<T>(1.0)
                / eqx::sqrt(static_cast<T>(1.0) + (val * val));

            // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
            return eqx::Radians<T>{eqx::newtonsMethod(
                eqx::acos(comp).get() * eqx::sign(val),
                1_uz,
                [val](const T x)
                    { return x - ((eqx::tan(eqx::Radians<T>{x}) - val)
                        * eqx::cos(eqx::Radians<T>{x})
                        * eqx::cos(eqx::Radians<T>{x})); })};
            // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        }
        else
        {
            return eqx::Radians<T>{std::atan(val)};
        }
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr eqx::Radians<T> atan2(const T x, const T y) noexcept
    {
        if (std::is_constant_evaluated())
        {
            eqx::ENSURE_HARD(eqx::hypot(x, y) != eqx::c_Zero<T>);
            return eqx::Radians<T>{
                eqx::acos(x / eqx::hypot(x, y)).get()
                    * static_cast<T>(eqx::sign(y))};
        }
        else
        {
            return eqx::Radians<T>{std::atan2(x, y)};
        }
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr std::pair<eqx::Radians<T>, eqx::Radians<T>> arcsin(
        const T val) noexcept
    {
        auto result = asin(val);
        return std::make_pair(result,
            eqx::Radians<T>{std::numbers::pi_v<T>
                + (eqx::c_2Pi<T> - result.get())});
    }

    template <typename T>
        requires std::floating_point<T>
    [[nodiscard]] constexpr std::pair<eqx::Radians<T>, eqx::Radians<T>> arccos(
        const T val) noexcept
    {
        auto result = acos(val);
        return std::make_pair(result, eqx::Radians<T>{-result.get()});
    }
}

#endif // EQX_Math_Trig_123