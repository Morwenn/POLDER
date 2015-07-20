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
#include <cmath>
#include <algorithm>
#include <POLDER/geometry/direction.h>
#include <POLDER/geometry/line.h>
#include <POLDER/geometry/point.h>
#include <POLDER/geometry/vector.h>
#include "catch.hpp"

using namespace polder;

TEST_CASE( "direction basic operations", "[geometry][direction]" )
{
    using Direction = geometry::Direction<3u>;
    using Vector = geometry::Vector<3u>;

    Vector vec = { 5.0, 8.0, -2.0 };
    Direction dir(vec);
    CHECK( dir == vec.direction() );

    auto tmp = vec / vec.norm();
    CHECK( std::equal(tmp.begin(), tmp.end(), dir.begin(),
        [](double a, double b)
        {
            return std::abs(a) == Approx(b);
        }
    ) );

    Direction foo;
    (void) foo;
}

TEST_CASE( "direction constructors", "[geometry][direction]" )
{
    using Direction = geometry::Direction<3u>;
    using Line = geometry::Line<3u>;
    using Point = geometry::Point<3u>;
    using Vector = geometry::Vector<3u>;

    Point origin;
    Point pt = { 6.0, -2.0, 3.0 };
    Vector vec = { 6.0, -2.0, 3.0 };
    CHECK( Direction(pt) == Direction(vec) );
    CHECK( Direction(pt) == Direction(origin, pt) );

    Line li = { pt, vec };
    CHECK( Direction(li) == li.direction() );
    CHECK( Direction(li) == Direction(pt, pt+vec) );
}
