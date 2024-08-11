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

#ifndef EQUINOX_MACROS_HPP
#define EQUINOX_MACROS_HPP

#ifdef EQX_NO_ASSERTS
#define ENSURE_HARD(...) noOp();
#define EQX_NO_ASSERTS true
#else
#define ENSURE_HARD(...) ensure(__VA_ARGS__);
#define EQX_NO_ASSERTS false
#endif // EQX_NO_ASSERTS

#endif // EQUINOX_MACROS_HPP
