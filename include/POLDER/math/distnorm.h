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
#ifndef POLDER_MATH_DISTNORM_H_
#define POLDER_MATH_DISTNORM_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <POLDER/details/config.h>

namespace polder
{
namespace math
{
    /**
     * @brief Mathematical distances.
     *
     * Collection of tag classes that represent
     * mathematical distances.
     */
    namespace dist
    {
        struct manhattan {};
        struct euclidean {};
        struct chebyshev {};
        struct minkowski {};
        struct canberra {};
    }

    /**
     * @brief Mathematical norms.
     *
     * Collection of tag classes that represent
     * mathematical norms. Every norm tag is an
     * alias for a polder::math::dist distance.
     */
    namespace norm
    {
        using manhattan = dist::manhattan;
        using euclidean = dist::euclidean;
        using uniform   = dist::chebyshev;
        using p         = dist::minkowski;
    }
}}

#endif // POLDER_MATH_DISTNORM_H_
