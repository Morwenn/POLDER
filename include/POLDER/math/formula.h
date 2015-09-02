/*
 * Copyright (C) 2011-2014 Morwenn
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
#ifndef POLDER_MATH_FORMULA_H_
#define POLDER_MATH_FORMULA_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <array>
#include <cmath>
#include <complex>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>
#include <POLDER/details/config.h>
#include <POLDER/math/cmath.h>
#include <POLDER/math/constants.h>


namespace polder
{
namespace math
{
    ////////////////////////////////////////////////////////////
    // Basic functions

    /**
     * @brief signum function
     * @param x Some number
     * @return Sign of \a x
     */
    template<typename Number>
    auto sign(Number x)
        -> int;

    /**
     * @brief Sum of a number of variables
     */
    template<typename T, typename U, typename... Rest>
    auto sum(T first, U second, Rest... rest)
        -> std::common_type_t<T, U, Rest...>;

    /**
     * @brief Mean of a number of variables
     */
    template<typename... Numbers>
    auto mean(Numbers... args)
        -> decltype(sum(args...) / sizeof...(args));

    /**
     * @brief Square function
     * @param x Some number
     * @return Square of \a x
     */
    template<typename Number>
    auto sqr(Number x)
        -> Number;

    /**
     * @brief Limits a value to a range
     * @param x Number to clamp
     * @param min Lower limit
     * @param max Higher limit
     * @return \a x clamped between \a min and \a max
     */
    template<typename Number>
    auto clamp(Number x, Number min, Number max)
        -> Number;

    ////////////////////////////////////////////////////////////
    // Integer-related functions

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
     * @brief Fibonacci function
     * @param n Some integer
     * @return Nth Fibonacci number
     */
    template<typename Unsigned>
    auto fibonacci(Unsigned n)
        -> Unsigned;

    /**
     * @brief Greatest common divisor
     *
     * Greatest common divisor of two integer values.
     * The result will always be positive, even if one
     * of the passed values is negative.
     *
     * @param a Some integer
     * @param b Some integer
     * @return Greatest common divisor of a and b
     */
    template<typename Integer>
    auto gcd(Integer a, Integer b)
        -> Integer;

    /**
     * @brief Least common multiple
     *
     * Least common multiple of two integer values.
     * The result will always be positive, even if
     * one of the passed values is negative.
     *
     * @param a Some integer
     * @param b Some integer
     * @return Least common multiple of a and b
     */
    template<typename Integer>
    auto lcm(Integer a, Integer b)
        -> Integer;

    /**
     * @brief Modular exponentiation
     * @param a Base
     * @param b Exponent
     * @param c Modulus
     * @return pow(a, b) % c
     */
    template<typename Unsigned>
    auto modpow(Unsigned a, Unsigned b, Unsigned c)
        -> Unsigned;

    ////////////////////////////////////////////////////////////
    // Angle conversions

    /**
     * @brief Converts an angle in radians into an angle in degrees.
     * @param x Angle in radians
     * @return The degrees value
     */
    template<typename Float>
    auto degrees(Float x)
        -> Float;

    /**
     * @brief Converts an angle in degrees into an angle in radians.
     * @param x Angle in degrees
     * @return The radians value
     */
    template<typename Float>
    auto radians(Float x)
        -> Float;

    ////////////////////////////////////////////////////////////
    // Trigonometric functions

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

    ////////////////////////////////////////////////////////////
    // Miscellaneous functions

    /**
     * @brief Resolves a quadratic equation
     *
     * @param a First member of the quadratic equation
     * @param b Second member of the quadratic equation
     * @param c Third member of the quadratic equation
     * @return Roots of the quadratic equation
     */
    template<typename Float>
    auto quadratic(Float a, Float b, Float c)
        -> std::array<std::complex<Float>, 2u>;

    /**
     *
     * @brief Approximative comparison.
     *
     * Compares two numbers by checking whether the difference
     * between the two of them is small enough.
     *
     * If the types are not floating point types, a regular
     * comparison is performed instead.
     *
     * @param lhs First value to compare
     * @param rhs Second value to compare
     * @return true if the values compare equal
     */
    template<typename T>
    auto is_close(T lhs, T rhs)
        -> bool;

    namespace meta
    {
        template<typename Number>
        constexpr auto sign(Number x)
            -> int;

        template<typename T, typename U, typename... Rest>
        constexpr auto sum(T first, U second, Rest... rest)
            -> std::common_type_t<T, U, Rest...>;

        template<typename... Numbers>
        constexpr auto mean(Numbers... args)
            -> decltype(sum(args...) / sizeof...(args));

        template<typename Number>
        constexpr auto sqr(Number x)
            -> Number;

        template<typename Number>
        constexpr auto clamp(Number x, Number min, Number max)
            -> Number;

        template<typename Integer>
        constexpr auto is_even(Integer n)
            -> bool;

        template<typename Integer>
        constexpr auto is_odd(Integer n)
            -> bool;

        template<typename Unsigned>
        constexpr auto is_prime(Unsigned n)
            -> bool;

        template<typename Unsigned>
        constexpr auto fibonacci(Unsigned n)
            -> Unsigned;

        template<typename Unsigned>
        constexpr auto gcd(Unsigned a, Unsigned b)
            -> Unsigned;

        template<typename Unsigned>
        constexpr auto lcm(Unsigned a, Unsigned b)
            -> Unsigned;

        template<typename Unsigned>
        constexpr auto modpow(Unsigned a, Unsigned b, Unsigned c)
            -> Unsigned;

        template<typename Float>
        constexpr auto degrees(Float radians)
            -> Float;

        template<typename Float>
        constexpr auto radians(Float degrees)
            -> Float;

        template<typename T>
        constexpr auto is_close(T lhs, T rhs)
            -> bool;
    }

    #include "details/formula.inl"
}}

#endif // POLDER_MATH_FORMULA_H_
