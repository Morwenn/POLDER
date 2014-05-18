/*
 * Copyright (C) 2014 Morwenn
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
#include <POLDER/math/cmath.h>

namespace polder
{
namespace math
{
namespace meta
{
    ////////////////////////////////////////////////////////////
    // Basic functions

    template<typename Int, Int N>
    constexpr auto abs(semisymbolic::Constant<Int, N>)
        -> semisymbolic::Constant<Int, abs(N)>
    {
        return {};
    }

    template<typename Int, Int... Numbers>
    constexpr auto min(semisymbolic::Constant<Int, Numbers>...)
        -> semisymbolic::Constant<Int, min(Numbers...)>
    {
        return {};
    }

    template<typename Int, Int... Numbers>
    constexpr auto max(semisymbolic::Constant<Int, Numbers>...)
        -> semisymbolic::Constant<Int, max(Numbers...)>
    {
        return {};
    }

    ////////////////////////////////////////////////////////////
    // Power and logarithmic functions

    template<typename Int, Int N, Int M>
    constexpr auto pow(semisymbolic::Constant<Int, N>,
                       semisymbolic::Constant<Int, M>)
        -> semisymbolic::Constant<Int, pow(N, M)>
    {
        return {};
    }
}}}
