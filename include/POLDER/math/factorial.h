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
#ifndef POLDER_MATH_FACTORIAL_H_
#define POLDER_MATH_FACTORIAL_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cmath>
#include <POLDER/details/config.h>
#include <POLDER/math/constants.h>

namespace polder
{
namespace math
{
    /**
     * @brief Iterative factorial function
     * @param n Some integer
     * @return Factorial of n
     */
    template<typename Unsigned>
    auto factorial(Unsigned n)
        -> Unsigned;

    /**
     * @brief Double factorial function
     * @param n Some integer
     * @return Double factorial of n
     */
    template<typename Unsigned>
    auto double_factorial(Unsigned n)
        -> Unsigned;

    /**
     * @brief Stirling formula
     * @param n Some integer
     * @return Approximation of the factorial of n
     */
    template<typename Unsigned>
    auto stirling(Unsigned n)
        -> Unsigned;

    namespace meta
    {
        template<typename Unsigned>
        constexpr auto factorial(Unsigned n)
            -> Unsigned;
    }

    #include "details/factorial.inl"
}}

#endif // POLDER_MATH_FACTORIAL_H_
