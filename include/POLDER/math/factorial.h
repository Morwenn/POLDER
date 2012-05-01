/*
 * Copyright (C) 2011-2012 Morwenn
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
#include <cassert>
#include <cmath>
#include <POLDER/config.h>
#include <POLDER/math/constants.h>
#include <POLDER/math/formula.h>


namespace polder
{
namespace math
{


inline namespace standard
{
    /**
     * @brief Iterative factorial function
     * @param n Some integer
     * @return Factorial of n
     */
    POLDER_API unsigned long long int factorial(unsigned long long int n);

    /**
     * @brief Double factorial function
     * @param n Some integer
     * @return Double factorial of n
     */
    POLDER_API unsigned long long int double_factorial(unsigned long long int n);

    /**
     * @brief Stirling formula
     * @param n Some integer
     * @return Approximation of the factorial of n
     */
    POLDER_API unsigned long long int stirling(unsigned long long int n);
}


namespace meta
{
    /**
     * @brief Compile time factorial function
     * @param n Some integer
     * @return Factorial of n
     */
    constexpr unsigned long long int factorial(unsigned long long int n) noexcept;

    /**
     * @brief Stirling formula
     * @param n Some integer
     * @return Approximation of the factorial of n
     */
    constexpr unsigned long long int stirling(unsigned long long int n);

    #include <POLDER/math/factorial.inl>
}

namespace memoized
{
    /**
     * @brief Memoized factorial function
     * @param n Some integer
     * @return Factorial of n
     */
    POLDER_API unsigned long long int factorial(unsigned long long int n);
}


} // namespace math
} // namespace polder


#endif // _POLDER_MATH_FACTORIAL_H
