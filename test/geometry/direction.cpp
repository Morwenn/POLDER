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
#include <POLDER/algorithm.h>
#include <POLDER/geometry/direction.h>
#include <POLDER/geometry/line.h>
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
        using Direction = geometry::Direction<3u, double>;
        using Vector = geometry::Vector<3u, double>;

        Vector vec = { 5.0, 8.0, -2.0 };
        Direction dir(vec);
        POLDER_ASSERT(dir == vec.direction());

        auto tmp = vec / vec.norm();
        POLDER_ASSERT(std::equal(tmp.begin(), tmp.end(), dir.begin(),
            [](double a, double b)
            {
                return polder::float_equal(std::abs(a), b);
            }
        ));

        Direction foo;
        (void) foo;
    }

    // TEST: constructors
    {
        using Direction = geometry::Direction<3u, double>;
        using Line = geometry::Line<3u, double>;
        using Point = geometry::Point<3u, double>;
        using Vector = geometry::Vector<3u, double>;

        Point origin = { 0.0, 0.0, 0.0 };
        Point pt = { 6.0, -2.0, 3.0 };
        Vector vec = { 6.0, -2.0, 3.0 };
        POLDER_ASSERT(Direction(pt) == Direction(vec));
        POLDER_ASSERT(Direction(pt) == Direction(origin, pt));

        Line li = { pt, vec };
        POLDER_ASSERT(Direction(li) == li.direction());
        POLDER_ASSERT(Direction(li) == Direction(pt, pt+vec));
    }
}
