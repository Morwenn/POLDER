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
#include <POLDER/geometry/point.h>
#include <POLDER/geometry/vector.h>

int main()
{
    using namespace polder;

    // TEST: Point basic operations
    // - construction
    // - indexing
    // relational operators
    {
        using Point = geometry::Point<2u, int>;

        Point a(48, 23);
        POLDER_ASSERT(a[0] == 48);
        POLDER_ASSERT(a[1] == 23);
        POLDER_ASSERT(a.x() == 48);
        POLDER_ASSERT(a.y() == 23);
        POLDER_ASSERT(*(a.begin()) == 48);

        Point b = { 48, 23 };
        POLDER_ASSERT(b[0] == 48);
        POLDER_ASSERT(b[1] == 23);
        POLDER_ASSERT(b.x() == 48);
        POLDER_ASSERT(b.y() == 23);
        POLDER_ASSERT(*(b.begin()) == 48);

        POLDER_ASSERT(a == b);
        POLDER_ASSERT(not (a != b));
        POLDER_ASSERT(Point(2, 3) != a);

        Point foo;
        POLDER_ASSERT(foo.x() == 0);
        POLDER_ASSERT(foo.y() == 0);
    }

    // TEST: Point-Point subtraction
    {
        using Point = geometry::Point<2u, int>;
        using Vector = geometry::Vector<2u, int>;

        Point a = { 2, 3 };
        Point b = { 6, 8 };

        POLDER_ASSERT(b-a == Vector(4, 5));
        POLDER_ASSERT(a-b == Vector(-4, -5));
        POLDER_ASSERT(b-a == -(a-b));
    }

    // TEST: Point-Vector operations
    // - addition
    // - subtraction
    {
        using Point = geometry::Point<2u, int>;
        using Vector = geometry::Vector<2u, int>;

        Point pt = { 5, -3 };
        Vector vec = { -1, 8 };

        POLDER_ASSERT(pt+vec == Point(4, 5));
        POLDER_ASSERT(pt-vec == Point(6, -11));
        POLDER_ASSERT(pt+vec == vec+pt);
    }
}
