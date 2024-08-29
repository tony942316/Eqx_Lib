/*
 * Copyright (C) 2024 Anthony H. Grasso
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

#ifndef EQX_LIB_MACROS_HPP
#define EQX_LIB_MACROS_HPP

#ifdef EQX_NO_ASSERTS
#define ENSURE_HARD(...) noOp();
#define EQX_NO_ASSERTS true
#else
#define ENSURE_HARD(...) ensure(__VA_ARGS__);
#define EQX_NO_ASSERTS false
#endif // EQX_NO_ASSERTS

#if defined(_WIN32)
#define EQX_LINUX false
#define EQX_WINDOWS true
#elif defined(__linux__)
#define EQX_LINUX true
#define EQX_WINDOWS false
#endif

#if defined(__clang__)
#define EQX_CLANG true
#define EQX_GCC false
#define EQX_MSVC false
#elif defined(__GNUC__) || defined(__GNUG__)
#define EQX_CLANG false
#define EQX_GCC true
#define EQX_MSVC false
#elif defined(_MSC_VER)
#define EQX_CLANG false
#define EQX_GCC false
#define EQX_MSVC true
#endif

#endif // EQX_LIB_MACROS_HPP
