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

/**
 * @file POLDER/geometry.h
 * @brief This header includes the 2d geometry module.
 */

#ifndef POLDER_GEO2D_H_
#define POLDER_GEO2D_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <POLDER/geometry.h>

namespace polder
{
    /**
     * @namespace polder::geo2d
     * @brief Geometry-related objects and functions
     *
     * This namespace contains contains aliases to
     * the objects of the main geometry modules in
     * order to provide consistent and easy names to
     * use with a 2d geometry module.
     */
    namespace geo2d
    {
        // Aliases for types
        template<typename T=double>
        using Direction = geometry::Direction<2u, T>;
        template<typename T=double>
        using Circle = geometry::Hypersphere<2u, T>;
        template<typename T=double>
        using Line = geometry::Line<2u, T>;
        template<typename T=double>
        using Point = geometry::Point<2u, T>;
        template<typename T=double>
        using Vector = geometry::Vector<2u, T>;

        // Aliases for functions
        using geometry::distance;
        using geometry::intersection;
        using geometry::intersects;
    }
}

#endif // POLDER_GEO2D_H_
