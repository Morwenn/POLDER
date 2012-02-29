/*
 * Copyright (C) 2011 Morwenn
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
#ifndef _POLDER_MATH_FORMULA_H
#define _POLDER_MATH_FORMULA_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <complex>
#include <cstdlib>
#include <utility>
#include <POLDER/config.h>
#include <POLDER/math/constants.h>


namespace polder
{
namespace math
{


inline namespace standard
{
    /**
     * @brief Tells whether the given number is even
     * @param n Integer value
     * @return Whether \a n is even or not
     */
    POLDER_API constexpr bool is_even(long long int n);

    /**
     * @brief Tells whether the given number is odd
     * @param n Integer value
     * @return Whether \a n is odd or not
     */
    POLDER_API constexpr bool is_odd(long long int n);

    /**
     * @brief Tells whether the given number is a prime number
     * @param n Integer value
     * @return True if \a n is a prime number
     */
    POLDER_API constexpr bool is_prime(unsigned long long int n);

    /**
     * @brief Converts an angle in radians into an angle in degrees.
     * @param radians Angle in radians
     * @return The degrees value
     */
    POLDER_API constexpr double degree(double radians);

    /**
     * @brief Converts an angle in degrees into an angle in radians.
     * @param degrees Angle in degrees
     * @return The radians value
     */
    POLDER_API constexpr double radian(double degrees);

    /**
     * @brief Unnormalized sinc function
     * @param x Real value
     * @return Unnormalized cardinal sine of x
     */
    POLDER_API constexpr double sinc(double x);
    POLDER_API float sinc(float x);
    POLDER_API long double sinc(long double x);

    /**
     * @brief Normalized sinc function
     * @param x Real value
     * @return Normalized cardinal sine of x
     */
    POLDER_API constexpr double normalized_sinc(double x);

    /**
     * @brief Resolves a quadratic equation
     *
     * @param A First member of the quadratic equation
     * @param B Second member of the quadratic equation
     * @param C Third member of the quadratic equation
     * @return Roots of the quadratic equation
     */
    POLDER_API std::pair<std::complex<double>, std::complex<double>> quadratic(double A, double B, double C);

    /**
     * @brief Fibonacci function
     * @param n Some integer
     * @return Nth Fibonacci number
     */
    POLDER_API unsigned long long int fibonacci(unsigned long long int n);

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
    POLDER_API unsigned long long int prime(unsigned long long int n);

    /**
     * @brief Greatest common divisor
     * @param a Some integer
     * @param b Some integer
     * @return Greatest common divisor of a and b
     */
    POLDER_API unsigned int gcd(unsigned int a, unsigned int b);

    /**
     * @brief Least common multiple
     * @param a Some integer
     * @param b Some integer
     * @return Least common multiple of a and b
     */
    POLDER_API unsigned int lcm(unsigned int a, unsigned int b);
}

namespace meta
{
    /**
     * @brief Tells whether the given number is even
     * @param n Integer value
     * @return Whether \a n is even or not
     */
    POLDER_API constexpr bool is_even(long long int n);

    /**
     * @brief Tells whether the given number is odd
     * @param n Integer value
     * @return Whether \a n is odd or not
     */
    POLDER_API constexpr bool is_odd(long long int n);

    /**
     * @brief Tells whether the given number is a prime number
     * @param n Integer value
     * @return True if \a n is a prime number
     */
    POLDER_API constexpr bool is_prime(unsigned long long int n);

    /**
     * @brief Converts an angle in radians into an angle in degrees.
     * @param radians Angle in radians
     * @return The degrees value
     */
    POLDER_API constexpr double degree(double radians);

    /**
     * @brief Converts an angle in degrees into an angle in radians.
     * @param degrees Angle in degrees
     * @return The radians value
     */
    POLDER_API constexpr double radian(double degrees);

    /**
     * @brief Unnormalized sinc function
     * @param x Real value
     * @return Unnormalized cardinal sine of x
     */
    POLDER_API constexpr double sinc(double x);

    /**
     * @brief Normalized sinc function
     * @param x Real value
     * @return Normalized cardinal sine of x
     */
    POLDER_API constexpr double normalized_sinc(double x);

    /**
     * @brief Fibonacci function
     * @param n Some integer
     * @return nth Fibonacci number
     */
    POLDER_API constexpr unsigned long long int fibonacci(unsigned long long int n);
}

namespace memoized
{
    /**
     * @brief Tells whether the given number is a prime number
     * @param n Integer value
     * @return True if \a n is a prime number
     */
    POLDER_API constexpr bool is_prime(unsigned long long int n);

    /**
     * @brief Fibonacci function
     * @param n Some integer
     * @return nth Fibonacci number
     */
    POLDER_API unsigned long long int fibonacci(unsigned long long int n);

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
    POLDER_API unsigned long long int prime(unsigned long long int n);
}


} // namespace math
} // namespace polder


#endif // _POLDER_MATH_FORMULA_H
