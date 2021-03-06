/*
 * Copyright (C) 2014 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef POLDER_MATH_CMATH_BASE_H_
#define POLDER_MATH_CMATH_BASE_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <type_traits>
#include <POLDER/details/config.h>

namespace polder
{
namespace math
{
namespace meta
{
namespace details
{
    template<typename Number>
    constexpr auto abs(Number x)
        -> Number
    {
        return (x >= 0) ? x : -x;
    }

    template<typename T, typename U>
    constexpr auto min(T first, U second)
        -> std::common_type_t<T, U>
    {
        return (first < second) ? first : second;
    }

    template<typename T, typename U, typename... Rest>
    constexpr auto min(T first, U second, Rest... rest)
        -> std::common_type_t<T, U, Rest...>
    {
        return (first < second) ?
            details::min(first, rest...) :
            details::min(second, rest...);
    }

    template<typename T, typename U>
    constexpr auto max(T first, U second)
        -> std::common_type_t<T, U>
    {
        return (first > second) ? first : second;
    }

    template<typename T, typename U, typename... Rest>
    constexpr auto max(T first, U second, Rest... rest)
        -> std::common_type_t<T, U, Rest...>
    {
        return (first > second) ?
            details::max(first, rest...) :
            details::max(second, rest...);
    }

    template<typename Float>
    constexpr auto is_close(std::true_type, Float lhs, Float rhs)
        -> bool
    {
        using math::meta::details::abs;
        using math::meta::details::max;

        return abs(lhs-rhs) <=
            std::numeric_limits<Float>::epsilon() *
            max(abs(lhs), abs(rhs));
    }

    template<typename T>
    constexpr auto is_close(std::false_type, T lhs, T rhs)
        -> bool
    {
        return lhs == rhs;
    }

    template<typename T>
    constexpr auto is_close(T lhs, T rhs)
        -> bool
    {
        return is_close(std::is_floating_point<T>{}, lhs, rhs);
    }
}}}}

#endif // POLDER_MATH_CMATH_BASE_H_
