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
#include <catch.hpp>
#include <POLDER/geometry/direction.h>
#include <POLDER/geometry/line.h>
#include <POLDER/geometry/point.h>
#include <POLDER/geometry/vector.h>

using namespace polder;

TEST_CASE( "line basic operations", "[geometry][line]" )
{
    using Line = geometry::Line<2u>;
    using Point = geometry::Point<2u>;

    Point origin;
    Point pt1 = { 1.0, 1.0 };
    Point pt2 = { 2.0, 2.0 };
    Point pt3 = { 2.0, 1.0 };

    Line li1 = { origin, pt1 };
    Line li2 = { origin, pt2 };
    Line li3 = { pt1, pt3 };

    SECTION( "inclusion" )
    {
        CHECK( li1.includes(origin) );
        CHECK( li1.includes(pt1) );
        CHECK( li1.includes(pt2) );
        CHECK( not li1.includes(pt3) );
        CHECK( li3.includes(li3.point()) );
        CHECK( li1.includes(li2.point()) );
        CHECK( li2.includes(li1.point()) );
    }

    SECTION( "comparison operators" )
    {
        CHECK( li1 == li1 );
        CHECK( li1 == li2 );
        CHECK( li1 != li3 );
        CHECK( li3 == li3 );
        REQUIRE_FALSE( li1 == li3 );
    }
}

TEST_CASE( "line inclusion method, tricky corner case", "[geometry][line]" )
{
    // Corner case. With the regular formula,
    // this would fail because of a division
    // by zero.

    using Line = geometry::Line<2u>;
    using Point = geometry::Point<2u>;

    Point origin;
    Point pt1 = { 2.0, 0.0 };
    Point pt2 = { 0.0, 2.0 };

    Line li1 = { origin, pt1 };
    Line li2 = { origin, pt2 };

    CHECK( li1.includes(pt1) );
    CHECK( li2.includes(pt2) );

    CHECK( not li1.includes(pt2) );
    CHECK( not li2.includes(pt1) );
}

TEST_CASE( "line constructors", "[geometry][line]" )
{
    using Direction = geometry::Direction<2u, int>;
    using Line = geometry::Line<2u, int>;
    using Point = geometry::Point<2u, int>;
    using Vector = geometry::Vector<2u, int>;

    Point pt1 = { 1, 2 };
    Point pt2 = { 5, 6 };
    Vector vec = { 4, 4 };
    Direction dir(vec);

    Line li1 = { pt1, pt2 };
    Line li2 = { pt1, vec };
    Line li3 = { pt1, dir };

    CHECK( li1 == li2 );
    CHECK( li1 == li3 );
    CHECK( li2 == li3 );
}
