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
#include <iostream>
#include <POLDER/algorithm.h>
#include <POLDER/geometry/hypersphere.h>
#include <POLDER/geometry/point.h>
#include <POLDER/geometry/vector.h>

int main()
{
    using namespace polder;

    // TEST: basic operations
    // - construction
    // - comparison
    {
        using Circle = geometry::Hypersphere<2u, double>;
        using Point = geometry::Point<2u, double>;
        using Vector = geometry::Vector<2u, double>;

        Circle foo;
        (void) foo;

        Point pt1 = { 2.0, 4.0 };
        Point pt2 = { 3.2, 5.8 };
        Vector vec = { 8.5, 7.528 };

        Circle c1 = { pt2, 2.16333 };
        POLDER_ASSERT(c1.centre == pt2);
        POLDER_ASSERT(c1.radius == 2.16333);

        Circle c2 = { pt1, vec };
        POLDER_ASSERT(c2.centre == pt1);
        POLDER_ASSERT(c2.radius == vec.norm());

        Circle c3 = { pt1, pt2 };
        POLDER_ASSERT(c3.centre == pt1);
        POLDER_ASSERT(
            c3.radius == (pt2-pt1).norm()
        );

        Circle c4 = { pt1, pt2-pt1 };

        POLDER_ASSERT(c4 == c3);
        POLDER_ASSERT(c2 != c3);
        POLDER_ASSERT(c1 != c2);
    }

    // TEST: inclusion
    {
        using Circle = geometry::Hypersphere<2u, double>;
        using Point = geometry::Point<2u, double>;

        Point origin;
        Point pt1 = { 2.0, 0.0 };
        Point pt2 = { 0.0, 2.0 };

        Circle c1 = { origin, pt1 };
        POLDER_ASSERT(c1.includes(pt1));
        POLDER_ASSERT(c1.includes(pt2));
        POLDER_ASSERT(not c1.includes(origin));
    }
}
