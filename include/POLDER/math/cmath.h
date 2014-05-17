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
#ifndef POLDER_MATH_CMATH_H_
#define POLDER_MATH_CMATH_H_

/**
 * @file POLDER/math/cmath.h
 * @brief compile-time versions of functions from <cmath>.
 *
 * This header provides functions aimed to mimic the ones
 * present in the header <cmath>. Some of them are not as
 * versatile as the original ones, some of them are more
 * versatile (e.g. min and max are variadic). If a function
 * is less versatile than the original one, the difference
 * between the two of them will be documented.
 *
 * The names slightly different from the original ones (for
 * example fabs, fmin and fmax are replaced by abs, min and
 * max).
 *
 * All of these functions are meant to be executed at
 * compile time and are less efficient than their <cmath>
 * counterparts at runtime.
 */

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <type_traits>
#include <POLDER/algorithm.h>
#include <POLDER/details/config.h>
#include <POLDER/math/details/cmath_base.h>

namespace polder
{
namespace math
{
namespace meta
{
    ////////////////////////////////////////////////////////////
    // Basic functions

    template<typename Number>
    constexpr auto abs(Number x)
        -> Number;

    /**
     * @brief Min of a number of variables
     */
    template<typename T, typename U, typename... Rest>
    constexpr auto min(T first, U second, Rest... rest)
        -> std::common_type_t<T, U, Rest...>;

    /**
     * @brief Max of a number of variables
     */
    template<typename T, typename U, typename... Rest>
    constexpr auto max(T first, U second, Rest... rest)
        -> std::common_type_t<T, U, Rest...>;

    ////////////////////////////////////////////////////////////
    // Number-theoretic and representation functions

    template<typename Float>
    constexpr auto floor(Float value)
        -> int;

    template<typename Float>
    constexpr auto ceil(Float value)
        -> int;

    template<typename Float>
    constexpr auto round(Float value)
        -> int;

    template<typename Float>
    constexpr auto trunc(Float value)
        -> int;

    ////////////////////////////////////////////////////////////
    // Power and logarithmic functions

    /**
     * @brief Power function.
     *
     * Because of the way it is implemented, this function may
     * be less precise than the <cmath> one. Moreover, it only
     * accepts integer exponents.
     */
    template<typename T, typename Integer>
    constexpr auto pow(T x, Integer exponent)
        -> std::common_type_t<T, Integer>;

    /**
     * @brief Square root function.
     *
     * Square root computation with the babylonian method until
     * the best possible precision for the given floating point
     * type.
     */
    template<typename Float>
    constexpr auto sqrt(Float x)
        -> Float;

    #include "details/cmath.inl"
}}}

#endif // POLDER_MATH_CMATH_H_
