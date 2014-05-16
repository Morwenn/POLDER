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
#ifndef POLDER_MATH_CONSTANTS_H_
#define POLDER_MATH_CONSTANTS_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <POLDER/details/config.h>

namespace polder
{
namespace math
{
    ////////////////////////////////////////////////////////////
    // Mathematical constants
    ////////////////////////////////////////////////////////////

    /*
     * All of the constants start with M_
     * After that suffix, we consider that the underscore
     * represents a division and that a number before a name
     * (ex: 2PI) represents a multiplication (2*PI)
     */

    ////////////////////////////////////////////////////////////
    // Non-standard constants of <cmath>
    ////////////////////////////////////////////////////////////

    /*
     * The non-standard POSIX macros constants
     * from <cmath> are undefined if needed and
     * redefined in POLDER as type-safe constexpr
     * variables.
     */

    #ifdef M_E
        #undef M_E
    #endif
    #ifdef M_LOG2E
        #undef M_LOG2E
    #endif
    #ifdef M_LOG10E
        #undef M_LOG10E
    #endif
    #ifdef M_LN2
        #undef M_LN2
    #endif
    #ifdef M_LN10
        #undef M_LN10
    #endif
    #ifdef M_PI
        #undef M_PI
    #endif
    #ifdef M_PI_2
        #undef M_PI_2
    #endif
    #ifdef M_PI_4
        #undef M_PI_4
    #endif
    #ifdef M_1_PI
        #undef M_1_PI
    #endif
    #ifdef M_2_PI
        #undef M_2_PI
    #endif
    #ifdef M_2_SQRTPI
        #undef M_2_SQRTPI
    #endif
    #ifdef M_SQRT2
        #undef M_SQRT2
    #endif
    #ifdef M_SQRT1_2
        #undef M_SQRT1_2
    #endif

    /** e */
    constexpr double M_E        = 2.71828182845904523540;

    /** log2(e) */
    constexpr double M_LOG2E    = 1.44269504088896340740;

    /** log10(e) */
    constexpr double M_LOG10E   = 0.43429448190325182765;

    /** ln(2) */
    constexpr double M_LN2      = 0.69314718055994530942;

    /** ln(10) */
    constexpr double M_LN10     = 2.30258509299404568402;

    /** pi */
    constexpr double M_PI       = 3.14159265358979323846;

    /** pi/2 */
    constexpr double M_PI_2     = 1.57079632679489661923;

    /** pi/4 */
    constexpr double M_PI_4     = 0.78539816339744830962;

    /** 1/pi */
    constexpr double M_1_PI     = 0.31830988618379067154;

    /** 2/pi */
    constexpr double M_2_PI     = 0.63661977236758134308;

    /** 2/sqrt(pi) */
    constexpr double M_2_SQRTPI = 1.12837916709551257390;

    /** sqrt(2) */
    constexpr double M_SQRT2    = 1.41421356237309504880;

    /** sqrt(1/2) */
    constexpr double M_SQRT1_2  = 0.70710678118654752440;

    ////////////////////////////////////////////////////////////
    // Constants related to the unit circle
    ////////////////////////////////////////////////////////////

    /** pi/3 */
    constexpr double M_PI_3     = 1.04719755119659774615;

    /** pi/6 */
    constexpr double M_PI_6     = 0.52359877559829887307;

    /** 2*pi/3 */
    constexpr double M_2PI_3    = 2.09439510239319549231;

    /** 3*pi/4 */
    constexpr double M_3PI_4    = 2.35619449019234492884;

    /** 5*pi/6 */
    constexpr double M_5PI_6    = 2.61799387799149436538;

    /** 7*pi/6 */
    constexpr double M_7PI_6    = 3.66519142918809211153;

    /** 5*pi/4 */
    constexpr double M_5PI_4    = 3.92699081698724154807;

    /** 4*pi/3 */
    constexpr double M_4PI_3    = 4.18879020478639098461;

    /** 5*pi/3 */
    constexpr double M_5PI_3    = 5.23598775598298873076;

    /** 7*pi/4 */
    constexpr double M_7PI_4    = 5.49778714378213816731;

    /** 11*pi/6 */
    constexpr double M_11PI_6   = 5.75958653158128760384;

    /** sqrt(2)/2 */
    constexpr double M_SQRT2_2  = 0.70710678118654752440;

    /** sqrt(2)/3 */
    constexpr double M_SQRT2_3  = 0.47140452079103168293;

    ////////////////////////////////////////////////////////////
    // Other common mathematical constants
    ////////////////////////////////////////////////////////////

    /** Golden ratio */
    constexpr double M_PHI      = 1.61803398874989484820;

    /** sqrt(3) */
    constexpr double M_SQRT3    = 1.73205080756887729352;

    /** pi/180 */
    constexpr double M_PI_180   = 0.01745329251994329577;

    /** 180/pi */
    constexpr double M_180_PI   = 57.2957795130823208768;

    /** 2*pi */
    constexpr double M_2PI      = 6.28318530717958647692;
}}

#endif // POLDER_MATH_CONSTANTS_H_
