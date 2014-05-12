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
#include <algorithm>
#include <POLDER/geometry.h>

int main()
{
    using namespace polder;

    // TEST: line-circle intersection
    {
        using Circle = geometry::Hypersphere<2u, double>;
        using Line = geometry::Line<2u, double>;
        using Point = geometry::Point<2u, double>;

        Line li = {
            Point { 2.0, 1.0 },
            Point { 3.0, 1.0 }
        };

        ////////////////////////////////////////////////////////////
        // Intersection: two points

        Circle cr1 = {
            Point { 0.0, 1.0 },
            1.0
        };

        try
        {
            if (auto res = intersection(li, cr1))
            {
                std::sort(std::begin(*res), std::end(*res));
                POLDER_ASSERT(
                    std::get<0>(*res) == Point(-1.0, 1.0) &&
                    std::get<1>(*res) == Point(1.0, 1.0)
                );
            }
            else
            {
                bool INTERSECTION1_IS_NULL = false;
                POLDER_ASSERT(INTERSECTION1_IS_NULL);
            }
        }
        catch (const Point&)
        {
            bool INTERSETION1_IS_ONE_POINT = false;
            POLDER_ASSERT(INTERSETION1_IS_ONE_POINT);
        }

        ////////////////////////////////////////////////////////////
        // No intersection

        Circle cr2 = {
            Point { 0.0, 3.0 },
            1.0
        };

        try
        {
            POLDER_ASSERT(not intersection(li, cr2));
        }
        catch (const Point&)
        {
            bool INTERSETION2_IS_ONE_POINT = false;
            POLDER_ASSERT(INTERSETION2_IS_ONE_POINT);
        }

        ////////////////////////////////////////////////////////////
        // Intersection: one point

        Circle cr3 = {
            Point {}, // origin
            1.0
        };

        try
        {
            if (auto res = intersection(li, cr3))
            {
                bool INTERSECTION3_IS_TWO_POINTS = false;
                POLDER_ASSERT(INTERSECTION3_IS_TWO_POINTS);
            }
            else
            {
                bool INTERSECTION3_IS_NULL = false;
                POLDER_ASSERT(INTERSECTION3_IS_NULL);
            }
        }
        catch (const Point& pt)
        {
            POLDER_ASSERT(pt == Point(0.0, 1.0));
        }

        ////////////////////////////////////////////////////////////
        // Reverse arguments order

        POLDER_ASSERT(intersection(li, cr1) == intersection(cr1, li));
        POLDER_ASSERT(intersection(li, cr2) == intersection(cr2, li));
    }
}
