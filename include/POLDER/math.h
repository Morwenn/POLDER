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
#ifndef _POLDER_MATH_H
#define _POLDER_MATH_H

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <complex>
#include <cstdlib>
#include <utility>


/* Some of these constants should be included in math.h
However, those includes are not standard, that is why we
check for each constant if it exists.
    If the constant exists, we undefine it and redefine
it as a constexpr for more type safety. */

// Non standard constants of math.h
#ifndef M_E
    #undef M_E
#endif
#ifndef M_LOG2E
    #undef M_LOG2E
#endif
#ifndef M_LOG10E
    #undef M_LOG10E
#endif
#ifndef M_LN2
    #undef M_LN2
#endif
#ifndef M_LN10
    #undef M_LN10
#endif
#ifndef M_PI
    #undef M_PI
#endif
#ifndef M_PI_2
    #undef M_PI_2
#endif
#ifndef M_PI_4
    #undef M_PI_4
#endif
#ifndef M_1_PI
    #undef M_1_PI
#endif
#ifndef M_2_PI
    #undef M_2_PI
#endif
#ifndef M_2_SQRTPI
    #undef M_2_SQRTPI
#endif
#ifndef M_SQRT_2
    #undef M_SQRT2
#endif
#ifndef M_SQRT1_2
    #undef M_SQRT1
#endif


namespace polder
{
namespace math
{


////////////////////////////////////////////////////////////
// Mathematical constants
////////////////////////////////////////////////////////////

/* All of the constants start with M_
After that suffix, we consider that the underscore
represents a division and that a number before a name
(ex: 2PI) represents a multiplication (2*PI) */

// Non-standard constants of math.h
constexpr double M_E        = 2.71828182845904523540;   // e
constexpr double M_LOG2E    = 1.44269504088896340740;   //
constexpr double M_LOG10E   = 0.43429448190325182765;   //
constexpr double M_LN2      = 0.69314718055994530942;   // ln(2)
constexpr double M_LN10     = 2.30258509299404568402;   // ln(10)
constexpr double M_PI       = 3.14159265358979323846;   // pi
constexpr double M_PI_2     = 1.57079632679489661923;   // pi / 2
constexpr double M_PI_4     = 0.78539816339744830962;   // pi / 4
constexpr double M_1_PI     = 0.31830988618379067154;   // 1 / pi
constexpr double M_2_PI     = 0.63661977236758134308;   // 2 / pi
constexpr double M_2_SQRTPI = 1.12837916709551257390;   // 2 / sqrt(pi)
constexpr double M_SQRT2    = 1.41421356237309504880;   // sqrt(2)
constexpr double M_SQRT1_2  = 0.70710678118654752440;   // sqrt(0.5)

// Constants related to the unit circle
constexpr double M_PI_3     = 1.04719755119659774615;   // pi / 3
constexpr double M_PI_6     = 0.52359877559829887307;   // pi / 6
constexpr double M_2PI_3    = 2.09439510239319549231;   // 2 * pi / 3
constexpr double M_3PI_4    = 2.35619449019234492884;   // 3 * pi / 4
constexpr double M_5PI_6    = 2.61799387799149436538;   // 5 * pi / 6
constexpr double M_7PI_6    = 3.66519142918809211153;   // 7 * pi / 6
constexpr double M_5PI_4    = 3.92699081698724154807;   // 5 * pi / 4
constexpr double M_4PI_3    = 4.18879020478639098461;   // 4 * pi / 3
constexpr double M_5PI_3    = 5.23598775598298873076;   // 5 * pi / 3
constexpr double M_7PI_4    = 5.49778714378213816731;   // 7 * pi / 4
constexpr double M_11PI_6   = 5.75958653158128760384;   // 11 * pi / 6
constexpr double M_SQRT2_2  = 0.70710678118654752440;   // sqrt(2) / 2
constexpr double M_SQRT2_3  = 0.47140452079103168293;   // sqrt(2) / 3

// Other mathematical constants
constexpr double M_PHI      = 1.61803398874989484820;   // Golden ratio
constexpr double M_SQRT3    = 1.73205080756887729352;   // sqrt(3)
constexpr double M_PI_180   = 0.01745329251994329577;   // pi / 180
constexpr double M_180_PI   = 57.2957795130823208768;   // 180 / pi
constexpr double M_2PI      = 6.28318530717958647692;   // 2 * pi


////////////////////////////////////////////////////////////
// Basic functions
////////////////////////////////////////////////////////////

/**
 * @brief Tells whether the given number is even
 * @param n Integer value
 * @return Whether n is even or not
 */
constexpr bool is_even(long long int n);


/**
 * @brief Tells whether the given number is odd
 * @param n Integer value
 * @return Whether n is odd or not
 */
constexpr bool is_odd(long long int n);

/**
 * @brief Converts an angle in radians into an angle in degrees.
 * @param radians Angle in radians
 * @return The degrees value
 */
constexpr double degree(double radians);

/**
 * @brief Converts an angle in degrees into an angle in radians.
 * @param degrees Angle in degrees
 * @return The radians value
 */
constexpr double radian(double degrees);

/**
 * @brief Unnormalized sinc function
 * @param x Real value
 * @return Unnormalized cardinal sine of x
 */
constexpr double sinc(double x);
float sinc(float x);
long double sinc(long double x);

/**
 * @brief Normalized sinc function
 * @param x Real value
 * @return Normalized cardinal sine of x
 */
constexpr double normalized_sinc(double x);


////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////

/**
 * @brief Resolves a quadratic equation
 * @param A First member of the quadratic equation
 * @param B Second member of the quadratic equation
 * @param C Third member of the quadratic equation
 * @return Roots of the quadratic equation
 */
std::pair<std::complex<double>, std::complex<double>> quadratic(double A, double B, double C);

/**
 * @brief Factorial function
 * @param N Some integer
 * @return Factorial of N
 */
unsigned int factorial(unsigned int N);

/**
 * @brief Stirling formula
 * @param N Some integer
 * @return Approximation of the factorial of N
 */
unsigned int stirling(unsigned int N);

/**
 * @brief Fibonacci function
 * @param N Some integer
 * @return Nth Fibonacci number
 */
unsigned int fibonacci(unsigned int N);

/**
 * @brief Search a prime number
 *
 * The first prime number returned by the function is 1,
 * even if it not "really" a prime number. It can still
 * be useful in some cases.
 *
 * @param N Some integer
 * @return Nth Prime number
 */
unsigned int prime(unsigned int N);

/**
 * @brief Greatest common divisor
 * @param a Some integer
 * @param b Some integer
 * @return Greatest common divisor of a and b
 */
unsigned int gcd(unsigned int a, unsigned int b);

/**
 * @brief Least common multiple
 * @param a Some integer
 * @param b Some integer
 * @return Least common multiple of a and b
 */
unsigned int lcm(unsigned int a, unsigned int b);


} // namespace math
} // namespace polder


#endif // _POLDER_MATH_H
