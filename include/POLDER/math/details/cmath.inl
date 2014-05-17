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

////////////////////////////////////////////////////////////
// Helper functions

namespace details
{
    template<typename T, typename Unsigned>
    constexpr auto pow_helper(T x, Unsigned exponent)
        -> T
    {
        // Exponentiation by squaring
        return (exponent == 0) ? 1 :
            (exponent % 2 == 0) ? pow_helper(x*x, exponent/2) :
                x * pow_helper(x*x, (exponent-1)/2);
    }

    template<typename T>
    constexpr auto sqrt_helper(T x, T y)
        -> T
    {
        return float_equal(x, y*y) ? y :
            sqrt_helper(x, (y + x/y) / 2.0);
    }
}

////////////////////////////////////////////////////////////
// Basic functions

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

////////////////////////////////////////////////////////////
// Number-theoretic and representation functions

template<typename Float>
constexpr auto floor(Float x)
    -> int
{
    return (int(x) == x) ? int(x) :
        (x >= 0.0) ? int(x) :
            int(x) - 1;
}

template<typename Float>
constexpr auto ceil(Float x)
    -> int
{
    return (int(x) == x) ? int(x) :
        (x >= 0.0) ? int(x) + 1 :
            int(x);
}

template<typename Float>
constexpr auto round(Float x)
    -> int
{
    return (x >= 0.0) ? int(x + 0.5) : int(x - 0.5);
}

template<typename Float>
constexpr auto trunc(Float x)
    -> int
{
    return int(x);
}

////////////////////////////////////////////////////////////
// Power and logarithmic functions

template<typename T, typename Integer>
constexpr auto pow(T x, Integer exponent)
    -> std::common_type_t<T, Integer>
{
    return (exponent == 0) ? 1 :
        (exponent > 0) ? details::pow_helper(x, exponent) :
            1 / details::pow_helper(x, -exponent);
}

template<typename Float>
constexpr auto sqrt(Float x)
    -> Float
{
    return details::sqrt_helper(x, x);
}
