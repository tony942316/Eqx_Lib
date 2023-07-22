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

#ifndef EQUINOX_UTILITYMACROS_HPP
#define EQUINOX_UTILITYMACROS_HPP

#include "details/Dependencies.hpp"

// NOLINTBEGIN(cppcoreguidelines-macro-usage,bugprone-macro-parentheses)

/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header, 
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_PARENS ()
/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_COMMA ,

/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_EXPAND1(...) __VA_ARGS__
/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_EXPAND2(...) \
    P_EQX_EXPAND1(P_EQX_EXPAND1(P_EQX_EXPAND1(P_EQX_EXPAND1(__VA_ARGS__))))
/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_EXPAND3(...) \
    P_EQX_EXPAND2(P_EQX_EXPAND2(P_EQX_EXPAND2(P_EQX_EXPAND2(__VA_ARGS__))))
/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_EXPAND4(...) \
    P_EQX_EXPAND3(P_EQX_EXPAND3(P_EQX_EXPAND3(P_EQX_EXPAND3(__VA_ARGS__))))
/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_EXPAND5(...) \
    P_EQX_EXPAND4(P_EQX_EXPAND4(P_EQX_EXPAND4(P_EQX_EXPAND4(__VA_ARGS__))))
/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_EXPAND(...) \
    P_EQX_EXPAND5(P_EQX_EXPAND5(P_EQX_EXPAND5(P_EQX_EXPAND5(__VA_ARGS__))))

/**
 * @brief Apply The First Argument To All Other Arguments
 *      i.e. EQX_FOR_EACH(SOME_MACRO, x, y, z) Would Produce
 *      SOME_MACRO(x) SOME_MACRO(y) SOME_MACRO(z)
 *
 * @param macro The Macro That Will Be Called On Each Argument
 * @param ... The Arguments That Will Be Used As Parameters For macro
 *
 * @returns The Result Of Applying macro To Each Argument Seperated By Spaces
 */
#define EQX_FOR_EACH(macro, ...) \
    __VA_OPT__(P_EQX_EXPAND(P_EQX_FOR_EACH_HELPER(macro, __VA_ARGS__)))
/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_FOR_EACH_HELPER(macro, a1, ...) \
    macro(a1) \
    __VA_OPT__(P_EQX_FOR_EACH_AGAIN P_EQX_PARENS (macro, __VA_ARGS__))
/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_FOR_EACH_AGAIN() P_EQX_FOR_EACH_HELPER

/**
 * @brief Apply The First Argument To All Other Arguments
 *      i.e. EQX_FOR_EACH_LIST(SOME_MACRO, x, y, z) Would Produce
 *      SOME_MACRO(x), SOME_MACRO(y), SOME_MACRO(z),
 *      Note The Addition Of Commas As Compared To EQX_FOR_EACH
 *
 * @param macro The Macro That Will Be Called On Each Argument
 * @param ... The Arguments That Will Be Used As Parameters For macro
 *
 * @returns The Result Of Applying macro To Each Argument Seperated By Commas
 */
#define EQX_FOR_EACH_LIST(macro, ...) \
    __VA_OPT__(P_EQX_EXPAND(P_EQX_FOR_EACH_LIST_HELPER(macro, __VA_ARGS__)))
/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_FOR_EACH_LIST_HELPER(macro, a1, ...) \
    macro(a1) \
    __VA_OPT__(P_EQX_COMMA P_EQX_FOR_EACH_LIST_AGAIN P_EQX_PARENS \
        (macro, __VA_ARGS__))
/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_FOR_EACH_LIST_AGAIN() P_EQX_FOR_EACH_LIST_HELPER

/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_COUNT_ARGS_HELPER(x) 1U+
/**
 * @brief Macro That Will Count The Number Of Arguments Provided
 *      i.e. EQX_COUNT_ARGS(a, b, c) Would Produce 1U + 1U + 1U + 0U
 *
 * @param ... The Arguments To Be Counted
 *
 * @returns The Sum Of The Number Of Arguments As A Repeated Addition Of
 *      1U
 */
#define EQX_COUNT_ARGS(...) \
    EQX_FOR_EACH(P_EQX_COUNT_ARGS_HELPER, __VA_ARGS__) 0U

/**
 * @brief Macro For Use By Other Macros In The UtilityMacros Header,
 *      NOT FOR EXTERNAL USE!
 */
#define P_EQX_STRING_ARGS_HELPER(x) #x
/**
 * @brief Macro That Will Parrot Back A const char[n] Of Its Inputs
 *      i.e. EQX_STRING_ARGS(a, b, c) Would Produce "a", "b", "c"
 *
 * @param ... The Arguments To Be Converted To const char[n]
 *
 * @returns A Comma Seperated "List"
 *      (NOT A std::list JUST LITERAL VALUES SEPERATED BY COMMAS!)
 *      Of The Converted Arguments
 */
#define EQX_STRING_ARGS(...) \
    EQX_FOR_EACH_LIST(P_EQX_STRING_ARGS_HELPER, __VA_ARGS__)

#ifdef _MSC_VER
/**
 * @brief Macro That Will Suppress A Warning
 */

/**
 * @brief Macro That Will Restore Last Suppressed Warning
 */
#define EQX_RESTORE_WARNING __pragma(warning(pop))

#endif // _MSC_VER

#ifdef __GNUC__
/**
 * @brief Macro That Will Suppress A Warning For One Line
 */

/**
 * @brief Macro That Will Restore Last Suppressed Warning
 */
#define EQX_RESTORE_WARNING _Pragma("GCC diagnostic pop")

#endif // __GNUC__

// NOLINTEND(cppcoreguidelines-macro-usage,bugprone-macro-parentheses)

#endif // EQUINOX_UTILITYMACROS_HPP
