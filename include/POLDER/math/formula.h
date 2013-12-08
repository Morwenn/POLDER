/*
 * Copyright (C) 2011-2013 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */
#ifndef _POLDER_MATH_FORMULA_H
#define _POLDER_MATH_FORMULA_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <complex>
#include <utility>
#include <vector>
#include <POLDER/config.h>
#include <POLDER/math/constants.h>


namespace polder
{
namespace math
{


inline namespace standard
{
    /**
     * @brief signum function
     * @param val Any number
     * @return Sign of \a val
     */
    template<typename Number>
    auto sign(Number val)
        -> int;

    /**
     * @brief Tells whether the given number is even
     * @param n Integer value
     * @return Whether \a n is even or not
     */
    template<typename Integer>
    auto is_even(Integer n)
        -> bool;

    /**
     * @brief Tells whether the given number is odd
     * @param n Integer value
     * @return Whether \a n is odd or not
     */
    template<typename Integer>
    auto is_odd(Integer n)
        -> bool;

    /**
     * @brief Tells whether the given number is a prime number
     * @param n Integer value
     * @return True if \a n is a prime number
     */
    template<typename Unsigned>
    auto is_prime(Unsigned n)
        -> bool;

    /**
     * @brief Converts an angle in radians into an angle in degrees.
     * @param radians Angle in radians
     * @return The degrees value
     */
    template<typename Float>
    auto degrees(Float radians)
        -> Float;

    /**
     * @brief Converts an angle in degrees into an angle in radians.
     * @param degrees Angle in degrees
     * @return The radians value
     */
    template<typename Float>
    auto radians(Float degrees)
        -> Float;

    /**
     * @brief Unnormalized sinc function
     * @param x Real value
     * @return Unnormalized cardinal sine of x
     */
    template<typename Float>
    auto sinc(Float x)
        -> Float;

    /**
     * @brief Normalized sinc function
     * @param x Real value
     * @return Normalized cardinal sine of x
     */
    template<typename Float>
    auto normalized_sinc(Float x)
        -> Float;

    /**
     * @brief Resolves a quadratic equation
     *
     * @param A First member of the quadratic equation
     * @param B Second member of the quadratic equation
     * @param C Third member of the quadratic equation
     * @return Roots of the quadratic equation
     */
    template<typename Float>
    auto quadratic(Float A, Float B, Float C)
        -> std::pair<std::complex<Float>, std::complex<Float>>;

    /**
     * @brief Fibonacci function
     * @param n Some integer
     * @return Nth Fibonacci number
     */
    template<typename Unsigned>
    auto fibonacci(Unsigned n)
        -> Unsigned;

    /**
     * @brief Search a prime number
     *
     * The first prime number returned by the function is 1,
     * even if it not "really" a prime number. It can still
     * be useful in some cases.
     *
     * @param n Some integer
     * @return Nth Prime number
     */
    template<typename Unsigned>
    auto prime(Unsigned n)
        -> Unsigned;

    /**
     * @brief Greatest common divisor
     * @param a Some integer
     * @param b Some integer
     * @return Greatest common divisor of a and b
     */
    template<typename Unsigned>
    auto gcd(Unsigned a, Unsigned b)
        -> Unsigned;

    /**
     * @brief Least common multiple
     * @param a Some integer
     * @param b Some integer
     * @return Least common multiple of a and b
     */
    template<typename Unsigned>
    auto lcm(Unsigned a, Unsigned b)
        -> Unsigned;
}

namespace meta
{
    /**
     * @brief signum function
     * @param val Any number
     * @return Sign of \a val
     */
    template<typename Number>
    constexpr auto sign(Number val)
        -> int;

    /**
     * @brief Tells whether the given number is even
     * @param n Integer value
     * @return Whether \a n is even or not
     */
    template<typename Integer>
    constexpr auto is_even(Integer n)
        -> bool;

    /**
     * @brief Tells whether the given number is odd
     * @param n Integer value
     * @return Whether \a n is odd or not
     */
    template<typename Integer>
    constexpr auto is_odd(Integer n)
        -> bool;

    /**
     * @brief Tells whether the given number is a prime number
     * @param n Integer value
     * @return True if \a n is a prime number
     */
    template<typename Unsigned>
    constexpr auto is_prime(Unsigned n)
        -> bool;

    /**
     * @brief Converts an angle in radians into an angle in degrees.
     * @param radians Angle in radians
     * @return The degrees value
     */
    template<typename Float>
    constexpr auto degrees(Float radians)
        -> Float;

    /**
     * @brief Converts an angle in degrees into an angle in radians.
     * @param degrees Angle in degrees
     * @return The radians value
     */
    template<typename Float>
    constexpr auto radians(Float degrees)
        -> Float;

    /**
     * @brief Fibonacci function
     * @param n Some integer
     * @return nth Fibonacci number
     */
    template<typename Unsigned>
    constexpr auto fibonacci(Unsigned n)
        -> Unsigned;
}

#include <POLDER/math/formula.inl>


} // namespace math
} // namespace polder


#endif // _POLDER_MATH_FORMULA_H
