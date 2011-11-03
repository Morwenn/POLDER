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


////////////////////////////////////////////////////////////
/// Mathematical constants
////////////////////////////////////////////////////////////

/* Some of these constants should be included in math.h
However, those includes are not standard, that is why we
check for each constant if it exists before including it. */

// Non standard constants of math.h
#ifndef M_E
    # define M_E 2.7182818284590452354
#endif
#ifndef M_LOG2E
    #define M_LOG2E 1.4426950408889634074
#endif
#ifndef M_LOG10E
    #define M_LOG10E 0.43429448190325182765
#endif
#ifndef M_LN2
    #define M_LN2 0.69314718055994530942
#endif
#ifndef M_LN10
    #define M_LN10 2.30258509299404568402
#endif
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#ifndef M_PI_2
    #define M_PI_2 1.57079632679489661923
#endif
#ifndef M_PI_4
    #define M_PI_4 0.78539816339744830962
#endif
#ifndef M_1_PI
    #define M_1_PI 0.31830988618379067154
#endif
#ifndef M_2_PI
    #define M_2_PI 0.63661977236758134308
#endif
#ifndef M_2_SQRTPI
    #define M_2_SQRTPI 1.12837916709551257390
#endif
#ifndef M_SQRT_2
    #define M_SQRT2 1.41421356237309504880
#endif
#ifndef M_SQRT1_2
    #define M_SQRT1_2 0.70710678118654752440
#endif

// Constants related to the unit circle
#ifndef M_PI_3
    #define M_PI_3 1.04719755119659774615
#endif
#ifndef M_PI_6
    #define M_PI_6 0.52359877559829887307
#endif
#ifndef M_2PI_3
    #define M_2PI_3 2.0943951023931954923
#endif
#ifndef M_3PI_4
    #define M_3PI_4 2.35619449019234492884
#endif
#ifndef M_5PI_6
    #define M_5PI_6 2.61799387799149436538
#endif
#ifndef M_7PI_6
    #define M_7PI_6 3.66519142918809211153
#endif
#ifndef M_5PI_4
    #define M_5PI_4 3.92699081698724154807
#endif
#ifndef M_4PI_3
    #define M_4PI_3 4.18879020478639098461
#endif
#ifndef M_5PI_3
    #define M_5PI_3 5.23598775598298873076
#endif
#ifndef M_7PI_4
    #define M_7PI_4 5.4977871437821381673
#endif
#ifndef M_11PI_6
    #define M_11PI_6 5.75958653158128760384
#endif
#ifndef M_SQRT2_2
    #define M_SQRT2_2 0.7071067811865475244
#endif
#ifndef M_SQRT3_2
    #define M_SQRT3_2 1.73205080756887729352
#endif

// Other constants
#ifndef M_PHI
    #define M_PHI 1.61803398874989484820
#endif
#ifndef M_SQRT3
    #define M_SQRT3 1.73205080756887729352
#endif


namespace polder
{
namespace math
{


////////////////////////////////////////////////////////////
/// Basic functions
////////////////////////////////////////////////////////////
double degree(double rad);
double radian(double deg);
double sinc(double x);


////////////////////////////////////////////////////////////
/// Miscellaneous functions
////////////////////////////////////////////////////////////
std::pair<std::complex<double>, std::complex<double>> quadratic(double A, double B, double C);
unsigned int factorial(unsigned int N);
unsigned int stirling(unsigned int N);
unsigned int fibonacci(unsigned int N);
unsigned int prime(unsigned int N);
unsigned int gcd(unsigned int a, unsigned int b);
unsigned int lcm(unsigned int a, unsigned int b);


} // namespace math
} // namespace polder


#endif
