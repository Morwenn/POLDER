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
#include <iostream>
#include <utility>
#include <POLDER/geometry.h>
#include <POLDER/geo2d.h>
#include <POLDER/geo3d.h>
#include <POLDER/utility.h>

using namespace polder;

int main()
{
    ////////////////////////////////////////////////////////////
    // Construction of simple objects
    {
        using namespace geometry;

        Point<3> p1(2.0, 2.5, 5.2);
        Point<3> p2 = { 0.1, 2.9, 9.000001 };

        Vector<3> v1(2.0, 2.1, 2.2);
        Vector<3> v2 = { 2.5, 8.3, 6. };
        Vector<3> v3 = { p1, p2 };

        Line<3> li = { p1, p2 };

        Direction<3> d1 = v1.direction();
        Direction<3> d2 = li.direction();

        Hypersphere<3> hs1(p1, 5.0);
        Hypersphere<3> hs2 = hs1;

        // Ignore warnings about
        // variables not used
        ignore(v2, v3, d1, d2, hs2);
    }


    ////////////////////////////////////////////////////////////
    // Intersection
    {
        using namespace geo2d;

        Line<> li = {
            Point<>(15.0, 1.0),
            Point<>(23.7, 1.0)
        };

        Circle<> c1 = {
            Point<>(0.0, 1.0),  // centre
            1.0                 // radius
        };

        Circle<> c2 = {
            Point<>(0.0, 3.0),  // centre
            1.0                 // radius
        };

        Circle<> c3 = {
            Point<>(0.0, 1.0),  // centre
            0.0                 // radius
        };

        try
        {
            // Change to c1, c2 or c3 in order
            // to see the different behaviours
            if (auto res = intersection(li, c1))
            {
                // c1
                std::cout << "intersection: two points" << '\n'
                          << std::get<0>(*res).x() << " "
                          << std::get<0>(*res).y() << '\n'   //  1, 1
                          << std::get<1>(*res).x() << " "
                          << std::get<1>(*res).y() << '\n';  // -1, 1
            }
            else
            {
                // c2
                std::cout << "no intersection" << '\n';
            }
        }
        catch (const Point<>& point)
        {
            // c3
            std::cout << "intersection: one point" << '\n'
                      << point.x() << " "
                      << point.y() << '\n';
        }

        ignore(c1, c2, c3);
    }

    ////////////////////////////////////////////////////////////
    // Distance
    {
        using namespace geo3d;

        Point<> a = { 4.5, 6.3, 15.23 };
        Point<> b = { 8.9, 25.3, 7.65 };
        std::cout << distance(a, b) << std::endl;

        POLDER_ASSERT(distance(a, b) == distance(b, a));
        POLDER_ASSERT(distance(a, a) == distance(b, b));
        POLDER_ASSERT(distance(a, a) == 0.0);
    }
}
