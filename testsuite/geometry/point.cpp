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
#include <POLDER/geometry/point.h>
#include <POLDER/geometry/vector.h>

using namespace polder;

TEST_CASE( "point basic operations", "[geometry][point]" )
{
    using Point = geometry::Point<2u, int>;

    Point origin;
    Point a(48, 23);
    Point b = { 48, 23 };

    SECTION( "indexing and basic observers" )
    {
        // default construction
        CHECK( origin[0] == 0 );
        CHECK( origin[1] == 0 );
        CHECK( origin.x() == 0 );
        CHECK( origin.y() == 0 );
        CHECK( *(origin.begin()) == 0 );

        CHECK( a[0] == 48 );
        CHECK( a[1] == 23 );
        CHECK( a.x() == 48 );
        CHECK( a.y() == 23 );
        CHECK( *(a.begin()) == 48 );

        CHECK( b[0] == 48 );
        CHECK( b[1] == 23 );
        CHECK( b.x() == 48 );
        CHECK( b.y() == 23 );
        CHECK( *(b.begin()) == 48 );
    }

    SECTION( "comparison operators" )
    {
        CHECK( a == b );
        REQUIRE_FALSE( a != b );
        CHECK( Point(2, 3) != a );
    }
}

TEST_CASE( "point relational operators", "[geometry][point]" )
{
    using Point = geometry::Point<3u, int>;

    Point origin;
    Point pt1 = { 2, 1, 1 };
    Point pt2 = { 1, 3, 5 };
    Point pt3 = { 1, 3, 4 };
    Point pt4 = { -5, 2, 6 };

    CHECK( origin < pt1 );
    CHECK( origin < pt2 );
    CHECK( origin > pt4 );
    CHECK( origin >= origin );
    CHECK( origin <= origin );

    CHECK( pt2 >= pt3 );
    CHECK( pt3 <= pt2 );
    CHECK( pt2 > pt3 );
    CHECK( pt3 < pt2 );
}

TEST_CASE( "point-vector arithmetic", "[geometry][point][vector]" )
{
    using Point = geometry::Point<2u, int>;
    using Vector = geometry::Vector<2u, int>;

    Point a = { 2, 3 };
    Point b = { 6, 8 };
    Point c = { 5, -3 };
    Vector vec = { -1, 8 };

    SECTION( "point-point subtraction" )
    {
        CHECK( b - a == Vector(4, 5) );
        CHECK( a - b == Vector(-4, -5) );
        CHECK( b - a == -(a - b) );
    }

    SECTION( "point-vector addition" )
    {
        CHECK( c + vec == Point(4, 5) );
        CHECK( b + vec == vec + b );
    }

    SECTION( "point-vector subtraction" )
    {
        CHECK( a - vec == Point(3, -5) );
        CHECK( b - vec == Point(7, 0) );
        CHECK( c - vec == Point(6, -11) );
    }
}
