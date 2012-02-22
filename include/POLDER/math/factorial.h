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
#ifndef _POLDER_MATH_FACTORIAL_H
#define _POLDER_MATH_FACTORIAL_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <POLDER/config.h>
#include <POLDER/math/constants.h>


namespace polder
{
namespace math
{


inline namespace standard
{
    /**
     * @brief Iterative factorial function
     * @param N Some integer
     * @return Factorial of N
     */
    POLDER_API unsigned int factorial(unsigned int N);

    /**
     * @see constexpr unsigned int polder::math::meta::stirling(unsigned int N);
     */
    POLDER_API constexpr unsigned int stirling(unsigned int N);
}


namespace meta
{
    /**
     * @brief Compile time factorial function
     * @param N Some integer
     * @return Factorial of N
     */
    POLDER_API constexpr unsigned int factorial(unsigned int N);

    /**
     * @brief Stirling formula
     * @param N Some integer
     * @return Approximation of the factorial of N
     */
    POLDER_API constexpr unsigned int stirling(unsigned int N);
}

namespace memoized
{
    /**
     * @brief Memoized factorial function
     * @param N Some integer
     * @return Factorial of N
     */
    POLDER_API unsigned int factorial(unsigned int N);
}


} // namespace math
} // namespace polder


#endif // _POLDER_MATH_FACTORIAL_H
