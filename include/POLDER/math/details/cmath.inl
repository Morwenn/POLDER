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

namespace details
{
    template<typename T, typename U>
    constexpr auto pow_helper(T acc, T value, U times)
        -> T
    {
        return (times > 1) ?
            pow_helper(acc*value, value, times-1) :
                acc;
    }

    template<typename T>
    constexpr auto sqrt_helper(T x, T y)
        -> T
    {
        return float_equal(x, y*y) ? y :
            sqrt_helper(x, (y + x/y) / 2.0);
    }
}

template<typename Number>
constexpr auto abs(Number x)
    -> Number
{
    return details::abs(x);
}

template<typename T, typename U, typename... Rest>
constexpr auto min(T first, U second, Rest... rest)
    -> std::common_type_t<T, U, Rest...>
{
    return details::min(first, second, rest...);
}

template<typename T, typename U, typename... Rest>
constexpr auto max(T first, U second, Rest... rest)
    -> std::common_type_t<T, U, Rest...>
{
    return details::max(first, second, rest...);
}

template<typename Float>
constexpr auto floor(Float value)
    -> int
{
    return (int(value) == value) ? int(value) :
        (value >= 0.0) ? int(value) :
            int(value) - 1;
}

template<typename Float>
constexpr auto ceil(Float value)
    -> int
{
    return (int(value) == value) ? int(value) :
        (value >= 0.0) ? int(value) + 1 :
            int(value);
}

template<typename Float>
constexpr auto round(Float value)
    -> int
{
    return (value >= 0.0) ? int(value + 0.5) : int(value - 0.5);
}

template<typename Float>
constexpr auto trunc(Float value)
    -> int
{
    return int(value);
}

template<typename T, typename U>
constexpr auto pow(T value, U exponent)
    -> std::common_type_t<T, U>
{
    return (exponent == 0) ? 1 :
        (exponent > 0) ? details::pow_helper(value, value, exponent) :
            1 / details::pow_helper(value, value, exponent);
}

template<typename Float>
constexpr auto sqrt(Float x)
    -> Float
{
    return details::sqrt_helper(x, x);
}
